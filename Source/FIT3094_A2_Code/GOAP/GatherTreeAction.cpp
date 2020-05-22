// Fill out your copyright notice in the Description page of Project Settings.


#include "GatherTreeAction.h"
#include "../TreeGatherer.h"
#include "AGOAPActor.h"
#include "Kismet/GameplayStatics.h"

GatherTreeAction::GatherTreeAction()
{
  Reset();
}

GatherTreeAction::~GatherTreeAction()
{
}

bool GatherTreeAction::IsActionDone()
{
  if (TreeGatherer->NumResource >= TreeGatherer->MaxResource)
    return true;
  return false;
}

bool GatherTreeAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  if (Agent->ToolHealth == 0)
    return false;
  TreeGatherer = Cast<ATreeGatherer>(Agent);
  //If we do not already have the resources stored then find some
  if (ResourceList.Num() == 0)
  {
    //List of overlaps with other actors we are about to generate
    TArray<AActor*> TempResources;

    //Get all stone actors in the world
    UGameplayStatics::GetAllActorsOfClass(Agent->GetWorld(), ATreeActor::StaticClass(), TempResources);

     // Cast all as trees and add to the ResourceList array
    for (auto Actor : TempResources)
    {
      ATreeActor* ResourcePointer = Cast<ATreeActor>(Actor);
      if (ResourcePointer) ResourceList.Add(ResourcePointer);
    }
  }

  //For each resource available
  ATreeActor* NearestResource = nullptr;
  for (auto Resource : ResourceList)
  {
    //If we already have a resource
    if (NearestResource)
    {
      //Check distance from current location to current resource and the new resource
      if (FVector::Dist(Resource->GetActorLocation(), Agent->GetActorLocation()) <
        FVector::Dist(NearestResource->GetActorLocation(), Agent->GetActorLocation()))
          //if it is shorter we have a new closest resource
          NearestResource = Resource;
    }
    // if nearest is null we have a new shortest
    else NearestResource = Resource;
  }
  //If the nearest resource is not null
  if (NearestResource)
  {
    // Set the actions target to be this resource and return true
    Target = NearestResource;
    TargetTree = NearestResource;
    return true;
  }

  // If we get to this point we failed
  return false;
}

bool GatherTreeAction::PerformAction(AGOAPActor* Agent)
{
  if (!TargetTree || Agent->ToolHealth == 0)
    return false;
  if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
  {
    TargetTree->WoodResources -= 1;
    TreeGatherer->NumResource += 1;
    TreeGatherer->ToolHealth -= 1;

    TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
  }

  return true;
}

bool GatherTreeAction::RequiresInRange()
{
  return true;
}

void GatherTreeAction::Reset()
{
  SetInRange(false);
  Target = nullptr;
  TargetTree = nullptr;
  TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}




