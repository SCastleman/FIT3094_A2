#include "PickupToolAction.h"
#include "AGOAPActor.h"
#include "Kismet/GameplayStatics.h"


bool PickupToolAction::IsActionDone()
{
  if (*AgentToolHealth > 0)
    return true;
  return false;
}

bool PickupToolAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  VillageCenter = Cast<AVillageCentreActor>(UGameplayStatics::GetActorOfClass(Agent->GetWorld(), AVillageCentreActor::StaticClass()));
  Target = VillageCenter;
  AgentToolHealth = &Agent->ToolHealth;
  if (Agent->ToolHealth == 0 && VillageCenter->Tools > 0)
    return true;
  return false;
}

bool PickupToolAction::PerformAction(AGOAPActor* Agent)
{
  if (VillageCenter->Tools == 0)
    return false;
  VillageCenter->Tools--;
  Agent->ToolHealth += 75;
  return true;
}

bool PickupToolAction::RequiresInRange()
{
  return true;
}

void PickupToolAction::Reset()
{
  SetInRange(false);
  AgentToolHealth = nullptr;
}
