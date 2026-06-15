// Copyright Narrative Tools 2025. 

#include "NavigationMarkerComponent.h"
#include "NarrativeNavigationComponent.h"
#include <UObject/ConstructorHelpers.h>
#include <Engine/Texture2D.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include "NavigatorGameplayTags.h"

#define LOCTEXT_NAMESPACE "NavigationMarker"


UNavigationMarkerComponent::UNavigationMarkerComponent()
{

	DefaultMarkerSettings.bOverride_LocationDisplayName = true;
	DefaultMarkerSettings.bOverride_bShowActorRotation = true;
	DefaultMarkerSettings.bOverride_LocationIcon = true;
	DefaultMarkerSettings.bOverride_IconTint = true;
	DefaultMarkerSettings.bOverride_IconSize = true;
	DefaultMarkerSettings.bOverride_IconOffset = true;

	//The default UI that ships with navigator really benefits from a couple of overrides! Compass icons and screen space markers should be a little bigger
	CompassOverrideSettings.bOverride_IconSize = true;
	CompassOverrideSettings.IconSize = FVector2D(40.f, 40.f);
	ScreenspaceOverrideSettings.bOverride_IconSize = true;
	ScreenspaceOverrideSettings.IconSize = FVector2D(50.f, 50.f);

	DefaultMarkerSettings.LocationDisplayName = LOCTEXT("NavigatorLocationDisplayName", "Location Marker");
	DefaultMarkerSettings.LocationIcon = nullptr;
	DefaultMarkerSettings.IconTint = FLinearColor(1.f, 1.f, 1.f);
	DefaultMarkerSettings.IconSize = FVector2D(20.f, 20.f);

	MarkerStartFadeOutDistance = 13500.f;
	MarkerStartFadeInDistance = 15000.f;
	bPinToMapEdge = false;

	auto LocationIconFinder = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Script/Engine.Texture2D'/NarrativeNavigator/Assets/Icons/T_Marker_Default.T_Marker_Default'"));
	if (LocationIconFinder.Succeeded())
	{
		DefaultMarkerSettings.LocationIcon = LocationIconFinder.Object;
	}

	//Markers should show up on these navigators by default - screen space shouldnt be default 
	MarkerDomain.AddTag(FNavigatorGameplayTags::Get().NavigatorTypes_Compass);
	MarkerDomain.AddTag(FNavigatorGameplayTags::Get().NavigatorTypes_Minimap);
	MarkerDomain.AddTag(FNavigatorGameplayTags::Get().NavigatorTypes_Worldmap);

	SetAutoActivate(true);
}


void UNavigationMarkerComponent::BeginPlay()
{
	Super::BeginPlay();

	RegisterMarker();
}

void UNavigationMarkerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	RemoveMarker();
}

void UNavigationMarkerComponent::RegisterMarker()
{
	//Because navigation is a local thing, we can safely use the local player controller
	for (FConstPlayerControllerIterator Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		if (APlayerController* PC = Iter->Get())
		{
			if (PC->IsLocalController())
			{
				if (UNarrativeNavigationComponent* NavComp = Cast<UNarrativeNavigationComponent>(PC->GetComponentByClass(UNarrativeNavigationComponent::StaticClass())))
				{
					NavComp->AddMarker(this);
				}
			}
		}
	}
}

void UNavigationMarkerComponent::RemoveMarker()
{
	//Because navigation is a local thing, we can safely use the local player controller
	for (FConstPlayerControllerIterator Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		if (APlayerController* PC = Iter->Get())
		{
			if (PC->IsLocalController())
			{
				if (UNarrativeNavigationComponent* NavComp = Cast<UNarrativeNavigationComponent>(PC->GetComponentByClass(UNarrativeNavigationComponent::StaticClass())))
				{
					NavComp->RemoveMarker(this);
				}
			}
		}
	}
}

FNavigationMarkerSettings UNavigationMarkerComponent::GetMarkerSettings(const FGameplayTag& NavigatorType)
{
	FNavigationMarkerSettings Settings = DefaultMarkerSettings;
	FNavigationMarkerSettings Overrides = CompassOverrideSettings;

	if (NavigatorType == FNavigatorGameplayTags::Get().NavigatorTypes_Compass)
	{
		Overrides = CompassOverrideSettings;
	}
	else if(NavigatorType == FNavigatorGameplayTags::Get().NavigatorTypes_Worldmap)
	{
		Overrides = WorldMapOverrideSettings;
	}
	else if (NavigatorType == FNavigatorGameplayTags::Get().NavigatorTypes_Minimap)
	{
		Overrides = MinimapOverrideSettings;
	}
	else if (NavigatorType == FNavigatorGameplayTags::Get().NavigatorTypes_Screenspace)
	{
		Overrides = ScreenspaceOverrideSettings;
	}

	if (Overrides.bOverride_LocationDisplayName)
	{
		Settings.LocationDisplayName = Overrides.LocationDisplayName;
	}

	if (Overrides.bOverride_LocationIcon)
	{
		Settings.LocationIcon = Overrides.LocationIcon;
	}

	if (Overrides.bOverride_IconTint)
	{
		Settings.IconTint = Overrides.IconTint;
	}

	if (Overrides.bOverride_IconSize)
	{
		Settings.IconSize = Overrides.IconSize;
	}

	if (Overrides.bOverride_IconOffset)
	{
		Settings.IconOffset = Overrides.IconOffset;
	}

	if (Overrides.bOverride_bShowActorRotation)
	{
		Settings.bShowActorRotation = Overrides.bShowActorRotation;
	}

	return Settings;
}

void UNavigationMarkerComponent::RefreshMarker()
{
	OnRefreshRequired.Broadcast();
}

FText UNavigationMarkerComponent::GetMarkerActionText_Implementation(class UNarrativeNavigationComponent* Selector, class APlayerController* SelectorOwner) const
{
	return DefaultMarkerActionText;
}

bool UNavigationMarkerComponent::CanInteract_Implementation(class UNarrativeNavigationComponent* Selector, class APlayerController* SelectorOwner) const
{
	return true;
}

void UNavigationMarkerComponent::OnSelect_Implementation(class UNarrativeNavigationComponent* Selector, class APlayerController* SelectorOwner)
{
	
}

void UNavigationMarkerComponent::SetDomain(const FGameplayTagContainer& InMarkerDomain)
{
	MarkerDomain = InMarkerDomain;
	RemoveMarker();
	RegisterMarker();
}

void UNavigationMarkerComponent::AddDomains(const FGameplayTagContainer& NewMarkerDomains)
{
	MarkerDomain.AppendTags(NewMarkerDomains);
	RemoveMarker();
	RegisterMarker();
}

#undef LOCTEXT_NAMESPACE 