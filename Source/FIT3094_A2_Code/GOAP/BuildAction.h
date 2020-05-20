#pragma once
#include "GOAPAction.h"
#include "FIT3094_A2_Code/Builder.h"
#include "FIT3094_A2_Code/BuildingActor.h"

class BuildAction : public GOAPAction
{
public:
  bool IsActionDone() override;
  bool CheckProceduralPrecondition(AGOAPActor* Agent) override;
  bool PerformAction(AGOAPActor* Agent) override;
  bool RequiresInRange() override;
private:
  void Reset() override;
  ABuilder* Builder;
  ABuildingActor* Building;
  const int8 Timer = 1;
  int TargetTime;
};
