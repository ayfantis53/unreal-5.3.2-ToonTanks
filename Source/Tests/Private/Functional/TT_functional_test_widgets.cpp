// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "Functional/TT_functional_test_widgets.h"

#include "UI/TT_Start_game_widget.h"
#include "UI/TT_End_game_widget.h"


ATT_functional_test_widgets::ATT_functional_test_widgets()
{
    wait_delay_  = 2;
    timer_delay_ = 1.f;
}

auto ATT_functional_test_widgets::BeginPlay() -> void
{
    Super::BeginPlay();

    test_steps_list_ = {
        "setup",
        "wait",
        "verify_start_widget",
        "wait",
        "verify_start_widget_collapsed",
        "verify_end_widget_collapsed",
        "end_game",
        "wait",
        "verify_end_widget",
        "finish_test"
    };
}

auto ATT_functional_test_widgets::verify_start_widget() -> void
{
    // Is Start game widget visible?
    AssertTrue(game_mode_ref_->start_game_widget_ref_->GetVisibility() == EVisibility::Visible, "Start Game widget active.");

    progress_test_step();
}

auto ATT_functional_test_widgets::verify_start_widget_collapsed() -> void
{
    // Is Start game widget visible?
    AssertTrue(game_mode_ref_->start_game_widget_ref_.IsValid(), "Start Game widget NOT active.");

    progress_test_step();
}

auto ATT_functional_test_widgets::verify_end_widget_collapsed() -> void
{
    // Is Start game widget visible?
    AssertTrue(game_mode_ref_->start_game_widget_ref_.IsValid(), "END Game widget NOT active.");

    progress_test_step();
}

auto ATT_functional_test_widgets::end_game() -> void
{
    // Set game to win
    bool game_won = true;
    game_mode_ref_->game_over(game_won);

    progress_test_step();
}

auto ATT_functional_test_widgets::verify_end_widget() -> void
{
    // Is End game widget visible?
    AssertTrue(game_mode_ref_->end_game_widget_ref_->GetVisibility() == EVisibility::Visible, "End Game widget active.");

    progress_test_step();
}
