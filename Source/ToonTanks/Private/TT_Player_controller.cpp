// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "TT_Player_controller.h"


ATT_Player_controller::ATT_Player_controller()
{
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bShowMouseCursor   = true;
}

auto ATT_Player_controller::set_player_enabled_state(bool b_player_enabled) -> void
{
	if (b_player_enabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = b_player_enabled;
}