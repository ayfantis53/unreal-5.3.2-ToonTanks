// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "Functional/TT_functional_test_tower.h"


ATT_functional_test_tower::ATT_functional_test_tower()
{
    wait_delay_  = 2;
    timer_delay_ = 1.f;
}

auto ATT_functional_test_tower::BeginPlay() -> void
{
    Super::BeginPlay();

    test_steps_list_ = {
        "setup",
        "verify_tower_count",
        "destroy_tower",
        "verify_tower_count",
        "finish_test"
    };
}

auto ATT_functional_test_tower::verify_tower_count() -> void
{
    // Verify game mode is calculating the correct amount of towers.
    AssertEqual_Int(game_mode_ref_->get_target_tower_count(), num_turrets_[iteration_], "The number of towers in game is Correct");

    // So we can get to next step and iteration in array of tower nums.
    iteration_++;

    progress_test_step();
}

auto ATT_functional_test_tower::destroy_tower() -> void
{
    // Find a tower and destroy it.
    TArray<AActor*> out_actors;
    UGameplayStatics::GetAllActorsOfClass(this, ATT_Tower::StaticClass(), out_actors);
    if (!out_actors.IsEmpty())
    {
        auto turret = Cast<ATT_Tower>(out_actors[0]);
        turret->health_component_->damage_taken(turret, 200, GetDefault<UDamageType>(), nullptr, nullptr);
    }

    progress_test_step();
}




