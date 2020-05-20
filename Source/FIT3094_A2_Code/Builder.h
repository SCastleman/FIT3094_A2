// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/AGOAPActor.h"
#include "Builder.generated.h"

/**
 * 
 */
UCLASS()
class FIT3094_A2_CODE_API ABuilder : public AGOAPActor
{
public:
	~ABuilder() override;
protected:
	void BeginPlay() override;
	TMap<FString, bool> GetWorldState() override;
	TMap<FString, bool> CreateGoalState() override;
	void OnPlanFailed(TMap<FString, bool> FailedGoalState) override;
	void OnPlanAborted(GOAPAction* FailedAction) override;
public:
	void Tick(float DeltaTime) override;

	const int MaxWood = 10;
	const int MaxStone = 5;
	int NumWood = 0;
	int NumStone = 0;
private:
	GENERATED_BODY()
	
};
