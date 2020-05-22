#pragma once
#include "GOAPAction.h"
#include "FIT3094_A2_Code/FoodActor.h"

class PickupFoodAction : public GOAPAction
{
public:

  bool IsActionDone() override;
  bool CheckProceduralPrecondition(AGOAPActor* Agent) override;
  bool PerformAction(AGOAPActor* Agent) override;
  bool RequiresInRange() override;
private:
  TArray<AFoodActor*> ResourceList;
  AFoodActor* TargetFood;
  int64 TargetTime = NULL;
  const int64 Timer = 2;
  void Reset() override;
  AGOAPActor* Gatherer;
};
