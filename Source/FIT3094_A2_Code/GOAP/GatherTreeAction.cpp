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
  if (ResourcesGathered >= ResourcesToGather) return true;
  return false;
}

bool GatherTreeAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  //If we do not already have the resources stored then find some
  if (ResourceList.Num() == 0)
  {
    //List of overlaps with other actors we are about to generate
    TArray<AActor*> TempResources;

    //Get all stone actors in the world
    UGameplayStatics::GetAllActorsOfClass(Agent->GetWorld(), ATreeActor::StaticClass(), TempResources);

     // Cast all as stone and add to the ResourceList array
    for (auto Actor : TempResources)
    {
      ATreeActor* ResourcePointer = Cast<ATreeActor>(Actor);
      if (ResourcePointer) ResourceList.Add(ResourcePointer);
    }
  }

  //Find the nearest resource. Start with null
  ATreeActor* NearestResource = nullptr;
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

bool GatherTreeAction::PerformAction(AGOAPActor* Agent)
{
  ATreeActor* Resource = Cast<ATreeActor>(Target);
  ATreeGatherer* Gatherer = Cast<ATreeGatherer>(Agent);
  if (!Resource || !Gatherer) return false;
  if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
  {
    ResourcesGathered += 1;
    Resource->WoodResources -= 1;
    Gatherer->NumResource += 1;

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
  ResourcesGathered = 0;
  TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}




