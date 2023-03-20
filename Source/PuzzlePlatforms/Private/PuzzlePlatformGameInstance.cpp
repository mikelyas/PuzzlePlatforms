// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "../MenuSystem/MainMenu.h"
#include "../MenuSystem/MenuWidget.h"


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MainMenuClass.Class != nullptr)) return;

	MenuClass = MainMenuClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	if (!ensure(GameMenuBPClass.Class != nullptr)) return;

	GameMenuClass = GameMenuBPClass.Class;

	UE_LOG(LogTemp, Warning, TEXT("Found widget %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Init"));
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	MainMenu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->Setup();

	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadGameMenu()
{
	if (!ensure(GameMenuClass != nullptr)) return;

	UMenuWidget* GameMenu = CreateWidget<UMenuWidget>(this, GameMenuClass);
	if (!ensure(GameMenu != nullptr)) return;

	GameMenu->Setup();

	GameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::Host()
{
	if (MainMenu)
	{
		MainMenu->TearDown();
	}

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString &ip_addr)
{
	if (MainMenu)
	{
		MainMenu->TearDown();
	}

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *ip_addr));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(ip_addr, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::ReturnToMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}