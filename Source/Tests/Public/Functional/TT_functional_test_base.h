// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //
#pragma once

#include "TT_Game_mode.h"
#include "Pawns/TT_Tank.h"
#include "Pawns/TT_Tower.h"
#include "Pawns/TT_Projectile.h"
#include "TT_Player_controller.h"
#include "Components/TT_Health_component.h"

// Unreal headers
#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "Kismet/GameplayStatics.h"
#include "TT_functional_test_base.generated.h"


/**
 *	Base Functional test actor to be used to Component test game
 */
UCLASS()
class TESTS_API ATT_functional_test_base : public AFunctionalTest
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this test actor's properties.
	ATT_functional_test_base();
	
	/// @brief Called every frame
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	virtual auto Tick(float delta_time) -> void override;

	/// @brief function in Unreal Engine's automation testing framework executes a specific test from parameters provided.
	/// @param params array of FStrings used to pass data or instructions to the test being executed.
	/// @return true signifies success, while false indicates one or more tests failed or an error occurred during execution.
	virtual auto RunTest(const TArray<FString>& params = TArray<FString>()) -> bool override;

	/// @brief signals the completion of an automated test.
	/// @param test_result enum value indicating the test outcome (success, failure, or skipped).
	/// @param message     an optional message providing additional context.
	virtual auto FinishTest(EFunctionalTestResult test_result, const FString& message) -> void override;

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

	/// @brief Sets up everything needed to initialize test.
	UFUNCTION()
	virtual void setup();

	/// @brief Bind new function from step list to timer, firing every 3 seconds to allow game to process input events.
	UFUNCTION()
	void progress_test_step();

	/// @brief Delay test in between step iterations.
	UFUNCTION()
	void wait();

	/// @brief Abort test without crashing and cleanup, because we encountered an unrecoverable error.
	UFUNCTION()
	void abort_test();

	/// @brief Set final result and call FinishTest() to close out test.
	UFUNCTION()
	void finish_test();

	/// @brief Calls a player action from our tank class.
	/// @param input_action bound action being called to be used in game.
	/// @param input_value  either bool(key presses/button clicks), float(mouse movement) or FVector2D(2D axis inputs).
	/// @param subsystem    manages and controls the player's input for the game.
	UFUNCTION()
	void do_player_ia(UInputAction* input_action, FInputActionValue input_value, UEnhancedInputLocalPlayerSubsystem* subsystem);

	/// @brief Set mouse position FVector2D in viewport.
	/// @param x horizontal position on screen between (0 and 1).
	/// @param y vertical on screen between (0 and 1).
	UFUNCTION()
	void set_mouse_pos(float x, float y);

	/* ----------------- REFERENCES FOR TEST ---------------- */

	/// @brief Reference to the player tank.
	UPROPERTY()
	ATT_Tank* tank_ref_;

	/// @brief Reference to tank controller to access input.
	UPROPERTY()
	ATT_Player_controller* controller_ref_;

	/// @brief Reference to tank gamemode.
	UPROPERTY()
	ATT_Game_mode* game_mode_ref_;

	/// @brief Reference to input subsystem of tank pawn.
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* input_subsystem_ref_;

	/* ------------------- TESTING MEMBERS ------------------ */

	/// @brief Stores the result of each individual event by logic AND-ing the values.
	bool final_result_{ true };

	/// @brief List of all UFUNCTIONS (representing steps in the test) bound to timer, run in this order.
	UPROPERTY()
	TArray<FName> test_steps_list_{};

	/// @brief Size of screen when testing.
	FIntPoint screen_size_{ 1000, 1200 };

	/// @brief Amount of time between function calls.
	float timer_delay_{ 3.f };

	/// @brief Amount of aditional delay to add between functions.
	int wait_delay_{ 7 };

private:
	/// @brief current step functional test is on.
	int test_step_iter_{};
};
