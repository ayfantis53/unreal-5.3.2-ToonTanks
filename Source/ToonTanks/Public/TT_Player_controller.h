// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TT_Player_controller.generated.h"


/**
 *	Player controller for Tank player in game 
 */
UCLASS()
class TOONTANKS_API ATT_Player_controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this component's properties.
	ATT_Player_controller();

	/// @brief Takes player control away if player dies so we cannot move once tank is technically destroyed.
	/// @param b_player_enabled Tells us if player is controllable.
	auto set_player_enabled_state(bool b_player_enabled) -> void;
};
