// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "LegacyCameraShake.h"
#include "TT_Camera_shake_death.generated.h"


/**
 *	Camera Shake Effect for when something is destroyed in game 
 */
UCLASS()
class TOONTANKS_API UTT_Camera_shake_death : public ULegacyCameraShake
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this actor's properties.
	UTT_Camera_shake_death();
};
