// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"


ALobbyGameMode::ALobbyGameMode()
{
	CurrentPlayers = 0;
	MaxPlayers = 3;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	CurrentPlayers++;
	if (CurrentPlayers == MaxPlayers)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Maps/Game?listen");
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	CurrentPlayers--;
}