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

#include "Pawns/TT_Tank.h"
#include "Pawns/TT_Base_pawn.h"

// Unreal headers
#include "CoreMinimal.h"
#include "TT_Tower.generated.h"


/**
 *	Class that defines enemy turret pawns to oppose player in game 
 */
UCLASS()
class TOONTANKS_API ATT_Tower : public ATT_Base_pawn
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this pawn's properties.
	ATT_Tower();

	/// @brief Called every frame
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	virtual auto Tick(float delta_time) -> void override;

	/// @brief
	auto handle_destruction() -> void;

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Check if path is valid and sets path of mesh in content browser.
	auto set_up_meshes() -> void;

	/// @brief Sees if the tank is in range to be fired at.
	auto check_fire_condition() -> void;

	/// @brief Checks to see if tank is the appropriate distance for pawn to fire at it.
	auto in_fire_range() -> bool;

	/* --------------------- REFERENCES --------------------- */

	/// @brief Reference to tank so we can find its location.
	ATT_Tank* tank_ref_;

	/* ---------------------- COMPONENTS -------------------- */

	//// PATHS TO MESH COMPONENTS ////

	/// @brief Path to tower turret static mesh in Content folder.
	FString base_mesh_path_{ "/Game/Assets/Meshes/SM_TowerBase.SM_TowerBase" };

	/// @brief Path to tower turret static mesh in Content folder.
	FString turret_mesh_path_{ "/Game/Assets/Meshes/SM_TowerTurret.SM_TowerTurret" };

	/* ------------------- INPUT ACTIONS -------------------- */

	//// FIRING PROPERTIES ////

	/// @brief How fast turrets fire at player when in range.
	float fire_rate_{ 2.f };

	/// @brief The max range at which the turrets will begin attacking the player.
	float fire_range_{ 700.f };

	/// @brief Unique handle used to set fire timer of tower.
	FTimerHandle fire_rate_timer_handle_;

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Pawn.
	friend class Tower_test;

	/// @brief Test classes to function test this Pawn.
	friend class ATT_functional_test_tower;
};
