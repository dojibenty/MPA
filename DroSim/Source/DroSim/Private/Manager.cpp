#include "Manager.h"

#include "Misc/ConfigCacheIni.h"
#include "DrawDebugHelpers.h"
#include "Drone.h"
#include "DroneRandom.h"
#include "DroneSweep.h"
#include "DroneSpiral.h"
#include "Objective.h"


AManager::AManager()
{
	PrimaryActorTick.bCanEverTick = true;

	// Creation of a mesh component for the manager
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cone.Cone"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Meshes/Ship_Mesh"));
	if (MeshAsset.Succeeded()) StaticMesh->SetStaticMesh(MeshAsset.Object); 

	// Loading config from .ini file
	LoadConfig();
}


/**
 * Loading configuration from .ini file
 *
 * Sets initial values to variables.
 */
void AManager::LoadConfig()
{
	FString ConfigFilePath = FPaths::ProjectContentDir() + TEXT("SimConfig.ini");
	ConfigFilePath = FConfigCacheIni::NormalizeConfigIniPath(ConfigFilePath);

	GConfig->LoadFile(ConfigFilePath);
	
	GConfig->GetDouble(TEXT("sim/global"), TEXT("environment_X_length"), EnvSize.X, ConfigFilePath);
	GConfig->GetDouble(TEXT("sim/global"), TEXT("environment_Y_length"), EnvSize.Y, ConfigFilePath);
	
	GConfig->GetInt(TEXT("sim/global"), TEXT("sim_speed"), SimulationSpeed, ConfigFilePath);
	
	GConfig->GetFloat(TEXT("sim/manager"), TEXT("time_per_sim"), MaxTimePerSim, ConfigFilePath);
	GConfig->GetFloat(TEXT("sim/global"), TEXT("step"), TickInterval, ConfigFilePath);

	GConfig->GetInt(TEXT("sim/manager"), TEXT("strategy"), StrategyID, ConfigFilePath);

	GConfig->GetFloat(TEXT("sim/manager"), TEXT("speed_cost_multiplier"), SpeedCostMultiplier, ConfigFilePath);
	GConfig->GetFloat(TEXT("sim/drones"), TEXT("max_speed"), DroneMaxSpeed, ConfigFilePath);
	GConfig->GetFloat(TEXT("sim/manager"), TEXT("drone_cost"), DroneCost, ConfigFilePath);

	GConfig->GetFloat(TEXT("sim/manager"), TEXT("min_speed"), MinSpeed, ConfigFilePath);
	GConfig->GetInt(TEXT("sim/manager"), TEXT("min_drones"), MinNumDrones, ConfigFilePath);

	// Initial config for the first group of simulations
	GroupSpeed = MinSpeed;
	GroupNumDrones = MinNumDrones;

	GConfig->GetFloat(TEXT("sim/manager"), TEXT("speed_increment"), SpeedIncrement, ConfigFilePath);
	GConfig->GetInt(TEXT("sim/manager"), TEXT("drone_increment"), DroneIncrement, ConfigFilePath);
	GConfig->GetFloat(TEXT("sim/manager"), TEXT("curve_research_speed_multiplier"), CurveResearchSpeedMultiplier, ConfigFilePath);

	GConfig->GetFloat(TEXT("sim/drones"), TEXT("side_offset"), DroneSideOffset, ConfigFilePath);
	GConfig->GetFloat(TEXT("sim/drones"), TEXT("ground_offset"), DroneGroundOffset, ConfigFilePath);

	GConfig->GetInt(TEXT("sim/manager"), TEXT("sim_group_size"), SimGroupSize, ConfigFilePath);
	GConfig->GetInt(TEXT("sim/manager"), TEXT("max_successive_same_speed_configs"), MaxSuccessiveSameSpeedConfigs, ConfigFilePath);
}


/**
 * First function to be executed after instantiation.
 */
void AManager::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickInterval(TickInterval);

	UE_LOG(LogTemp, Warning, TEXT("Trying with speed=%f and drones=%d"), GroupSpeed, GroupNumDrones);
	ManageNewSimulation();
}


/**
 * Update function.
 *
 * This function is called every TickInterval seconds, as set in BeginPlay().
 *
 * @param DeltaTime Time elapsed since last frame.
 */
