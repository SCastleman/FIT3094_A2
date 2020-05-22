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
	GENERATED_BODY()
	virtual void BeginPlay() override;
public:
	ABuilder();
	TMap<FString, bool> GetWorldState() override;
	TMap<FString, bool> CreateGoalState() override;
	void Tick(float DeltaTime) override;

	const int MaxWood = 10;
	const int MaxStone = 5;
	int NumWood = 0;
	int NumStone = 0;
	
};
