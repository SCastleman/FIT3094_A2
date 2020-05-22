// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//Forward declaration of the GOAP actor. Include it in CPP file
//This avoids dependency loops
class AGOAPActor;
/**
 * 
 */

class FIT3094_A2_CODE_API GOAPAction
{
public:

	//List of conditions required for this action to be valid
	TMap<FString, bool> Preconditions;
	// Changes this action has on the world
	TMap<FString, bool> Effects;

	// The cost of the action
	// All actions have a cost associated with them
	// You can change this at run time if needed
	float ActionCost;

	//Often actors will work on a target
	// We store a generic actor as the target here
	// sub classes can cast this as needed
	AActor* Target;

	//Constructor and destructor
	GOAPAction();
	~GOAPAction();

	//Reset the action to its base state
	void DoReset();

	//Adding and removing preconditions
	void AddPrecondition(FString Name, bool State);
	void RemovePrecondition(FString Name);

	//Adding and removing effects
	void AddEffect(FString Name, bool State);
	void RemoveEffect(FString Name);
	// Set and check whether or not action is within range
	bool IsInRange() const {return InRange;}
	void SetInRange(const bool Range) {InRange = Range;}

	//Pure virtual functions that child classes MUST implement
	//Whether or not an action has finished executing
	virtual bool IsActionDone() = 0;
	//Check procedural preconditions at runtime. Provided an agent
	virtual bool CheckProceduralPrecondition(AGOAPActor* Agent) = 0;

	
	//Actually perform the action. Returns true unless action can no longer be completed. Called each frame until done.
	virtual bool PerformAction(AGOAPActor* Agent) = 0;
	//Some actions can be executed anywhere. Others need specific spots
	virtual bool RequiresInRange() = 0;

private:
	bool InRange;

	//Do Reset above handles calling this.
	//Subclasses can handle their own additional reset requirements here
	virtual void Reset() = 0;
};
