#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drone.h"
#include "IManagerInterface.h"
#include "Objective.h"
#include "Manager.generated.h"

UCLASS()
class DROSIM_API AManager : public AActor, public IManagerInterface
{
	GENERATED_BODY()
	
public:
	AManager();

protected:
	virtual void BeginPlay() override;
	void LoadConfig();
	void InitSimulation();
	bool DroneDestroyedEvent();
	void HandleSimulationEnd();
	void MutateSimulationParameters(const bool IsSimSuccessful);
	void ManageNewSimulation();
	void SpawnDrones(const TSubclassOf<ADrone> DroneStrategy, int& Idx);
	void WriteResultsToFile();
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void ObjectiveFound(int DroneID, FString ClassName) override;
	virtual float GetGroupDroneSpeed() override;

private:
	FVector2D EnvSize;
	FVector ObjectiveSpawnPoint;

	float DroneSideOffset;
	float DroneGroundOffset;

	int StrategyID;

	float SpeedCostMultiplier;
	float DroneMaxSpeed;
	float DroneCost;

	float MinSpeed;
	int MinNumDrones;
	float GroupSpeed;
	int GroupNumDrones;

	float SpeedIncrement;
	int DroneIncrement;
	float CurveResearchSpeedMultiplier;

	float MaxTimePerSim;
	float TickInterval;
	float CurrentSimulatedTime;
	int SimulationSpeed;
	int SimID = 0;
	int ReportedSimID = 0;

	int SimGroupSize;
	int CurrentGroupSim = 0;
	int SuccessfulSim = 0;
	bool IsCurveFound = false;
	bool AutoSuccess = false;
	bool AutoFail = false;

	float PreviousSpeed = -1;
	int PreviousNumDrones = -1;
	bool WasPreviousConfigSuccessful = false;

	int MaxSuccessiveSameSpeedConfigs;
	int SuccessiveSameSpeedConfigs = 0;

	bool SimulationHasEnded = false;

	TArray<FVector2D> SuccessfulConfigs;

	AObjective* CurrentSimulatedObjective;
	TArray<ADrone*> CurrentSimulatedDrones;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
};
