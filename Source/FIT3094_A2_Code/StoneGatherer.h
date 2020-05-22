// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/AGOAPActor.h"
#include "Components/StaticMeshComponent.h"
#include "StoneGatherer.generated.h"

/**
 * 
 */
UCLASS()
class FIT3094_A2_CODE_API AStoneGatherer : public AGOAPActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;
protected:
	virtual void BeginPlay() override;

public:
	AStoneGatherer();

	virtual void Tick(float DeltaTime) override;

	//Function for getting the current world state. Virtual as it probably should be overridden by child agents as they
	// will have different information
	TMap<FString, bool> GetWorldState() override;
	// Create a goal state we want to achieve. We could have multiple and pick one
	TMap<FString, bool> CreateGoalState() override;
};
