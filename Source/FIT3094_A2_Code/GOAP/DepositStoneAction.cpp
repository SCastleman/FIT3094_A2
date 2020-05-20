#include "DepositStoneAction.h"

#include "FIT3094_A2_Code/StoneGatherer.h"
#include "Kismet/GameplayStatics.h"

DepositStoneAction::DepositStoneAction()
{
  Reset();
}

DepositStoneAction::~DepositStoneAction()
{
}

bool DepositStoneAction::IsActionDone()
{
  if (StoneGatherer && StoneGatherer->NumResource == 0)
    return true;
  return false;
}

bool DepositStoneAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  StoneGatherer = Cast<AStoneGatherer>(Agent);
  if (!StoneGatherer || StoneGatherer->NumResource != StoneGatherer->MaxResource)
    return false;
  AActor* TempVillage = UGameplayStatics::GetActorOfClass(Agent, AVillageCentreActor::StaticClass());
  VillageCentre = Cast<AVillageCentreActor>(TempVillage);
  if (!VillageCentre)
    return false;
  Target = VillageCentre;
  return true;
}

bool DepositStoneAction::PerformAction(AGOAPActor* Agent)
{
  if (!VillageCentre || !StoneGatherer)
    return false;
  VillageCentre->StoneResources += StoneGatherer->NumResource;
  StoneGatherer->NumResource = 0;
  return true;
}

bool DepositStoneAction::RequiresInRange()
{
  return true;
}

void DepositStoneAction::Reset()
{
  SetInRange(false);
  Target = nullptr;
}





