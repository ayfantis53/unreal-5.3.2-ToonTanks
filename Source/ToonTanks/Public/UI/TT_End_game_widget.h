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

#include "TT_Game_mode.h"

// Unreal headers
#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"


/**
 *	Slate widget that is design and function of end game text 
 */
class TOONTANKS_API STT_End_game_widget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STT_End_game_widget)
	{}
	SLATE_END_ARGS()

	/// @brief This is the method that's called to build the UI widget.
	/// @param in_args struct that contains the parameters passed to the widget during its construction.
	auto Construct(const FArguments& in_args) -> void;

	/// @brief sets text for game over from gamemode.
	/// @param b_win tells if player won or not to display correct text .
	auto set_game_over_text(bool b_win) -> void;

private:
	/// @brief Text for countdown display at start of game.
	TSharedPtr<STextBlock> display_text_;

	/// @brief Value for Start Game Text.
	FString end_game_text_{ "GAME OVER!" };

	/// @brief needed to set the widget text to Roboto.
	inline const static FString roboto_path_{ "Slate/Fonts/Roboto-Bold.ttf" };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Component.
	friend class End_game_widget_test;
};
