// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../MenuSystem/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadGameMenu();

	UFUNCTION()
	virtual void Host() override;

	UFUNCTION(exec)
	virtual void Join(const FString &ip_addr) override;

	UFUNCTION()
	virtual void ReturnToMainMenu() override;

private:

	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> GameMenuClass;

	class UMainMenu* MainMenu;
};
