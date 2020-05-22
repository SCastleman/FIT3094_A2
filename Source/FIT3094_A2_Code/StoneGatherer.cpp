// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneGatherer.h"

#include "GOAP/DepositAction.h"
#include "GOAP/GatherStoneAction.h"
#include "GOAP/PickupToolAction.h"
#include "Kismet/GameplayStatics.h"

AStoneGatherer::AStoneGatherer() : AGOAPActor()
{
	NumResource = 0;
	MaxResource = 20;
	Health = 100;
	MaxHealth = 100;
	FoodTrigger = 40;
}

void AStoneGatherer::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PickupToolAction* PickupTool = new PickupToolAction();
	PickupTool->AddPrecondition("HasTool", false);
	PickupTool->AddPrecondition("VillageHasTool", true);
	PickupTool->AddEffect("HasTool", true);
	AvailableActions.Add(PickupTool);
	GatherStoneAction* GatherAction = new GatherStoneAction();
	GatherAction->AddPrecondition("HasResource", false);
	GatherAction->AddPrecondition("HasTool", true);
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

	AVillageCentreActor* TempVillage = Cast<AVillageCentreActor>(UGameplayStatics::GetActorOfClass(this->GetWorld(), AVillageCentreActor::StaticClass()));
	WorldState.Add("HasResource", NumResource == MaxResource);
	WorldState.Add("HasTool", ToolHealth > 0);
	WorldState.Add("VillageHasTool", TempVillage->Tools > 0); 
	

	return WorldState;
}

TMap<FString, bool> AStoneGatherer::CreateGoalState()
{
	TMap<FString, bool> GoalState;
	GoalState.Add("HasResource", true);

	return GoalState;
}



