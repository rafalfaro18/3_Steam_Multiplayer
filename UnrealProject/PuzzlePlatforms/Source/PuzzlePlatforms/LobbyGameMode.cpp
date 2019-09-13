// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer) {
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;

	if (NumberOfPlayers >= 2) {
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ALobbyGameMode::StartGame, 5.0f);
		
	}
}

void ALobbyGameMode::Logout(AController * Exiting) {
	Super::Logout(Exiting);
	--NumberOfPlayers;
}

void ALobbyGameMode::StartGame() {
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	bUseSeamlessTravel = true;

	World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game?listen");
}
