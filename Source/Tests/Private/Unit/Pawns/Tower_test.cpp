// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Unit/Pawns/Tower_test.h"
#include "Unit/Pawns/Tank_test.h"

// Unreal headers
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_tower_test, "UEUnitTests.Pawns.Tower.SpawnTower", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_tower_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tower pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tower = world->SpawnActor<ATT_Tower>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test Tower was made.
    TestNotNull("Tower Mesh Made",                 tower                                                                        );
    // Test all meshes were populated.
    TestFalse("Tower Base Mesh populated",         Tower_test::get_tower_base_mesh(tower)->GetPathName().Equals("")             );
    TestFalse("Tower Turret Mesh populated",       Tower_test::get_tower_turret_mesh(tower)->GetPathName().Equals("")           );
    // Test to ensure capsule properties are correct.
    TestEqual("Tower capsule half height correct", Tower_test::get_tower_capsule_comp(tower)->GetScaledCapsuleHalfHeight(), 74.f);
    TestEqual("Tower capsule radius is correct",   Tower_test::get_tower_capsule_comp(tower)->GetScaledCapsuleRadius(),     32.f);
    // Test projectile spawn point.
    TestEqual("Projectile spawn point correct",    Tower_test::get_projectile_spawn_point(tower)->GetRelativeLocation(), FVector(90.f, 0.f, 95.f));

    /// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(tower_begin_play_test, "UEUnitTests.Pawns.Tower.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto tower_begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tower pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tower = world->SpawnActor<ATT_Tower>(FVector(0.f), FRotator(0.f));

    // Call BeginPlay.
    tower->DispatchBeginPlay();

     //// TEST ////

    // Test tower were made.
    TestNotNull("Tower Mesh Made",                 tower);
    // Timer manager was set for checking fire condition.
    TestTrue("Check if Timer was set", world->GetTimerManager().IsTimerActive(Tower_test::get_fire_rate_timer_handle(tower)));
    
    /// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(tower_in_fire_range_test, "UEUnitTests.Pawns.Tower.InFireRange", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto tower_in_fire_range_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tower pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank  = world->SpawnActor<ATT_Tank>(FVector(30.f), FRotator(0.f));
    auto       tower = world->SpawnActor<ATT_Tower>(FVector(0.f), FRotator(0.f));

    // Setup player controller and add it to world (Spawn and posess pawn).
    auto  controller = world->SpawnActor<APlayerController>(FVector(0.f), FRotator(0.f));
    world->AddController(controller);
    controller->Possess(tank);

    // Call BeginPlay.
    tower->DispatchBeginPlay();

    //// TEST ////

    // Test tower were made.
    TestNotNull("Tower Mesh Made",          tower                                );
    TestNotNull("Tank Mesh Made",           tank                                 );
    // Timer manager was set for checking fire condition.
    TestTrue("Tower detects tank in range", Tower_test::call_in_fire_range(tower));

    /// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(handle_tower_destruction_test, "UEUnitTests.Pawns.Tower.Destruction", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto handle_tower_destruction_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tower pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tower  = world->SpawnActor<ATT_Tower>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test tower were made.
    TestNotNull("Tower Mesh Made", tower         );
    // call destruction function.
    Tower_test::call_handle_destruction(tower);
    // Test Tower was destroyed properly.
    TestFalse("Tower Mesh Made",   IsValid(tower));

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}