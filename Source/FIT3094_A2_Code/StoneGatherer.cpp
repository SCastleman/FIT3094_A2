// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneGatherer.h"

#include "GOAP/DepositStoneAction.h"
#include "UObject/ConstructorHelpers.h"

AStoneGatherer::AStoneGatherer() : AGOAPActor()
{
	NumResource = 0;
	Health = 100;
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
	DepositStoneAction* DepositAction = new DepositStoneAction();
	DepositAction->AddPrecondition("HasResource", true);
	DepositAction->AddEffect("HasResource", false);
	AvailableActions.Add(DepositAction);
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



