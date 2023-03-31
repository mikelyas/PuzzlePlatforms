// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "TimerManager.h"

#include "PuzzlePlatformGameInstance.h"


ALobbyGameMode::ALobbyGameMode()
{
	CurrentPlayers = 0;
	MaxPlayers = 2;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	CurrentPlayers++;
	if (CurrentPlayers == MaxPlayers)
	{
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ALobbyGameMode::StartGame, 5.0f);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	CurrentPlayers--;
}

void ALobbyGameMode::StartGame()
{
	UPuzzlePlatformGameInstance* GameInst = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());
	if (GameInst == nullptr) return;
	GameInst->StartSession();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}