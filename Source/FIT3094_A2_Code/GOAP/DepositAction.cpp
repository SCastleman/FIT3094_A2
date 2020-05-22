#include "DepositAction.h"

#include "FIT3094_A2_Code/StoneGatherer.h"
#include "FIT3094_A2_Code/ToolCrafter.h"
#include "FIT3094_A2_Code/TreeGatherer.h"
#include "Kismet/GameplayStatics.h"

DepositAction::DepositAction()
{
  Reset();
}

DepositAction::~DepositAction()
{
}

bool DepositAction::IsActionDone()
{
  if (*TargetResources == 0)
    return true;
  return false;
}

bool DepositAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  TargetResources = &Agent->NumResource;
  if (Agent->NumResource < Agent->MaxResource)
    return false;
  AActor* TempVillage = UGameplayStatics::GetActorOfClass(Agent, AVillageCentreActor::StaticClass());
  VillageCentre = Cast<AVillageCentreActor>(TempVillage);
  if (!VillageCentre)
    return false;
  Target = VillageCentre;
  return true;
}

bool DepositAction::PerformAction(AGOAPActor* Agent)
{
  if (!VillageCentre)
    return false;

  if (Cast<AStoneGatherer>(Agent))
    VillageCentre->StoneResources += Agent->NumResource;
  else if (Cast<ATreeGatherer>(Agent))
    VillageCentre->WoodResources += Agent->NumResource;
  else if (Cast<AToolCrafter>(Agent))
    VillageCentre->Tools += Agent->NumResource;
  else // If the cast fails for some reason the action should also fail
    return false;

  *TargetResources = 0;
  return true;
}

bool DepositAction::RequiresInRange()
{
  return true;
}

void DepositAction::Reset()
{
  SetInRange(false);
  Target = nullptr;
  TargetResources = nullptr;
}





