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

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Projectile.generated.h"


class USoundBase;
class UParticleSystem;
class ULegacyCameraShake;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

/**
 *	Projectile Clas used to animate missiles when fired from Tanks and Turrets
 */
UCLASS()
class TOONTANKS_API ATT_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	/// @brief Sets default values for this actor's properties.
	ATT_Projectile();

	/// @brief Called every frame
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	virtual auto Tick(float delta_time) -> void override;

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;
	
private:
	/// @brief Construction helpers to set all UPROPERTIES.
	auto set_up_projectile() -> void;

	/// @brief how to deal with objects getting hit by projectile.
	/// @param hit_comp       A pointer to the primitive component that was hit.
	/// @param other_actor    A pointer to the actor that the hit component collided with.
	/// @param other_comp     A pointer to the primitive component of the other actor that was involved in the collision.
	/// @param normal_impulse A vector representing the normal impulse (or force) applied to the hit component.
	/// @param hit            A reference to FHitResult object, containing info about collision, eg: location, normal, etc.
	UFUNCTION()
	void on_hit(UPrimitiveComponent* hit_comp, 
				AActor*              other_actor, 
				UPrimitiveComponent* other_comp, 
				FVector              normal_impulse, 
				const FHitResult&    hit);

	/* --------------------- COMPONENTS --------------------- */
	
	//// POINTERS TO COMPONENTS ////

	/// @brief Basic unit used to create Projectile world geometry for levels.
	UPROPERTY()
	UStaticMeshComponent* projectile_mesh_;

	/// @brief Necessary so we can move pawn around level.
	UPROPERTY()
	UProjectileMovementComponent* projectile_movement_component_;

	/// @brief Sets animation for when projectile is in motion in game.
	UPROPERTY()
	UParticleSystemComponent* trail_particles_component_;

	//// PATHS TO MESHES FOR COMPONENTS ////

	/// @brief Path to projectile mesh in Content folder.
	FString projectile_mesh_path_{ "StaticMesh'/Game/Assets/Meshes/SM_Projectile.SM_Projectile'" };

	/* ----------------------- EFFECTS ---------------------- */

	//// POINTERS TO EFFECTS ////

	/// @brief Sets sound for one projectile collides with actor and is destroyed. 
	UPROPERTY()
	USoundBase* hit_sound_;

	/// @brief Sets sound for when projectile is spawned.
	UPROPERTY()
	USoundBase* launch_sound_;

	/// @brief Sets animation for when we collide with another actor.
	UPROPERTY()
	UParticleSystem* hit_particles_;

	/// @brief Sets camera shake for when projectile hits an actor.
	UPROPERTY()
	ULegacyCameraShake* hit_camera_shake_class_;

	//// PATHS TO EFFECTS ////

	/// @brief Path to launch sound in Content folder.
	FString launch_sound_path_{ "/Game/Assets/Audio/Thud_Audio.Thud_Audio" };

	/// @brief Path to hit effect particles in Content folder.
	FString hit_particles_path_ { "/Game/Assets/Effects/P_HitEffect.P_HitEffect" };

	/// @brief Path to trailing effect particles in Content folder.
	FString trail_particles_path_{ "/Game/Assets/Effects/P_ProjectileTrail.P_ProjectileTrail" };

	/* ---------------------- PROPERTIES -------------------- */

	/// @brief The amount of damage a pawn takes when colliding with a projectile.
	UPROPERTY()
	float damage_{ 50.f };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Pawn.
	friend class Projectile_test;
};