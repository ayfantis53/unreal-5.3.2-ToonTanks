// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TT_Game_mode.generated.h"


class ATT_Tank;
class ATT_Player_controller;

/**
 *	Game Mode handles how the game starts and when/how it ends
 */
UCLASS()
class TOONTANKS_API ATT_Game_mode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this component's properties.
	ATT_Game_mode();

	/// @brief Dissapears Pawn when destroyed.
	/// @param dead_actor Actor to be destroyed.
	auto actor_died(AActor* dead_actor) -> void;

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Displays Start game widget.
	auto start_game() -> void;

	/// @brief How to end game, what text widget to handle.
	/// @param b_won_game tells if player won the game or not.
	auto game_over(bool b_won_game) -> void;

	/// @brief Deletes widget from screen.
	auto remove_widget() -> void;

	/// @brief Displays countdown widget and disables player input until countdown finished.
	auto handle_game_start() -> void;

	/// @brief Finds out how many towers are left in the game.
	auto get_target_tower_count() -> int32;

	/* --------------------- REFERENCES --------------------- */

	//// GAME CLASSES ////

	/// @brief a reference to the tank pawn or player.
	ATT_Tank* tank_ref_;

	/// @brief a reference to the player controller.
	ATT_Player_controller* tt_player_controller_ref_;

	//// WIDGET SHARED POINTERS ////

	/// @brief reference to start game widget.
	TSharedPtr<class STT_Start_game_widget> start_game_widget_ref_;

	/// @brief ptr to widget that holds the start game widget.
	TSharedPtr<SWidget> start_game_widget_container_;

	/// @brief reference to end game widget.
	TSharedPtr<class STT_End_game_widget> end_game_widget_ref_;

	/// @brief ptr to widget that holds the end game widget.
	TSharedPtr<SWidget> end_game_widget_container_;

	/* --------------------- PROPERTIES --------------------- */

	/// @brief Amount of seconds it takes to countdown the game start.
	float start_delay_{ 5.0f };

	/// @brief How many towers we have to kill left in game to win.
	int32 target_towers_{ 0 };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to function test this GameMode.
	friend class ATT_functional_test_tower;
	friend class ATT_functional_test_widgets;
};
