// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AMovingPlatform();

	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	float Speed;

	UPROPERTY(EditInstanceOnly, meta = (MakeEditWidget = true))
	FVector TargetPosition;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:

	virtual void Tick(float DeltaTime) override;

private:

	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
	
};
