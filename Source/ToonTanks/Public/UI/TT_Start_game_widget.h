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
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"


/**
 *	Slate widget that is design and function of start game text 
 */
class TOONTANKS_API STT_Start_game_widget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STT_Start_game_widget)
	{}
	SLATE_END_ARGS()

	/// @brief This is the method that's called to build the UI widget.
	/// @param in_args struct that contains the parameters passed to the widget during its construction.
	auto Construct(const FArguments& in_args) -> void;

protected:
	/// @brief Ticks this widget with Geometry. Override in derived classes, but always call the parent implementation.
	/// @param allotted_geometry updates position, rotation, or properties of objects (geometry) in the game world.
	/// @param in_current_time   current time within the game's simulation, which is updated each frame.
	/// @param in_delta_time     time elapsed since the last frame, often represented as a floating-point number.
	virtual auto Tick(const FGeometry& allotted_geometry, 
					  const double     in_current_time, 
					  const float      in_delta_time) -> void override;

private:
	/// @brief Populate the game time text to countdown timer using time from game.
	/// @param in_current_time current time within the game's simulation, which is updated each frame.
	auto count_down(const float in_delta_time) -> void;
	
	/// @brief Text for countdown display at start of game.
	TSharedPtr<STextBlock> display_text_;

	/// @brief Value for Start Game Text.
	FString start_game_text_{ "" };

	/// @brief needed to set the widget text to Roboto.
	inline const static FString roboto_path_{ "Slate/Fonts/Roboto-Bold.ttf" };

	/// @brief Time it takes for the countdown.
	float count_down_{ 4.f };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Component.
	friend class Start_game_widget_test;
};
