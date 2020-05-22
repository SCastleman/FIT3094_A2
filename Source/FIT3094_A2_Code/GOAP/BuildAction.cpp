#include "BuildAction.h"

#include "Kismet/GameplayStatics.h"

bool BuildAction::IsActionDone()
{
  if (
    +-Builder->NumWood == 0 && Builder->NumStone == 0
  || (Building->WoodResources == 100 && Building->StoneResources == 100))
    return true;
  return false;
}

bool BuildAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  Builder = Cast<ABuilder>(Agent);
  Building = Cast<ABuildingActor>(UGameplayStatics::GetActorOfClass(Agent->GetWorld(), ABuildingActor::StaticClass()));
  Target = Building;
  if ((Builder->NumStone > 0 || Builder->NumWood > 0) 
    && Building->StoneResources != 100 && Building->WoodResources != 100)
    return true;
  return false;
}

bool BuildAction::PerformAction(AGOAPActor* Agent)
{
  if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
  {
    if (Builder->NumStone > 0 && Building->StoneResources < 100)
    {
    Building->StoneResources += 1;  
    Builder->NumStone -= 1;
    }
    if (Builder->NumWood > 0 && Building->WoodResources < 100)
    {
    Building->WoodResources += 1;
    Builder->NumWood -= 1;
    }
    TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
  }
  return true;
}

bool BuildAction::RequiresInRange()
{
  return true;
}

void BuildAction::Reset()
{
  Target = nullptr;
  SetInRange(false);
  TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
