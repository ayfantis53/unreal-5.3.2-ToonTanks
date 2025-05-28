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

// Unreal headers
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_Base_pawn.generated.h"


class ATT_Projectile;
class UTT_Health_component;

/**
 *	Base Pawn for tanks and turrets in game
 */
UCLASS()
class TOONTANKS_API ATT_Base_pawn : public APawn
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this pawn's properties.
	ATT_Base_pawn();

protected:
	/// @brief Rotate turret to wherever child pawn needs to aim.
	/// @param look_at_target directional point turret needs to be pointing.
	auto rotate_turret(FVector look_at_target) -> void;

	/// @brief Fires projectile from cannon.
	auto fire() -> void;

	/// @brief Destroys pawn if health goes to zero.
	auto handle_destruction() -> void;

	/* --------------------- COMPONENTS --------------------- */

	/// @brief Used mainly to define collisions and transform of an object.
	UPROPERTY()
	UCapsuleComponent* capsule_comp_;

	/// @brief Basic unit used to create Tank base world geometry for levels.
	UPROPERTY()
	UStaticMeshComponent* base_mesh_;

	/// @brief Basic unit used to create Tank turret world geometry for levels.
	UPROPERTY()
	UStaticMeshComponent* turret_mesh_;

	/// @brief Actor Component that exists at a specific physical position in the world for bullets.
	UPROPERTY()
	USceneComponent* projectile_spawn_point_;

	/// @brief Component that keeps track if we should be alive or not.
	UPROPERTY()
	UTT_Health_component* health_component_;

private:
	/// @brief Construction helpers to set all UPROPERTIES.
	auto set_up_base_pawn() -> void;

	/* ----------------------- EFFECTS ---------------------- */

	//// POINTERS TO EFFECTS ////
	
	/// @brief Sets animation for when tank or tower dies.
	UPROPERTY()
	UParticleSystem* death_particles_;

	/// @brief Sets sound for for when tank or tower dies.
	UPROPERTY()
	USoundBase* death_sound_;

	/// @brief Sets Camera shake for when tank or tower dies.
	UPROPERTY()
	TSubclassOf<UCameraShakeBase> death_camera_shake_class_;

	//// PATHS TO EFFECTS ////

	/// @brief Path to death particle effect in Content folder.
	FString death_particle_path_{ "/Game/Assets/Effects/P_DeathEffect.P_DeathEffect" };

	/// @brief Path to death sound effect in Content folder.
	FString death_sound_path_{ "/Game/Assets/Audio/Explode_Audio.Explode_Audio" };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Pawn.
	friend class Base_pawn_test;
	friend class Tank_test;
	friend class Tower_test;
	friend class Health_component_test;

	/// @brief Test classes to function test this Pawn.
	friend class ATT_functional_test_tower;
	friend class ATT_functional_test_widgets;
};