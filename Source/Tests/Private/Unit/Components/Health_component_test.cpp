// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Unit/Components/Health_component_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(health_spawn_test, "UEUnitTests.Components.HealthComponent.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto health_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank   = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test all components were made and projectile was bound to delegate.
    TestNotNull("Health Component created", Health_component_test::get_health_component(tank));

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(health_begin_play_test, "UEUnitTests.Components.HealthComponent.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto health_begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank   = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Call BeginPlay which binds on damage to pawn.
    tank->DispatchBeginPlay();

    // Test all components were made and projectile was bound to delegate.
    TestTrue("Health Component bound tank to delegate", tank->OnTakeAnyDamage.IsBound());

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(health_comp_kill_tank_test, "UEUnitTests.Components.HealthComponent.KillTank", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto health_comp_kill_tank_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank   = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Call BeginPlay which binds on damage to pawn.
    tank->DispatchBeginPlay();

    // Get health from spawned tank since its a component of every pawn.
    auto health = Health_component_test::get_health_component(tank);
    Health_component_test::call_take_damage(health, tank, 100.f, GetDefault<UDamageType>(), nullptr, nullptr);

    // Test all components were made and projectile was bound to delegate.
    TestEqual("Tank health was subtracted", Health_component_test::get_health_value(health), 0.f);

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}