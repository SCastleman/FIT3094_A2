#pragma once
#include "GOAPAction.h"
#include "../VillageCentreActor.h"
#include "FIT3094_A2_Code/StoneGatherer.h"

class DepositStoneAction : public GOAPAction
{
public:
  DepositStoneAction();
  ~DepositStoneAction();

  bool IsActionDone() override;

  virtual bool CheckProceduralPrecondition(AGOAPActor* Agent);
  virtual bool PerformAction(AGOAPActor* Agent);
  virtual bool RequiresInRange();

private:
  virtual void Reset();
  AStoneGatherer* StoneGatherer;
  AVillageCentreActor* VillageCentre;
};
