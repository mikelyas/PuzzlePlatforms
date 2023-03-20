// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Speed = 10.0f;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetPosition);
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers)
	{
		ActiveTriggers--;
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers)
	{
		if (HasAuthority())
		{
			FVector ActorLocation = GetActorLocation();
			if ((ActorLocation - GlobalStartLocation).Size() >= (GlobalTargetLocation - GlobalStartLocation).Size())
			{
				FVector tmp = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = tmp;
			}
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			ActorLocation += Speed * DeltaTime * Direction;
			SetActorLocation(ActorLocation);
		}
	}
}
