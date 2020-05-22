#pragma once
#include "GOAPAction.h"
#include "FIT3094_A2_Code/ToolCrafter.h"
#include "FIT3094_A2_Code/ForgeActor.h"

class ForgeToolAction : public GOAPAction
{
public:

  bool IsActionDone() override;
  bool CheckProceduralPrecondition(AGOAPActor* Agent) override;
  bool PerformAction(AGOAPActor* Agent) override;
  bool RequiresInRange() override;
  const int64 ToolCost = 7;
private:
  void Reset() override;
  AToolCrafter* ToolCrafter;
  AForgeActor* TargetForge;
  int64 TargetTimer = NULL;
  const int64 Timer = 3;
};
