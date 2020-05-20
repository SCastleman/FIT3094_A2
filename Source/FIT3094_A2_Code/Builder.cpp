// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder.h"


#include "GOAP/BuildAction.h"
#include "GOAP/PickupMaterialsAction.h"

ABuilder::~ABuilder()
{
  Health = 400;
  MaxHealth = 400;
  FoodTrigger = 15;
}

void ABuilder::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PickupMaterialsAction* PickupMaterials = new PickupMaterialsAction();
	PickupMaterials->AddPrecondition("HasResources", false);
	PickupMaterials->AddEffect("HasResources", true);
	BuildAction* NewBuildAction = new BuildAction();
	NewBuildAction->AddPrecondition("HasResources", true);
	NewBuildAction->AddEffect("HasResources", false);
}

TMap<FString, bool> ABuilder::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();
	WorldState.Add("HasResources", (NumWood != 0 && NumStone != 0)) ;
	return WorldState;
}

TMap<FString, bool> ABuilder::CreateGoalState()
{
	TMap<FString, bool> GoalState;
	return GoalState;
}

void ABuilder::OnPlanFailed(TMap<FString, bool> FailedGoalState)
{
}

void ABuilder::OnPlanAborted(GOAPAction* FailedAction)
{
}

void ABuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