void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentSimulatedTime += DeltaTime * SimulationSpeed;
	
	if (CurrentSimulatedTime >= MaxTimePerSim) HandleSimulationEnd();
}


/**
 * Management function.
 *
 * The execution flow always comes back to this function unless the simulation is over.
 */
void AManager::ManageNewSimulation()
{
	if (AutoSuccess)
	{
		AutoSuccess = false;
		MutateSimulationParameters(true);
	}
	else if (AutoFail)
	{
		AutoFail = false;
		MutateSimulationParameters(false);
	}
	else
	{
		if (CurrentGroupSim++ == SimGroupSize) // End of current group
        	{
				// If >50% of simulations result in a success, the configuration is successful
				if (SimGroupSize == 1) MutateSimulationParameters(SuccessfulSim == 1);
        		else MutateSimulationParameters(SuccessfulSim >= SimGroupSize/2);
        		SuccessfulSim = 0;
        		CurrentGroupSim = 0;
        	}
		InitSimulation();
	}
}


/**
 * Mutate configuration of the current group of simulations, based on the outcome it gave.
 * 
 * @param IsSimSuccessful True if the current group configuration is successful, false otherwise.
 */
void AManager::MutateSimulationParameters(const bool IsSimSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("%hs"), IsSimSuccessful ? "Success" : "Fail");
	if (IsCurveFound)
	{
		if (!IsSimSuccessful && WasPreviousConfigSuccessful && PreviousNumDrones == GroupNumDrones)
		{
			// If the last saved config has the same speed as the current one with a different number of drones,
			// we increment the counter.
			// Otherwise, we reset it.
			if (SuccessfulConfigs.Contains(FVector2D(GroupSpeed,GroupNumDrones-1))) SuccessiveSameSpeedConfigs++;
			else SuccessiveSameSpeedConfigs = 0;

			// As the previous config was successful but the current one is not, we save the previous config
			SuccessfulConfigs.Add(FVector2D(PreviousSpeed,PreviousNumDrones));
            GroupSpeed = PreviousSpeed + SpeedIncrement;
            GroupNumDrones += DroneIncrement;

			// As the next config will have the same speed and an additional drone, we expect it to succeed
			AutoSuccess = true;
		}
		else if (IsSimSuccessful)
		{
			GroupSpeed -= SpeedIncrement;
			AutoFail = GroupSpeed < MinSpeed;
		}
	}
	else if (IsSimSuccessful)
	{
		// This block runs only once when the first successful config is found
		IsCurveFound = true;
		SuccessfulConfigs.Add(FVector2D(GroupSpeed,GroupNumDrones));
		GroupNumDrones += DroneIncrement;
		AutoSuccess = true;
		UE_LOG(LogTemp, Warning, TEXT("Curve found"));
	}
	else GroupSpeed += SpeedIncrement;

	// We save the current config for later comparison
	PreviousSpeed = GroupSpeed;
	PreviousNumDrones = GroupNumDrones;
	WasPreviousConfigSuccessful = IsSimSuccessful;
	
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Trying with speed=%f and drones=%d"), GroupSpeed, GroupNumDrones);
}


/**
 * Perform the initialization for a new simulation.
 *
 * It spawns an Objective and Drones and draws visuals.
 */
void AManager::InitSimulation()
{
	// Objective
	ObjectiveSpawnPoint = FVector(
		FMath::RandRange(EnvSize.X*.75,EnvSize.X),
		FMath::RandRange(-(EnvSize.Y/2),EnvSize.Y/2),
		GetActorLocation().Z);
	CurrentSimulatedObjective = GetWorld()->SpawnActor<AObjective>(AObjective::StaticClass(), ObjectiveSpawnPoint, GetActorRotation());

	// Drones
	int Idx = 0;
	switch (StrategyID)
	{
	case 1:
		SpawnDrones(ADroneRandom::StaticClass(), Idx);
		break;
	case 2:
		SpawnDrones(ADroneSweep::StaticClass(), Idx);
		break;
	case 3:
		SpawnDrones(ADroneSpiral::StaticClass(), Idx);
		break;
	default: break;
	}

	// Research environment limits visuals
	FVector BoxCenter = FVector(EnvSize.X/2,0,0);
	FVector BoxExtent = FVector(EnvSize.X/2,EnvSize.Y/2,200);
	DrawDebugBox(GetWorld(), BoxCenter, BoxExtent, FQuat::Identity, FColor::Green, true, -1, 0, 5);

	SimID++;
}


