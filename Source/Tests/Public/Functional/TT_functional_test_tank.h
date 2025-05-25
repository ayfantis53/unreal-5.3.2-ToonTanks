// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "Functional/TT_functional_test_base.h"
#include "TT_functional_test_tank.generated.h"


/**
 *  Functional test actor to demonstrate the Tank Player Controls
 */
UCLASS()
class TESTS_API ATT_functional_test_tank : public ATT_functional_test_base
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this test actor's properties.
	ATT_functional_test_tank();

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;
	
private:
	/// @brief Aims at center of screen.
	UFUNCTION()
	void center_mouse();

	/// @brief Presses button to move tank forward.
	UFUNCTION()
	void move_forward();

	/// @brief Presses button to move tank backward.
	UFUNCTION()
	void move_backward();

	/// @brief Presses button to move tank right.
	UFUNCTION()
	void move_right();

	/// @brief Presses button to move tank left.
	UFUNCTION()
	void move_left();

	/// @brief Stops all input for tank.
	UFUNCTION()
	void stop();

	/// @brief Makes tank fire a projectile.
	UFUNCTION()
	void tank_fire();

	/// @brief Verify tank moved forward.
	UFUNCTION()
	void verify_moved_forward();

	/// @brief Verify tank moved backward.
	UFUNCTION()
	void verify_moved_backward();

	/// @brief Verify tank Rotated right.
	UFUNCTION()
	void verify_moved_right();

	/// @brief Verify tank Rotated right.
	UFUNCTION()
	void verify_moved_left();

	/// @brief Verify tank fired.
	UFUNCTION()
	void verify_fired();

	/* ------------------ ASSERTION MEMBERS ----------------- */
	
	//// MOVEMENT ////

	/// @brief Tanks prev position to compare for test.
	FVector tank_last_pos_{};
	
	/// @brief Tanks current position to compare for test.
	FVector tank_curr_pos_{};

	//// ROTATION ////

	/// @brief Tanks prev rotation to compare for test.
	FRotator tank_last_rot_{};
	
	/// @brief Tanks current rotation to compare for test.
	FRotator tank_curr_rot_{};
};
