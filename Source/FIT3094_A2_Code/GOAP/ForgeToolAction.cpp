#include "ForgeToolAction.h"


#include "FIT3094_A2_Code/ForgeActor.h"
#include "Kismet/GameplayStatics.h"

bool ForgeToolAction::IsActionDone()
{
  if (TargetForge->MetalResources < 7 && ToolCrafter->NumResource >= 1)
    return true;
  return false;
}

bool ForgeToolAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  ToolCrafter = Cast<AToolCrafter>(Agent);
  Target = UGameplayStatics::GetActorOfClass(Agent->GetWorld(), AForgeActor::StaticClass());
  TargetForge = Cast<AForgeActor>(Target);
  if (ToolCrafter->NumMetal >= ToolCost)
    return true;
  return false;
}

bool ForgeToolAction::PerformAction(AGOAPActor* Agent)
{
  if (ToolCrafter->NumMetal != 0)
  {
    TargetForge->MetalResources = ToolCrafter->NumMetal;
    ToolCrafter->NumMetal = 0;
  }
  if (!TargetTimer)
    TargetTimer = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
  else if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTimer)
  {
    ToolCrafter->NumResource += 1;
    TargetForge->MetalResources -= ToolCost;
  }
  return true;
}

bool ForgeToolAction::RequiresInRange()
{
  return true;
}

void ForgeToolAction::Reset()
{
  
}