/**
 * Spawns a certain number of a given class of Drones in the environment.
 * 
 * @param DroneStrategy The derived class of Drone to spawn.
 * @param Idx ID of the first Drone to spawn, later incremented by 1 for each Drone.
 */
void AManager::SpawnDrones(const TSubclassOf<ADrone> DroneStrategy, int& Idx)
{
	for (int i = 0; i < GroupNumDrones; i++, Idx++)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0,DroneSideOffset * Idx,DroneGroundOffset - GetActorLocation().Z);
		ADrone* d = GetWorld()->SpawnActor<ADrone>(DroneStrategy, SpawnLocation, GetActorRotation());
		d->ID = Idx + 1; // A unique ID
		d->Manager = this; // A reference to the manager
		CurrentSimulatedDrones.Add(d);
	}
}


/**
 * Event function for a Drone loss.
 */
bool AManager::DroneDestroyedEvent()
{
	const int RdID = FMath::RandRange(1,GroupNumDrones);
	for (ADrone* d : TArray(CurrentSimulatedDrones))
		if (d->ID == RdID)
		{
			d->Destroy();
			CurrentSimulatedDrones.Remove(d);
			UE_LOG(LogTemp, Warning, TEXT("Lost communication with drone %d"), RdID);
			return true;
		}
		
	return false;
}


/**
 * Thrown by any Drone whenever it finds the Objective.
 * 
 * @param DroneID ID of the calling Drone for informative purpose.
 * @param ClassName Class of the calling Drone for informative purpose.
 */
void AManager::ObjectiveFound(const int DroneID, const FString ClassName)
{
	if (ReportedSimID == SimID) return;
	ReportedSimID = SimID;
	SuccessfulSim++;
	HandleSimulationEnd();
}


/**
 * Reset the environment to its initial state.
 *
 * This function destroys every Drones and Objective currently playing.
 *
 * If the stopping condition is met, results are produced and the simulation comes to an end.
 */
void AManager::HandleSimulationEnd()
{
	// Destroy all drones
	TArray<ADrone*> Copy = CurrentSimulatedDrones;
	for (ADrone* d : Copy) if (d) d->Destroy();
	CurrentSimulatedDrones.Empty();

	// Destroy objective
	CurrentSimulatedObjective->Destroy();

	// Clear debug shapes
	FlushPersistentDebugLines(GetWorld());

	// Reset time
	CurrentSimulatedTime = 0;

	// Set up new simulations or print results
	if (SimulationHasEnded) return;
	if (SuccessiveSameSpeedConfigs < MaxSuccessiveSameSpeedConfigs - 1) ManageNewSimulation();
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
		UE_LOG(LogTemp, Warning, TEXT("%d successive similar speeds : End of simulations"), MaxSuccessiveSameSpeedConfigs);
		for (FVector2D sc : SuccessfulConfigs) UE_LOG(LogTemp, Warning, TEXT("(vitesse:%f,drones:%f)"), sc.X, sc.Y);
		SimulationHasEnded = true;
		WriteResultsToFile();
	}
}


/**
 * Allows Drones to set their speed properly.
 * 
 * @returns The current speed the Drones are set to.
 */
float AManager::GetGroupDroneSpeed()
{
	return GroupSpeed;
}


/**
 * Appends successful configs to a result file.
 */
void AManager::WriteResultsToFile()
{
	FString ResultsFile = FPaths::ProjectConfigDir();
	ResultsFile.Append(TEXT("../results.txt"));
	
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	TArray<FString> ConfigsToWrite;
	for (FVector2D sc : SuccessfulConfigs) {
		FString FormattedString = FString::Printf(TEXT("vitesse:%f,drones:%d"), sc.X, static_cast<int>(sc.Y));
		ConfigsToWrite.Add(FormattedString);
	}
	
	if (FileManager.FileExists(*ResultsFile))
	{
		if (FFileHelper::SaveStringArrayToFile(ConfigsToWrite,*ResultsFile))
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully written \"%d\" strings to the text file"),ConfigsToWrite.Num());
		}
		else UE_LOG(LogTemp, Warning, TEXT("Failed to write to file."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("File not found."));
		UE_LOG(LogTemp, Warning, TEXT("Expected location: %s"),*ResultsFile);
	}
}

