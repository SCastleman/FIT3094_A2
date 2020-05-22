#include "PickupMaterialsAction.h"


#include "FIT3094_A2_Code/VillageCentreActor.h"
#include "Kismet/GameplayStatics.h"

bool PickupMaterialsAction::IsActionDone()
{
  if (Builder && Builder->NumStone == Builder->MaxStone && Builder->NumWood == Builder->MaxWood)
    return true;
  return false;
}

bool PickupMaterialsAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
  Builder = Cast<ABuilder>(Agent);
  if (Builder->NumStone == Builder->MaxStone && Builder->NumWood == Builder->MaxWood)
    return false;
  VillageCentre = Cast<AVillageCentreActor>(UGameplayStatics::GetActorOfClass(Agent->GetWorld(), AVillageCentreActor::StaticClass()));
  Target = VillageCentre;
  return true;
}

bool PickupMaterialsAction::PerformAction(AGOAPActor* Agent)
{
  // Only pick up resources if it would be holding the maximum amount it can carry
  if (VillageCentre->WoodResources >= Builder->MaxWood - Builder->NumWood
    && VillageCentre->StoneResources >= Builder->MaxStone - Builder->NumStone)
  {
    VillageCentre->WoodResources -= (Builder->MaxWood - Builder->NumWood);
    VillageCentre->StoneResources -= (Builder->MaxStone - Builder->NumStone);
    Builder->NumStone = Builder->MaxStone;
    Builder->NumWood = Builder->MaxWood;
    return true;
  }
  return false;
}

bool PickupMaterialsAction::RequiresInRange()
{
  return true;
}

void PickupMaterialsAction::Reset()
{
  SetInRange(false);
}
