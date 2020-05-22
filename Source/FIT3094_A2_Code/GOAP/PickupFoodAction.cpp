#include "PickupFoodAction.h"
#include "AGOAPActor.h"
#include "Kismet/GameplayStatics.h"

bool PickupFoodAction::IsActionDone()
{
  if (Gatherer->Health >= Gatherer->MaxHealth)
    return true;
  return false;
}

bool PickupFoodAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  if (Agent->Health > Agent->FoodTrigger)
    return false;
  //If we do not already have the resources stored then find some
  Gatherer = Agent;
  if (ResourceList.Num() == 0)
  {
    //List of overlaps with other actors we are about to generate
    TArray<AActor*> TempResources;

    //Get all stone actors in the world
    UGameplayStatics::GetAllActorsOfClass(Agent->GetWorld(), AFoodActor::StaticClass(), TempResources);

     // Cast all as trees and add to the ResourceList array
    for (auto Actor : TempResources)
    {
      AFoodActor* ResourcePointer = Cast<AFoodActor>(Actor);
      if (ResourcePointer) ResourceList.Add(ResourcePointer);
    }
  }

  //For each resource available
  AFoodActor* NearestResource = nullptr;
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
    TargetFood = NearestResource;
    return true;
  }

  // If we get to this point we failed
  return false;
}

bool PickupFoodAction::PerformAction(AGOAPActor* Agent)
{
  if (!TargetTime)
    TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
  int64 CurrentTime = FDateTime::UtcNow().ToUnixTimestamp();
  if (CurrentTime >= TargetTime)
  {
    Agent->Health = Agent->MaxHealth;
    TargetFood->Destroy();
  }
  return true;
}

bool PickupFoodAction::RequiresInRange()
{
  return true;
}

void PickupFoodAction::Reset()
{
  ResourceList.Empty();
  Target = nullptr;
  TargetTime = NULL;
  TargetFood = nullptr;
}
