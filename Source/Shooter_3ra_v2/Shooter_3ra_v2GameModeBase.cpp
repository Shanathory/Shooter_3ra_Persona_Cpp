// Copyright Epic Games, Inc. All Rights Reserved.


#include "Shooter_3ra_v2GameModeBase.h"
#include "PlayerCharacter.h"

AShooter_3ra_v2GameModeBase::AShooter_3ra_v2GameModeBase()
{
	// REGION: Indicar que queremos que el GameMode Spawne el BP_ PlayerCharacter que creamos.
	static ConstructorHelpers::FClassFinder<APawn> BP_PlayerCharacter (TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (BP_PlayerCharacter.Class != NULL)
	{
		DefaultPawnClass = BP_PlayerCharacter.Class;  
	}
	// ENDREGION.
}
