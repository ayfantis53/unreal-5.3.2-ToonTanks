// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Functional/TT_functional_test_tank.h"


ATT_functional_test_tank::ATT_functional_test_tank()
{
    wait_delay_  = 1;
    timer_delay_ = 1.f;
}

auto ATT_functional_test_tank::BeginPlay() -> void
{
    Super::BeginPlay();

    test_steps_list_ = {
        "setup",
        "wait",
        "center_mouse",
        "move_forward",
        "verify_moved_forward",
        "stop",
        "move_backward",
        "verify_moved_backward",
        "stop",
        "move_right",
        "verify_moved_right",
        "stop",
        "move_left",
        "verify_moved_left",
        "stop",
        "center_mouse",
        "tank_fire",
        "verify_fired",
        "finish_test"
    };
}

auto ATT_functional_test_tank::center_mouse() -> void
{
    // Aim mouse
    set_mouse_pos(0.5f, 0.2f);

    progress_test_step();
}

auto ATT_functional_test_tank::move_forward() -> void
{   
    // initial tank position
    tank_curr_pos_ = tank_ref_->GetActorLocation();

    // move tank forward
    controller_ref_->InputKey(FInputKeyParams{FKey{"W"}, IE_Pressed, 100.f});

    progress_test_step();
}

auto ATT_functional_test_tank::verify_moved_forward() -> void
{   
    // Check if tank moved in the positive X
    tank_last_pos_ = tank_curr_pos_;
    AssertTrue(tank_ref_->GetActorLocation().X > tank_last_pos_.X, "Tank moved forward");

    progress_test_step();
}

auto ATT_functional_test_tank::move_backward() -> void
{   
    // initial tank position
    tank_curr_pos_ = tank_ref_->GetActorLocation();

    // move tank backward
    controller_ref_->InputKey(FInputKeyParams{FKey{"S"}, IE_Pressed, 100.f});

    progress_test_step();
}

auto ATT_functional_test_tank::verify_moved_backward() -> void
{   
    // Check if tank moved in the negative X
    tank_last_pos_ = tank_curr_pos_;
    AssertTrue(tank_ref_->GetActorLocation().X < tank_last_pos_.X, "Tank moved backward");

    progress_test_step();
}

auto ATT_functional_test_tank::move_right() -> void
{   
    // Change delay between tests since projectile will only exist shortly
    timer_delay_ = 0.1f;

    tank_last_rot_ = tank_ref_->GetActorRotation();

    // move tank forward
    controller_ref_->InputKey(FInputKeyParams{FKey{"D"}, IE_Pressed, 1.f});

    progress_test_step();
}

auto ATT_functional_test_tank::verify_moved_right() -> void
{   
    // Check if tank rotated in postive YAW
    tank_last_rot_ = tank_curr_rot_;
    AssertTrue(tank_ref_->GetActorRotation().Yaw > tank_last_rot_.Yaw, "Tank turned right");

    progress_test_step();
}

auto ATT_functional_test_tank::move_left() -> void
{   
    timer_delay_ = 0.3f;
    // move tank forward
    controller_ref_->InputKey(FInputKeyParams{FKey{"A"}, IE_Pressed, 1.f});

    progress_test_step();
}

auto ATT_functional_test_tank::verify_moved_left() -> void
{   
    // Check if tank rotated in negative YAW
    AssertTrue(tank_ref_->GetActorRotation().Yaw < tank_last_rot_.Yaw, "Tank turned left");

    progress_test_step();
}

auto ATT_functional_test_tank::stop() -> void
{   
    timer_delay_ = 1.f;

    // stop tank
    controller_ref_->InputKey(FInputKeyParams{FKey{"W"}, IE_Released, 100.f});
    controller_ref_->InputKey(FInputKeyParams{FKey{"S"}, IE_Released, 100.f});
    controller_ref_->InputKey(FInputKeyParams{FKey{"D"}, IE_Released, 100.f});
    controller_ref_->InputKey(FInputKeyParams{FKey{"A"}, IE_Released, 100.f});

    progress_test_step();
}

auto ATT_functional_test_tank::tank_fire() -> void
{   
    // Change delay between tests since projectile will only exist shortly
    timer_delay_ = 0.4f;

    // Fire tank cannon
    const auto fire_value = FInputActionValue(true);
    do_player_ia(tank_ref_->fire_action_, fire_value, input_subsystem_ref_);

    progress_test_step();
}

auto ATT_functional_test_tank::verify_fired() -> void
{   
    // See if a projectile actually spawned
    TArray<AActor*> out_actors;
    UGameplayStatics::GetAllActorsOfClass(this, ATT_Projectile::StaticClass(), out_actors);
    AssertFalse(out_actors.IsEmpty(), "Projectile was fired and spawned");

    progress_test_step();
}