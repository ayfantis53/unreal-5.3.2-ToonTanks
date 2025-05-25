// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#include "UI/TT_Start_game_widget.h"
#include "TT_Game_mode.h"


/**
 * Test class suite to assist Unit testing for Start game widget text
 */
class Start_game_widget_test
{
public:
    /* --------------------- MEMBER VARS -------------------- */

    /// @brief tIME FOR COUNTING DOWN START GAME COUNTER TO TEST STARTGAME WIDGET.
    static constexpr float delta_times[] = { 0.f, 1.f, 1.017069f, 1.016772f, 1.016726f };

    /// @brief Get start game text.
    /// @return FString.
    static auto get_start_game_text(TSharedPtr<class STT_Start_game_widget> widget_ref) -> FString
    {
        return widget_ref->start_game_text_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Calls toon tanks start_game_widget countdown text function.
    static auto set_countdown_text(TSharedPtr<class STT_Start_game_widget> widget_ref, int curr_time) -> void
    {
        return widget_ref->count_down(curr_time);
    }
};