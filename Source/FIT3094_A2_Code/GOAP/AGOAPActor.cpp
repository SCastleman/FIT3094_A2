// Fill out your copyright notice in the Description page of Project Settings.


#include "AGOAPActor.h"
#include "GOAPPlanner.h"

AGOAPActor::AGOAPActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ActionStateMachine = new StateMachine<Actor_States, AGOAPActor>(this, State_Nothing);
	ActionStateMachine->RegisterState(State_Idle, &AGOAPActor::OnIdleEnter, &AGOAPActor::OnIdleUpdate, &AGOAPActor::OnIdleExit);
	ActionStateMachine->RegisterState(State_Action, &AGOAPActor::OnActionEnter, &AGOAPActor::OnActionUpdate, &AGOAPActor::OnActionExit);
	ActionStateMachine->RegisterState(State_Move, &AGOAPActor::OnMoveEnter, &AGOAPActor::OnMoveUpdate, &AGOAPActor::OnMoveExit);
	ActionStateMachine->ChangeState(State_Idle);

}

AGOAPActor::~AGOAPActor()
{
}

void AGOAPActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGOAPActor::DecreaseHealth, 2.0f, true, 2.0f);

}

void AGOAPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ActionStateMachine->Tick(DeltaTime);
}

void AGOAPActor::DecreaseHealth()
{
		// Decrease health by one and if 0 then destroy object
	Health--;

	if(Health <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}

void AGOAPActor::OnIdleEnter()
{
}

void AGOAPActor::OnIdleUpdate(float DeltaTime)
{
	// In this state we are planning our next move
	// Get world state
	TMap<FString, bool> WorldState = GetWorldState();
	//Get desired goal state
	TMap<FString, bool> GoalState = CreateGoalState();

	//Attempt to make a plan anc check success
	if (GOAPPlanner::Plan(this, AvailableActions, CurrentActions, WorldState, GoalState))
	{
		UE_LOG(LogTemp, Warning, TEXT("GOAP AGENT CLASS: Plan has been found"));
		ActionStateMachine->ChangeState(State_Action);
	}
	else UE_LOG(LogTemp, Warning, TEXT("GOAP AGENT CLASS: No plan found!"));
}

void AGOAPActor::OnIdleExit()
{

}

void AGOAPActor::OnMoveEnter()
{
	//Entering into move state check to ensure we can move. If no actions return to idle immediately
	if (CurrentActions.IsEmpty())
	{
		ActionStateMachine->ChangeState(State_Idle);
		return;
	}

	// If current action requires an in range check AND the target is null. Return to planning
	GOAPAction* CurrentAction = *CurrentActions.Peek();
	if (CurrentAction->RequiresInRange() && CurrentAction->Target == nullptr)
		ActionStateMachine->ChangeState(State_Idle);
}

void AGOAPActor::OnMoveUpdate(float DeltaTime)
{
	GOAPAction* CurrentAction = *CurrentActions.Peek();

	//This is a direct movement example. For assignments you need to use pathfinding/grid based movement here
	FVector Direction = CurrentAction->Target->GetActorLocation() - GetActorLocation();
	Direction.Normalize();

	//Update position based on direction and move speed
	FVector NewPos = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	//If we are close enough to target then snap to it
	if (FVector::Dist(NewPos, CurrentAction->Target->GetActorLocation()) <= Tolerance)
	{
		NewPos = CurrentAction->Target->GetActorLocation();
		//We are now in range of target so set it to true
		CurrentAction->SetInRange(true);
		//Moving is done transition to action state
		ActionStateMachine->ChangeState(State_Action);
	}

	SetActorLocation(NewPos);
}

void AGOAPActor::OnMoveExit()
{
}

void AGOAPActor::OnActionEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("ActionEnter triggered"));
}

void AGOAPActor::OnActionUpdate(float DeltaTime)
{
	GOAPAction* CurrentAction = *CurrentActions.Peek();
	if (CurrentAction->IsActionDone())
		//We are done with the current action
		CurrentActions.Dequeue(CurrentAction);

	if (!CurrentActions.IsEmpty())
	{
		//Get the top of the queue
		CurrentAction = *CurrentActions.Peek();

		// Check to see if we must be in range for action. If no range requirement needed, return true.
		// If range requirement doesn't exist, check to see we are in range.
		bool InRange = CurrentAction->RequiresInRange() ? CurrentAction->IsInRange() : true;

		// If we're in range, attempt action
		if (InRange)
		{
			// Attempt to perform action. Can fail so we store result
			bool IsActionSuccessful = CurrentAction->PerformAction(this);
			if (!IsActionSuccessful)
			{
				ActionStateMachine->ChangeState(State_Idle);
				OnPlanAborted(CurrentAction);
			}
		} else 
		{
				//At this point we have a valid action but aren't in range. Commence movement
			ActionStateMachine->ChangeState(State_Move);
		}
	} else
	{
		ActionStateMachine->ChangeState(State_Idle);
	}
}

void AGOAPActor::OnActionExit()
{
}

TMap<FString, bool> AGOAPActor::GetWorldState()
{
	TMap<FString, bool> CurrentWorldState;
	return CurrentWorldState;
}

TMap<FString, bool> AGOAPActor::CreateGoalState()
{

	TMap<FString, bool> GoalState;
	return GoalState;
}

void AGOAPActor::OnPlanFailed(TMap<FString, bool> FailedGoalState)
{
}

void AGOAPActor::OnPlanAborted(GOAPAction* FailedAction)
{
}





