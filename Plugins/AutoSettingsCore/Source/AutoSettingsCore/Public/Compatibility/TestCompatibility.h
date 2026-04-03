// Copyright Sam Bonifacio. All Rights Reserved.

#pragma once

#include "Misc/EngineVersionComparison.h"

/**
 * Compatibility header for AutoSettings test files across different Unreal Engine versions.
 * 
 * This header provides compatibility definitions that allow test code to use modern UE syntax
 * while maintaining backward compatibility with older UE versions.
 * 
 * Usage: Include this header in test files before using UE automation test macros.
 */

// Version compatibility for EAutomationTestFlags_ApplicationContextMask
// UE 5.4 uses EAutomationTestFlags::ApplicationContextMask  
// UE 5.5+ uses EAutomationTestFlags_ApplicationContextMask
#if UE_VERSION_OLDER_THAN(5, 5, 0)
	constexpr auto EAutomationTestFlags_ApplicationContextMask = EAutomationTestFlags::ApplicationContextMask;
#endif