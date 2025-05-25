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
#include "TT_functional_test_widgets.generated.h"


/**
 *  Test the widgets in the game
 */
UCLASS()
class TESTS_API ATT_functional_test_widgets : public ATT_functional_test_base
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this test actor's properties.
	ATT_functional_test_widgets();

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Verify Start game widget displays.
	UFUNCTION()
	void verify_start_widget();

	/// @brief Verify Start game widget hidden.
	UFUNCTION()
	void verify_start_widget_collapsed();

	/// @brief Verify Start game widget hidden.
	UFUNCTION()
	void verify_end_widget_collapsed();

	/// @brief Destroys turret to end game.
	UFUNCTION()
	void end_game();

	/// @brief Verify End game widget displays.
	UFUNCTION()
	void verify_end_widget();
};
