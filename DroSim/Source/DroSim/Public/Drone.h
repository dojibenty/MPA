#pragma once

#include "CoreMinimal.h"
#include "IManagerInterface.h"
#include "Components/SphereComponent.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Drone.generated.h"

UCLASS()
class DROSIM_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	ADrone();

protected:
	virtual void BeginPlay() override;
	virtual void SetNewDestination();
	void LoadConfig();
	float TickInterval;
	float MovementTolerance; // tolérance de placement
	float MovementSpeed; // vitesse de déplacement
	float MovementDistance; // distance parcourue entre chaque point de décision
	FVector CurrentDestination; // destination choisie au dernier point de décision
	FVector MoveDirection = FVector(1.0f,0,0); // direction choisie au dernier point de décision
	FVector2D EnvSize;
	float WanderDistance;
	int WanderSteps;
	float SpiralRadius;
	float SpiralMovementDistance;
	float SpiralIncrementFactor;
	bool DrawsConcentricCircles;
	int NbCirclePoints;
	float SweepHeight;
	float SweepLength;
	int SimulationSpeed;
	
public:
	virtual void Tick(float DeltaTime) override;
	int ID = -1;
	IManagerInterface* Manager;
	
	UFUNCTION()
	void OnObjectNear(UPrimitiveComponent* ThisSphere, AActor* OtherActor, UPrimitiveComponent* OtherSphere, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnObjectAway(UPrimitiveComponent* ThisSphere, AActor* OtherActor, UPrimitiveComponent* OtherSphere, int32 OtherBodyIndex);

	UFUNCTION()
	void OnObjectVisible(UPrimitiveComponent* ThisSphere, AActor* OtherActor, UPrimitiveComponent* OtherSphere, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float CollisionCheckRadius; // rayon de détection des collisions
	float VisionSphereRadius; // rayon de vision

	bool Init = true;

	TSet<ADrone*> OverlappingDrones;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* DetectionSphere;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* VisionSphere;
};