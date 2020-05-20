// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "StateMachine.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "AGOAPActor.generated.h"

/**
 * 
 */
UCLASS()
class FIT3094_A2_CODE_API AGOAPActor : public AActor
{
	GENERATED_BODY()
public:
	// State Machine Valid States
	// Te4chnically Nothing is not valid, only used for initialisation
	enum Actor_States
	{
		State_Nothing,
		State_Idle,
		State_Move,
		State_Action
	};

	// Variables for handling movement
	const float Tolerance = 20;
	float MoveSpeed = 150.0f;

	FTimerHandle TimerHandle;

	//Starting/maximum health for actor
	int Health;
	//Health level at which to seek food
	int FoodTrigger;

	//Sets default values for this actor's properties
	AGOAPActor();
	~AGOAPActor();

protected:
	StateMachine<Actor_States, AGOAPActor>* ActionStateMachine;

	// A list of all available actions this Agent can do
	TSet<GOAPAction*> AvailableActions;
	TQueue<GOAPAction*> CurrentActions;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// State Machine Functions
	void OnIdleEnter();
	void OnIdleUpdate(float DeltaTime);
	void OnIdleExit();

	
	void OnMoveEnter();
	void OnMoveUpdate(float DeltaTime);
	void OnMoveExit();

	void OnActionEnter();
	void OnActionUpdate(float DeltaTime);
	void OnActionExit();


	void DecreaseHealth();
	//Function for getting the current world state. This is virtual as it should be overriden by child agents as they will
	//have different information
	virtual TMap<FString, bool> GetWorldState();
	//Create a goal state we want to achieve. We could have multiple and pick one
	virtual TMap<FString, bool> CreateGoalState();
	//A plan was unable to be found. Handle this behaviour
	virtual void OnPlanFailed(TMap<FString, bool> FailedGoalState);
	//A plan was aborted midway. The provided action failed to execute. Handle this in some way
	virtual void OnPlanAborted(GOAPAction* FailedAction);

public:
	//Called every frame
	virtual void Tick(float DeltaTime) override;
};
