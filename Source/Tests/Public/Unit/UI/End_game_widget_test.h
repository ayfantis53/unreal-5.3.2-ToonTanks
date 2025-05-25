// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#include "UI/TT_End_game_widget.h"


/**
 * Test class suite to assist Unit testing for End game widget text
 */
class End_game_widget_test
{
public:
    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get end game text.
    /// @return FString.
    static auto get_end_game_text(TSharedPtr<class STT_End_game_widget> widget_ref) -> FString
    {
        return widget_ref->end_game_text_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Calls toon tanks end_game_widget set game over text function.
    static auto set_game_over_text(TSharedPtr<class STT_End_game_widget> widget_ref, bool b_win) -> void
    {
        widget_ref->set_game_over_text(b_win);
    }
};