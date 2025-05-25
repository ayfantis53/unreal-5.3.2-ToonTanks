// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Unit/UI/Start_game_widget_test.h"

// Unreal headers
#include "HAL/PlatformProcess.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(start_game_widget_spawn_test, "UEUnitTests.UI.StartGameText.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto start_game_widget_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////
    
    // Get viewport and Initialize widget.
    UGameViewportClient* view_port = GEngine->GameViewport;
    TSharedPtr<class STT_Start_game_widget> widget_ref = SNew(STT_Start_game_widget);

    //// TESTS ////

    // Test text correct for win.
    TestTrue("Start game widget created", widget_ref.IsValid());

    //// FINISH ////

    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(start_game_widget_test, "UEUnitTests.UI.StartGameText.SetText", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto start_game_widget_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Initialize widget.
    TSharedPtr<class STT_Start_game_widget> widget_ref = SNew(STT_Start_game_widget);

    //// TESTS ////

    // Test text for FIRST second after game started.
    Start_game_widget_test::set_countdown_text(widget_ref, Start_game_widget_test::delta_times[0]);
    TestEqual("Start game 0s text set correctly", Start_game_widget_test::get_start_game_text(widget_ref), FString(TEXT("Get Ready!!!")));
    // Test text for SECOND second after game started.
    Start_game_widget_test::set_countdown_text(widget_ref, Start_game_widget_test::delta_times[1]);
    TestEqual("Start game 1s text set correctly", Start_game_widget_test::get_start_game_text(widget_ref), FString(TEXT("3")));
    // Test text for THIRD second after game started.
    Start_game_widget_test::set_countdown_text(widget_ref, Start_game_widget_test::delta_times[2]);
    TestEqual("Start game 2s text set correctly", Start_game_widget_test::get_start_game_text(widget_ref), FString(TEXT("2")));
    // Test text for FOURTH second after game started.
    Start_game_widget_test::set_countdown_text(widget_ref, Start_game_widget_test::delta_times[3]);
    TestEqual("Start game 3s text set correctly", Start_game_widget_test::get_start_game_text(widget_ref), FString(TEXT("1")));
    // Test text for FIFTH second after game started.
    Start_game_widget_test::set_countdown_text(widget_ref, Start_game_widget_test::delta_times[4]);
    TestEqual("Start game 4s text set correctly", Start_game_widget_test::get_start_game_text(widget_ref), FString(TEXT("Go!!!")));

    //// FINISH ////

    // Finish test
    return true;
}