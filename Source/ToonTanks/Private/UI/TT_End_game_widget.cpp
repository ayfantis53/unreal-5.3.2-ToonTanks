// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "UI/TT_End_game_widget.h"

// Unreal headers
#include "SlateOptMacros.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
auto STT_End_game_widget::Construct(const FArguments& in_args) -> void
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
						.Text(FText::FromString(end_game_text_))
				]
		];
}

auto STT_End_game_widget::set_game_over_text(bool b_win) -> void
{
	// Did player win or lose.
	if (b_win)
	{
		end_game_text_ = FString(TEXT("YOU WON!!!"));
	}
	else
	{
		end_game_text_ = FString(TEXT("YOU LOSE!!!"));
	}

	// Change display text accordingly.
	if (display_text_.IsValid())
	{
		display_text_->SetText(FText::FromString(end_game_text_));
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
