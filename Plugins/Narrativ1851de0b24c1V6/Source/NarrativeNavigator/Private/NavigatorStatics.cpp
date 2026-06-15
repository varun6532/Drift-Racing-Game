// Copyright Narrative Tools 2025. 


#include "NavigatorStatics.h"
#include "NavigationMarkerComponent.h"
#include "GameFramework/Actor.h"
#include <GameplayTagContainer.h>

UNavigationMarkerComponent* UNavigatorStatics::AddNavigationMarkerToActor(class AActor* ActorToMark, const FNavigationMarkerSettings& MarkerSettings, const FGameplayTagContainer& InMarkerDomain)
{
	if (ActorToMark)
	{
		UNavigationMarkerComponent* Marker = Cast<UNavigationMarkerComponent>(ActorToMark->AddComponentByClass(UNavigationMarkerComponent::StaticClass(), false, FTransform(), false));
		if (Marker)
		{
			Marker->DefaultMarkerSettings = MarkerSettings;
			Marker->SetDomain(InMarkerDomain);

			return Marker;
		}
	}

	return nullptr;
}
