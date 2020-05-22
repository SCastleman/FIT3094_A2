#include "GatherMetalAction.h"

#include "FIT3094_A2_Code/MineActor.h"
#include "Kismet/GameplayStatics.h"

bool GatherMetalAction::IsActionDone()
{
  if (ToolCrafter->NumMetal >= ToolCrafter->MaxMetal)
    return true;
  return false;
}

bool GatherMetalAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  ToolCrafter = Cast<AToolCrafter>(Agent);
   //If we do not already have the resources stored then find some
   if (ResourceList.Num() == 0)
   {
     //List of overlaps with other actors we are about to generate
     TArray<AActor*> TempResources;
 
     //Get all stone actors in the world
     UGameplayStatics::GetAllActorsOfClass(Agent->GetWorld(), AMineActor::StaticClass(), TempResources);
 
      // Cast all as trees and add to the ResourceList array
     for (auto Actor : TempResources)
     {
       AMineActor* ResourcePointer = Cast<AMineActor>(Actor);
       if (ResourcePointer) ResourceList.Add(ResourcePointer);
     }
   }
 
   //For each resource available
   AMineActor* NearestResource = nullptr;
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
     TargetMine = NearestResource;
     return true;
   }
 
   // If we get to this point we failed
   return false;
}

bool GatherMetalAction::PerformAction(AGOAPActor* Agent)
{
  if (!TargetMine)
    return false;
  if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
  {
    TargetMine->MetalResources -= 1;
    ToolCrafter->NumMetal += 1;
    TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
  }
  return true;
}

bool GatherMetalAction::RequiresInRange()
{
  return true;
}

void GatherMetalAction::Reset()
{
  SetInRange(false);
  Target = nullptr;
  TargetMine = nullptr;
  TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
