// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeGatherer.h"

#include "GOAP/DepositAction.h"
#include "GOAP/GatherTreeAction.h"
#include "GOAP/PickupToolAction.h"
#include "Kismet/GameplayStatics.h"

ATreeGatherer::ATreeGatherer() : AGOAPActor()
{
	NumResource = 0;
	MaxResource = 50;
	Health = 40;
	MaxHealth = 40;
	FoodTrigger = 15;
}

void ATreeGatherer::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PickupToolAction* PickupTool = new PickupToolAction();
	PickupTool->AddPrecondition("HasTool", false);
	PickupTool->AddPrecondition("VillageHasTool", true);
	PickupTool->AddEffect("HasTool", true);
	AvailableActions.Add(PickupTool);
	GatherTreeAction* NewAction = new GatherTreeAction();
	NewAction->AddPrecondition("HasResource", false);
	NewAction->AddPrecondition("HasTool", true);
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

	AVillageCentreActor* TempVillage = Cast<AVillageCentreActor>(UGameplayStatics::GetActorOfClass(this->GetWorld(), AVillageCentreActor::StaticClass()));
	WorldState.Add("VillageHasTool", TempVillage->Tools > 0);
	WorldState.Add("HasResource", NumResource == MaxResource);
	WorldState.Add("HasTool", ToolHealth > 0);

	return WorldState;
}

TMap<FString, bool> ATreeGatherer::CreateGoalState()
{
	TMap<FString, bool> GoalState;
	GoalState.Add("HasResource", true);

	return GoalState;
}



