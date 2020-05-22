// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "../TreeActor.h"
#include "FIT3094_A2_Code/TreeGatherer.h"

/**
 * 
 */
class FIT3094_A2_CODE_API GatherTreeAction : public GOAPAction
{
public:
	GatherTreeAction();
	~GatherTreeAction();

	//pure virtual functions that child classes MUST implement.
	//Whether or not an action has finished executing
	bool IsActionDone() override;

	// Check procedural preconditions at runtime. Provided an agent
	virtual bool CheckProceduralPrecondition(AGOAPActor* Agent);

	// Actually performs the action
	// Returns true unless the action can no longer be completed
	// this is called each frame until the action is done
	virtual bool PerformAction(AGOAPActor* Agent);

	//Whether or not the action requires something in range. Some actions can be executed anywhere, others need specific spots
	virtual bool RequiresInRange();

private:
	//Do reset above handles calling this. Sub classes can handle their own additional requirements here
	virtual void Reset();

	// An array of all known resources. This is stored so that we do not waste resources doing constant collision checks.
	// We could also have this linked with a world controller for easier access (assignment 1)
	TArray<ATreeActor*> ResourceList;

	// The gatherer associated with this action
	ATreeGatherer* TreeGatherer;

	// The tree this actor is cutting down
	ATreeActor* TargetTree;
	
	// The timer we use for determining when to collect resources (Timer based)
	int64 TargetTime;

	// How often should the timer increment. 1 = 1 second
	const int64 Timer = 1;
};
