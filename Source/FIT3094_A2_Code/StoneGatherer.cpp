// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneGatherer.h"

#include "GOAP/DepositAction.h"
#include "GOAP/GatherStoneAction.h"

AStoneGatherer::AStoneGatherer() : AGOAPActor()
{
	NumResource = 0;
	MaxResource = 1;
	Health = 40;
	MaxHealth = 100;
	FoodTrigger = 40;
}

void AStoneGatherer::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	GatherStoneAction* GatherAction = new GatherStoneAction();
	GatherAction->AddPrecondition("HasResource", false);
	GatherAction->AddEffect("HasResource", true);
	AvailableActions.Add(GatherAction);
	DepositAction* NewDepositAction = new DepositAction();
	NewDepositAction->AddPrecondition("HasResource", true);
	NewDepositAction->AddEffect("HasResource", false);
	AvailableActions.Add(NewDepositAction);
}

void AStoneGatherer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TMap<FString, bool> AStoneGatherer::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();

	WorldState.Add("HasResource", NumResource > 0) ;

	return WorldState;
}

TMap<FString, bool> AStoneGatherer::CreateGoalState()
{
	TMap<FString, bool> GoalState;
	GoalState.Add("HasResource", true);

	return GoalState;
}



