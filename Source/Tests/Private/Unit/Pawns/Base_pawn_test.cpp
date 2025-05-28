// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "Unit/Pawns/Base_pawn_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_actor_test, "UEUnitTests.Pawns.BasePawn.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_actor_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto base_pawn   = world->SpawnActor<ATT_Base_pawn>(FVector(0.f), FRotator(0.f));

    //// TEST ////
    
    // Test BasePawn was made.
    TestNotNull("Base Pawn Made",           base_pawn                                            );
    // Test all components were made.
    TestNotNull("Capsule Made",             Base_pawn_test::get_capsule_comp(base_pawn)          );
    TestNotNull("Base Mesh Made ",          Base_pawn_test::get_base_mesh(base_pawn)             );
    TestNotNull("Turret Mesh Made",         Base_pawn_test::get_turret_mesh(base_pawn)           );
    TestNotNull("Projectile Spawn Made",    Base_pawn_test::get_projectile_spawn_point(base_pawn));
    TestNotNull("Health component Made",    Base_pawn_test::get_health_component(base_pawn)      );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(fire_test, "UEUnitTests.Pawns.BasePawn.Fire", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto fire_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto base_pawn    = world->SpawnActor<ATT_Base_pawn>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // call fire function.
    Base_pawn_test::call_fire(base_pawn);

    // Test projectile point has a location and rotation were made.
    FVector  location = Base_pawn_test::get_projectile_spawn_point(base_pawn)->GetComponentLocation();
    FRotator rotation = Base_pawn_test::get_projectile_spawn_point(base_pawn)->GetComponentRotation();

    TestTrue("Projectile location updated", location == FVector(0.f) );
    TestTrue("Projectile rotation updated", rotation == FRotator(0.f));

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(handle_destruction_test, "UEUnitTests.Pawns.BasePawn.Destruction", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto handle_destruction_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto base_pawn    = world->SpawnActor<ATT_Base_pawn>(FVector(0.f), FRotator(0.f));

    // Setup player controller (Spawn and posess pawn).
    auto  controller  = world->SpawnActor<APlayerController>(FVector(0.f), FRotator(0.f));
    world->AddController(controller);
    controller->Possess(base_pawn);

    //// TEST ////

    // call fire function.
    Base_pawn_test::call_handle_destruction(base_pawn);

    // Test all effects were made.
    TestNotNull("Death Effects Made ",      Base_pawn_test::get_death_particles_fx(base_pawn));
    TestNotNull("Death Sound Made ",        Base_pawn_test::get_death_sound_fx(base_pawn)    );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}