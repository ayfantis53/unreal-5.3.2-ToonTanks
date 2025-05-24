// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Unit/Pawns/Tank_test.h"

// Unreal headers
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_tank_test, "UEUnitTests.Pawns.Tank.SpawnTank", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_tank_test::RunTest(const FString& Parameters) -> bool
{
    // Create game and create a tank pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank  = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test Tank was made.
    TestNotNull("Tank Mesh Made",           tank                                                           );
    // Test all components and effects were made.
    TestFalse("Tank Base Mesh populated",   Tank_test::get_tank_base_mesh(tank)->GetPathName().Equals("")  );
    TestFalse("Tank Turret Mesh populated", Tank_test::get_tank_turret_mesh(tank)->GetPathName().Equals(""));
    TestNotNull("Tank Movement created",    Tank_test::get_tank_movement_component(tank)                   );

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(camera_components_test, "UEUnitTests.Pawns.Tank.CameraComponents", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto camera_components_test::RunTest(const FString& Parameters) -> bool
{
    // Create game and create a tank pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank  = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    // Test all Camera and Spring arm components and effects were made.
    TestNotNull("Tank Camera created",           Tank_test::get_tank_camera(tank)                              );
    TestNotNull("Tank Spring arm created",       Tank_test::get_tank_spring_arm(tank)                          );
    TestEqual("Tank Spring arm Length",          Tank_test::get_tank_spring_arm(tank)->TargetArmLength, 600.f  );
    TestEqual("Spring arm rotation set",         Tank_test::get_tank_spring_arm(tank)->GetRelativeRotation(), FRotator(-33.f, 0.f, 0.f));
    TestTrue("Spring arm Camera Lag",            Tank_test::get_tank_spring_arm(tank)->bEnableCameraLag        );
    TestTrue("Spring arm CameraRotationLag",     Tank_test::get_tank_spring_arm(tank)->bEnableCameraRotationLag);
    TestEqual("Spring arm CameraLagSpeed",       Tank_test::get_tank_spring_arm(tank)->CameraLagSpeed, 4.f     );

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(tank_begin_play_test, "UEUnitTests.Pawns.Tank.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto tank_begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank  = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    // Setup player controller (Spawn and posess pawn).
    auto  controller = world->SpawnActor<APlayerController>(FVector(0.f), FRotator(0.f));
    world->AddController(controller);
    controller->Possess(tank);

    //// TEST ////

    // Call BeginPlay.
    tank->DispatchBeginPlay();

    // Test player controller was set.
    TestNotNull("Player controller ref set", Tank_test::get_player_controller(tank));

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_player_input_test, "UEUnitTests.Pawns.Tank.SetupPlayerInput", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_player_input_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank  = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    // Setup Player Input.
    auto       comp  = NewObject<UEnhancedInputComponent>();
    tank->SetupPlayerInputComponent(comp);

    //// TEST ////

    // Test Bindings were added to the Player Input Component.
    TestTrue("Player Input Setup successfully", comp->HasBindings());

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(handle_tank_destruction_test, "UEUnitTests.Pawns.Tank.Destruction", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto handle_tank_destruction_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto       tank  = world->SpawnActor<ATT_Tank>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // call destruction function.
    Tank_test::call_handle_destruction(tank);

    // Test Tank was destroyed properly.
    TestTrue("Tank dissapeared after destruct",  tank->IsHidden());
    TestFalse("Tank dissapeared after destruct", tank->IsActorTickEnabled());
    TestFalse("Tank is no longer alive",         tank->b_alive);

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}