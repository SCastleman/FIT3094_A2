#pragma once
#include "GOAPAction.h"
#include "../VillageCentreActor.h"
#include "FIT3094_A2_Code/StoneGatherer.h"

class DepositAction : public GOAPAction
{
public:
  DepositAction();
  ~DepositAction();

  bool IsActionDone() override;

  virtual bool CheckProceduralPrecondition(AGOAPActor* Agent);
  virtual bool PerformAction(AGOAPActor* Agent);
  virtual bool RequiresInRange();

private:

  int* TargetResources;
  virtual void Reset();
  AVillageCentreActor* VillageCentre;
};
