// Fill out your copyright notice in the Description page of Project Settings.


#include "GatherStoneAction.h"
#include "../StoneGatherer.h"
#include "AGOAPActor.h"
#include "Kismet/GameplayStatics.h"

GatherStoneAction::GatherStoneAction()
{
  Reset();
}

GatherStoneAction::~GatherStoneAction()
{
}

bool GatherStoneAction::IsActionDone()
{
  if (ResourcesGathered >= ResourcesToGather) 
    return true;
  return false;
}

bool GatherStoneAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  //If we do not already have the resources stored then find some
  if (ResourceList.Num() == 0)
  {
    //List of overlaps with other actors we are about to generate
    TArray<AActor*> TempResources;

    //Get all stone actors in the world
    UGameplayStatics::GetAllActorsOfClass(Agent->GetWorld(), AStoneActor::StaticClass(), TempResources);

     // Cast all as stone and add to the ResourceList array
    for (auto Actor : TempResources)
    {
      AStoneActor* ResourcePointer = Cast<AStoneActor>(Actor);
      if (ResourcePointer) ResourceList.Add(ResourcePointer);
    }
  }

  //Find the nearest resource. Start with null
  AStoneActor* NearestResource = nullptr;
  //For each resource available
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
    return true;
  }

  // If we get to this point we failed
  return false;
}

bool GatherStoneAction::PerformAction(AGOAPActor* Agent)
{
  AStoneActor* Resource = Cast<AStoneActor>(Target);
  AStoneGatherer* Gatherer = Cast<AStoneGatherer>(Agent);
  if (!Resource || !Gatherer) return false;
  if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
  {
    ResourcesGathered += 1;
    Resource->StoneResources -= 1;
    Gatherer->NumResource += 1;

    TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
  }

  return true;
}

bool GatherStoneAction::RequiresInRange()
{
  return true;
}

void GatherStoneAction::Reset()
{
  SetInRange(false);
  Target = nullptr;
  ResourcesGathered = 0;
  TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}




