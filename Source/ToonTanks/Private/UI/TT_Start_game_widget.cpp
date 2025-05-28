// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "UI/TT_Start_game_widget.h"

// Unreal headers
#include "Widgets/Layout/SConstraintCanvas.h"
#include "SlateOptMacros.h"

// System headers
#include <cmath>


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
auto STT_Start_game_widget::Construct(const FArguments& in_args) -> void
{
	// Widget Design.
	ChildSlot
	[
		// Populate the widget.
		SNew(SConstraintCanvas)
			+ SConstraintCanvas::Slot()
			.AutoSize(true)
			.Anchors(FAnchors(0.5, 0.5, 0.5, 0.5))
			.Offset(FVector2d(0, -320))
		[
			// Our Text for widget.
			SAssignNew(display_text_, STextBlock)
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / roboto_path_, 42))
				.ColorAndOpacity(FLinearColor::White)
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
				.ShadowOffset(FVector2D(2.f, 2.f))
				.Text(FText::FromString(start_game_text_))
		]
	];

}

auto STT_Start_game_widget::Tick(const FGeometry& allotted_geometry, const double in_current_time, const float in_delta_time) -> void
{
	SCompoundWidget::Tick(allotted_geometry, in_current_time, in_delta_time);

	// Populate the game time to countdown timer.
	count_down(in_delta_time);
}

auto STT_Start_game_widget::count_down(const float in_delta_time) -> void
{
	count_down_ = count_down_ - in_delta_time;
	auto result = static_cast<int>(ceil(count_down_));

	// Set text based on the countdown.
	switch (result)
	{
	case 0:
		start_game_text_ = FString(TEXT("Go!!!"));
		break;
	case 1:
		start_game_text_ = FString(TEXT("1"));
		break;
	case 2:
		start_game_text_ = FString(TEXT("2"));
		break;
	case 3:
		start_game_text_ = FString(TEXT("3"));
		break;
	case 4:
		start_game_text_ = FString(TEXT("Get Ready!!!"));
		break;
	default:
		start_game_text_ = FString(TEXT(" "));
		break;
	}

	// Display text.
	if (display_text_.IsValid())
	{
		display_text_->SetText(FText::FromString(start_game_text_));
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
