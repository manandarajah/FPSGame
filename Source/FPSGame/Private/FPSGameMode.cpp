// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "FPSGameState.h"
#include <Engine/World.h>

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn) {
		if (SpectatingViewpoint) {

			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpoint, ReturnedActors);

			if (ReturnedActors.Num() > 0) {
				AActor* NewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++) {
					APlayerController* PC = It->Get();

					if (PC) {
						PC->SetViewTargetWithBlend(NewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}

			}
		}

		else {
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpoint is nullptr. Please update GameMode clas with valid subclass. Cannot change spectating view target"))
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();

	if (GS) {
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
