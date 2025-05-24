// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "Functional/TT_functional_test_base.h"
#include "TT_functional_test_tower.generated.h"


/**
 *	Test the Enemy Towers in the game 
 */
UCLASS()
class TESTS_API ATT_functional_test_tower : public ATT_functional_test_base
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this test actor's properties.
	ATT_functional_test_tower();

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Verify Number of towers is correct in game.
	UFUNCTION()
	void verify_tower_count();

	/// @brief Verify Number of towers is correct in game.
	UFUNCTION()
	void destroy_tower();

	/* ------------------- TESTING MEMBERS ------------------ */

	/// @brief Keeps track of steps for us.
	int iteration_{};

	/// @brief List of towers, based on step we are on.
	TArray<int32> num_turrets_{ 2, 1 };
};
