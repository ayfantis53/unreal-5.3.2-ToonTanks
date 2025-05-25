// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Functional/TT_functional_test_base.h"

// Unreal headers.
#include "TimerManager.h"
#include "UnrealClient.h"
#include "Engine/Engine.h" 
#include "GameFramework/GameUserSettings.h"


ATT_functional_test_base::ATT_functional_test_base()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;
}

auto ATT_functional_test_base::BeginPlay() -> void
{
	Super::BeginPlay();

    // Initialize necessary game references.
	tank_ref_            = Cast<ATT_Tank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    game_mode_ref_       = Cast<ATT_Game_mode>(UGameplayStatics::GetGameMode(GetWorld()));
    controller_ref_      = Cast<ATT_Player_controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    input_subsystem_ref_ = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller_ref_->GetLocalPlayer());
    
}

auto ATT_functional_test_base::Tick(float delta_time) -> void
{
	Super::Tick(delta_time);
}

auto ATT_functional_test_base::RunTest(const TArray<FString>& params) -> bool
{
	Super::RunTest(params);

    StartStep("RunTest");
    // increment to next part of test
    progress_test_step();

    return final_result_;
}

auto ATT_functional_test_base::setup() -> void
{
    // Check for headless and set viewport size
    if (GEngine && GEngine->GameViewport)
    {
        const auto game_settings = GEngine->GetGameUserSettings();
        game_settings->SetFullscreenMode(EWindowMode::Windowed);
        game_settings->SetScreenResolution(screen_size_);
        game_settings->ApplySettings(false);
    }

    // increment to next part of test
    progress_test_step();
}

auto ATT_functional_test_base::progress_test_step() -> void
{
    FinishStep();

    FTimerDelegate timer_delegate{};
    FTimerHandle   timer_handle{};

    timer_delegate.BindUFunction(this, test_steps_list_[test_step_iter_]);
    GetWorldTimerManager().SetTimer(timer_handle, timer_delegate, timer_delay_, false);

    StartStep(test_steps_list_[test_step_iter_].ToString());
    test_step_iter_++;
}

auto ATT_functional_test_base::wait() -> void
{
    // Set timer delay to wait delay
    float timer_temp = timer_delay_;
    timer_delay_     = wait_delay_;

    // increment to next part of test
    progress_test_step();

    // return timer delay back to normal value
    timer_delay_     = timer_temp;
}

auto ATT_functional_test_base::do_player_ia(UInputAction*                       input_action, 
                                            FInputActionValue                   input_value, 
                                            UEnhancedInputLocalPlayerSubsystem* subsystem) -> void
{
    auto player_input = subsystem->GetPlayerInput();
    player_input->InjectInputForAction(input_action, input_value);
}

auto ATT_functional_test_base::set_mouse_pos(float x, float y) -> void
{
    if (controller_ref_)
    {
        const ULocalPlayer* local_player = controller_ref_->GetLocalPlayer();
        if (local_player && local_player->ViewportClient)
        {
            FViewport* viewport = local_player->ViewportClient->Viewport;
            if (viewport)
            {
                FVector2d viewport_size{};
                local_player->ViewportClient->GetViewportSize(viewport_size);
                const int32 viewport_x = viewport_size.X * x;
                const int32 viewport_y = viewport_size.Y * y;

                viewport->SetMouse(viewport_x, viewport_y);
            }
        }
    }
}

auto ATT_functional_test_base::abort_test() -> void
{
    const FString err_msg = "Test FAILED. Exiting at step " + FString::FromInt(test_step_iter_) + GetCurrentStepName();

    AddError(err_msg);

    FinishStep();

    final_result_        = false;
    test_step_iter_      = test_steps_list_.Num() - 1;
}

auto ATT_functional_test_base::finish_test() -> void
{
    Result = final_result_ ? EFunctionalTestResult::Succeeded : EFunctionalTestResult::Failed;

    FinishStep();

    FinishTest(Result, "Reached the end of Test");
}

auto ATT_functional_test_base::FinishTest(EFunctionalTestResult test_result, const FString& message) -> void
{
    Super::FinishTest(test_result, message);

    UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}