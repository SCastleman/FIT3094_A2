// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolCrafter.h"


#include "GOAP/DepositAction.h"
#include "GOAP/ForgeToolAction.h"
#include "GOAP/GatherMetalAction.h"

AToolCrafter::AToolCrafter() : AGOAPActor()
{
  // NumResource for ToolCrafter refers to the number of 
  NumResource = 0;
  // MaxResource for the ToolCrafter is 0 so DepositAction always triggers. MaxMetal defines the max metal it can hold.
  MaxResource = 0;
  Health = 80;
  MaxHealth = 80;
  FoodTrigger = 30;
}

void AToolCrafter::BeginPlay()
{
  Super::BeginPlay();
  PrimaryActorTick.bCanEverTick = true;
  GatherMetalAction* GatherMetal = new GatherMetalAction();
  GatherMetal->AddPrecondition("HasResource", false);
  GatherMetal->AddPrecondition("HasTool", false);
  GatherMetal->AddEffect("HasResource", true);
  AvailableActions.Add(GatherMetal);
  ForgeToolAction* ForgeTool = new ForgeToolAction();
  ForgeTool->AddPrecondition("HasResource", true);
  ForgeTool->AddEffect("HasResource", false);
  ForgeTool->AddEffect("HasTool", true);
  AvailableActions.Add(ForgeTool);
  DepositAction* NewDepositAction = new DepositAction();
  NewDepositAction->AddPrecondition("HasTool", true);
  NewDepositAction->AddEffect("HasTool", false);
  AvailableActions.Add(NewDepositAction);
}

void AToolCrafter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

TMap<FString, bool> AToolCrafter::GetWorldState()
{
  TMap<FString, bool> WorldState = Super::GetWorldState();
  WorldState.Add("HasResource", NumMetal == MaxMetal);
  WorldState.Add("HasTool", NumResource > 0);
  return WorldState;
}

TMap<FString, bool> AToolCrafter::CreateGoalState()
{
  TMap<FString, bool> GoalState;
  GoalState.Add("HasResource", true);
  return GoalState;
}




