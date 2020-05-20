// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Queue.h"
#include "CoreMinimal.h"

class AGOAPActor;
class GOAPAction;

//We use a basic struct called a GOAPNode when planning
//This functions fairly similar to our GridNode from previous weeks
//These are used when building the search graph in the planner
struct GOAPNode
{
	//Where did we come from?
	GOAPNode* Parent;

	//The cost so far to reach this point
	float RunningCost;

	//The current state of the world when reaching this point
	//This will be the world state with all previous effects applied
	TMap<FString, bool> State;

	//A node is associated with an action. This is that action
	GOAPAction* Action;
};
/**
 * The GOAPPlanner class itself. We actually only use it as a static class.
 * This could be improved by making it not static and implementing an object pool for nodes. As of now the method of
 * handling GOAPNodes is pretty rudimentary and can be quite resource intensive.
 */
class FIT3094_A2_CODE_API GOAPPlanner
{
public:
	GOAPPlanner();
	~GOAPPlanner();

	// The function called to generate the action plan
	// The agent calling it passed itself through along with its available actions and action queue.
	// NOTE: We are using C++ so these MUST be references or pointers, otherwise it is pass-by-copy. Not an issue with
	// C# or other non-C languages
	static bool Plan(AGOAPActor* Agent, const TSet<GOAPAction*>& AvailableActions, TQueue<GOAPAction*>& PlannedActions,
		TMap<FString, bool> WorldState, TMap<FString, bool> GoalState);

protected:

	// Builds out the node graph until it exhausts all possible paths
	// uses a combination of A* and brute force to do this. Could be optimised
	// Calls itself recursively to build out nodes in the graph and find goals
	// again this is not well optimised and should be used carefully
	static bool BuildGraphRecursive(TArray<GOAPNode*>& AllNodes, GOAPNode* Parent, TArray<GOAPNode*>& GoalNodes,
		const TSet<GOAPAction*>& AvailableActions, TMap<FString, bool>& GoalState);

	static TSet<GOAPAction*> CreateActionSubset(const TSet<GOAPAction*>& AvailableActions, GOAPAction* RemoveAction);
	// Function used for creating a subset of actions with an action removed. Used to reduce available actions as more are
	// checked off the list (aka don't call same action twice). Do note this could cause issues if you want to do that
	static bool CheckConditionsInState(TMap<FString, bool>& Conditions, TMap<FString, bool>& State);

	// Combine a current state with the changes (aka effects) of an action
	static TMap<FString, bool> PopulateNewState(const TMap<FString, bool>& CurrentState, TMap<FString, bool>& Changes);
};
