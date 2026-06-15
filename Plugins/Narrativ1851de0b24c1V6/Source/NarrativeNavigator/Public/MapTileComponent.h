// Copyright Narrative Tools 2025.

#pragma once

#include "CoreMinimal.h"
#include "NavigationMarkerComponent.h"
#include <GameplayTagContainer.h>
#include <NativeGameplayTags.h>
#include "MapTileComponent.generated.h"

USTRUCT(BlueprintType)
struct FMapTileLayer
{
	GENERATED_BODY()

	FMapTileLayer()
		: LayerTag()
		, MapTileTexture(nullptr)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Tiles")
	FGameplayTag LayerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Tiles")
	TObjectPtr<class UTexture2D> MapTileTexture;
};

/**
 * A specialized map marker used for map tiles. Map tiles are nice because we can generate the right size grid for our specified map.
 */
UCLASS(ClassGroup = (Narrative), Blueprintable, DisplayName = "Map Tile Marker", meta = (BlueprintSpawnableComponent))
class NARRATIVENAVIGATOR_API UMapTileComponent : public UNavigationMarkerComponent
{
	GENERATED_BODY()

	UMapTileComponent();

	virtual bool CanInteract_Implementation(class UNarrativeNavigationComponent* Selector, class APlayerController* SelectorOwner) const;

public:

	//The map tile layers.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Tiles")
	TMap<FGameplayTag, TObjectPtr<UTexture2D>> MapTileLayers;

	//Set the layer of this map tile for the given domains
	UFUNCTION(BlueprintCallable, Category = "Map Layers")
	bool SetMapLayer(
		UPARAM(meta = (Categories = "Navigator.MapLayer")) const FGameplayTag& NewLayer,
		UPARAM(meta = (Categories = "Navigator.NavigatorTypes")) const FGameplayTagContainer& Domains
	);
};