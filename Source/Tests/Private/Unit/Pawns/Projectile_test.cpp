// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Unit/Pawns/Projectile_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_projectile_test, "UEUnitTests.Pawns.Projectile.SpawnProjectile", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_projectile_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto projectile  = world->SpawnActor<ATT_Projectile>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test Projectile was made.
    TestNotNull("Projectile was Created",             projectile                                                    );
    // Test all components and effects were made.
    TestNotNull("Projectile Mesh Made ",              Projectile_test::get_projectile_mesh(projectile)              );
    TestNotNull("Projectile Movement Component made", Projectile_test::get_projectile_movement_component(projectile));
    TestNotNull("Trailing particles Made",            Projectile_test::get_trail_particles_component(projectile)    );
    TestNotNull("Hit Particle Effects Made",          Projectile_test::get_hit_particles_fx(projectile)             );
    TestNotNull("Launch Sound Made",                  Projectile_test::get_launch_sound_fx(projectile)              );
    TestNotNull("Hit Sound Made",                     Projectile_test::get_hit_sound_fx(projectile)                 );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(begin_play_test, "UEUnitTests.Pawns.Projectile.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto projectile  = world->SpawnActor<ATT_Projectile>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Call BeginPlay.
    projectile->DispatchBeginPlay();

    // Test all components were made and projectile was bound to delegate.
    TestTrue("Projectile bound to delegate",          Projectile_test::get_projectile_mesh(projectile)->OnComponentHit.IsBound());
    TestNotNull("Launch Sound Made",                  Projectile_test::get_launch_sound_fx(projectile)                          );

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}