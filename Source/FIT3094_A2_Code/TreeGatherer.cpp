// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeGatherer.h"

#include "GOAP/DepositAction.h"
#include "GOAP/GatherTreeAction.h"
#include "UObject/ConstructorHelpers.h"

ATreeGatherer::ATreeGatherer() : AGOAPActor()
{
	NumResource = 0;
	MaxResource = 1;
	Health = 40;
	MaxHealth = 40;
	FoodTrigger = 15;
}

void ATreeGatherer::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	GatherTreeAction* NewAction = new GatherTreeAction();
	NewAction->AddPrecondition("HasResource", false);
	NewAction->AddEffect("HasResource", true);
	AvailableActions.Add(NewAction);
	DepositAction* NewDepositAction = new DepositAction();
	NewDepositAction->AddPrecondition("HasResource", true);
	NewDepositAction->AddEffect("HasResource", false);
	AvailableActions.Add(NewDepositAction);
}

void ATreeGatherer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TMap<FString, bool> ATreeGatherer::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();

	WorldState.Add("HasResource", NumResource > 0) ;

	return WorldState;
}

TMap<FString, bool> ATreeGatherer::CreateGoalState()
{
	TMap<FString, bool> GoalState;
	GoalState.Add("HasResource", true);

	return GoalState;
}



