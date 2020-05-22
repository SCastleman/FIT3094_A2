#pragma once

#include "GOAPAction.h"
#include "FIT3094_A2_Code/MineActor.h"
#include "FIT3094_A2_Code/ToolCrafter.h"

class GatherMetalAction : public GOAPAction
{
public:

  bool IsActionDone() override;
  bool CheckProceduralPrecondition(AGOAPActor* Agent) override;
  bool PerformAction(AGOAPActor* Agent) override;
  bool RequiresInRange() override;
private:
  void Reset() override;
  AMineActor* MineActor;
  AToolCrafter* ToolCrafter;
  TArray<AMineActor*> ResourceList;
  AMineActor* TargetMine;
  int64 TargetTime;
  const int64 Timer = 1;
};
