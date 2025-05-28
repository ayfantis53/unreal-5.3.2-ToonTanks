// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "Unit/UI/End_game_widget_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(end_game_widget_spawn_test, "UEUnitTests.UI.EndGameText.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto end_game_widget_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////
    
    // Get viewport and Initialize widget.
    UGameViewportClient* view_port = GEngine->GameViewport;
    TSharedPtr<class STT_End_game_widget> widget_ref = SNew(STT_End_game_widget);

    //// TEST ////

    // Test text correct for win.
    TestTrue("End game widget created", widget_ref.IsValid());

    //// FINISH ////

    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(end_game_widget_test, "UEUnitTests.UI.EndGameText.SetText", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto end_game_widget_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Initialize widget.
    TSharedPtr<class STT_End_game_widget> widget_ref = SNew(STT_End_game_widget);

    //// TEST ////

    // Test text correct for win.
    End_game_widget_test::set_game_over_text(widget_ref, true);
    TestEqual("Winning text set correctly", End_game_widget_test::get_end_game_text(widget_ref), FString(TEXT("YOU WON!!!")));

    // Test text correct for Loss.
    End_game_widget_test::set_game_over_text(widget_ref, false);
    TestEqual("Losing text set correctly", End_game_widget_test::get_end_game_text(widget_ref), FString(TEXT("YOU LOSE!!!")));

    //// FINISH ////

    // Finish test.
    return true;
}