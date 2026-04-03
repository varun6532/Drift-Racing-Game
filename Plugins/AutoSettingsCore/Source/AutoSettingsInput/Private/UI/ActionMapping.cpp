// Copyright Sam Bonifacio. All Rights Reserved.

#include "UI/ActionMapping.h"

#include "AutoSettingsError.h"
#include "InputMappingManager.h"

void UActionMapping::NativeConstruct()
{
	Super::NativeConstruct();
}

void UActionMapping::UpdateLabel_Implementation()
{
	if(!GetActionLabel())
	{
		FAutoSettingsError::LogMissingBindWidget(GetClass(), GET_MEMBER_NAME_CHECKED(ThisClass, ActionLabel));
		return;
	}
	
	GetActionLabel()->ActionName = ActionName;
	GetActionLabel()->MappingGroup = MappingGroup;
	GetActionLabel()->KeyGroup = KeyGroup;
	GetActionLabel()->bUsePlayerKeyGroup = false;
	GetActionLabel()->IconTags = IconTags;
	GetActionLabel()->InitializeLabel();
}

void UActionMapping::BindChord(FCapturedInput CapturedInput)
{
	const FInputChord Chord = CapturedInput.Chord;
	const FInputActionKeyMapping NewMapping = FInputActionKeyMapping(ActionName, Chord.Key, Chord.bShift, Chord.bCtrl, Chord.bAlt, Chord.bCmd);

	// Override all key groups if none is specified
	const bool bAnyKeyGroup = !KeyGroup.IsValid();

	// Update this player's bindings
	UInputMappingManager::Get()->AddPlayerActionOverride(GetOwningPlayer(), NewMapping, MappingGroup, bAnyKeyGroup);

	// Tell the label to refresh since we might have changed keys
	GetActionLabel()->InitializeLabel();
}

