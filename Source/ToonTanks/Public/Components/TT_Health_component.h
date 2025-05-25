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

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TT_Health_component.generated.h"


class ATT_Game_mode;

/**
 *	Component that deals with life of whatever pawn its attached to
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UTT_Health_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// @brief Sets default values for this component's properties.
	UTT_Health_component();

	/// @brief Called every frame
	/// @param delta_time         For time-based calculations and consistent behavior regardless of frame rate.
	/// @param tick_type          An enum of type ELevelTick that specifies the type of tick being executed. (LEVELTICK_Normal, LEVELTICK_TimeOnly, or LEVELTICK_PauseTick).
	/// @param this_tick_function A pointer to struct that provides access to properties and functions related to the tick execution, such as enabling or disabling ticking.
	virtual auto TickComponent(float      				    delta_time, 
							   ELevelTick 				    tick_type, 
							   FActorComponentTickFunction* this_tick_function) -> void override;

protected:
	/// @brief Called when the game starts.
	virtual auto BeginPlay() -> void override;

	/// @brief Called when the game starts.
	/// @param damaged_actor  This refers to the actor that is receiving the damage. 
	/// @param damage         Represents the amount of health that is being reduced from the DamagedActor. 
	/// @param damage_type    type of damage (e.g. fire, blunt, etc.) and influences how the damage is handled or what effects are applied. 
	/// @param instigator     This is the controller that is responsible for dealing the damage, such as a player or AI. 
	/// @param damage_causer  This is the actor that physically caused the damage, such as a projectile or explosion. 
	UFUNCTION()
	void damage_taken(AActor*            damaged_actor, 
					  float              damage, 
					  const UDamageType* damage_type, 
					  class AController* instigator, 
					  AActor*            damage_causer);

private:
	/* --------------------- REFERENCES --------------------- */
	
	/// @brief Reference to the game mode so we now to end game or not.
	ATT_Game_mode* toon_tanks_game_mode_ref_;

	/* ---------------- HEALTH PROPERTIES ---------------- */

	/// @brief Amount of damage taken on each hit from projectile.
	float damaged_{ 50.f }; 

	/// @brief Current health of pawn.
	float health_{ 0.f };

	/// @brief Maximum starting health of pawn.
	float max_health_{ 100.f };	

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Component.
	friend class Health_component_test;

	/// @brief Test classes to function test this Component.
	friend class ATT_functional_test_tower;
	friend class ATT_functional_test_widgets;
};
