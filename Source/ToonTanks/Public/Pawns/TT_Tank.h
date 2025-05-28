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
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "CoreMinimal.h"
#include "Pawns/TT_Base_pawn.h"
#include "TT_Tank.generated.h"


class UCameraComponent;
class USpringArmComponent;

/**
 *	Class that sets up Tank that Player will use when playing game 
 */
UCLASS()
class TOONTANKS_API ATT_Tank : public ATT_Base_pawn
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this pawn's properties.
	ATT_Tank();

	/// @brief Called every frame
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	virtual auto Tick(float delta_time) -> void override;

	/// @brief Called to bind functionality to input.
	/// @param player_input_component Allows a Pawn to set up custom input bindings.
	virtual auto SetupPlayerInputComponent(class UInputComponent* player_input_component) -> void override;

	/// @brief
	void handle_destruction();

	/// @brief Tells us if tank is alive for GameMode.
	bool b_alive{ true };

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Populates meshes with correct filepaths.
	auto set_up_meshes() -> void;

	/// @brief Populates inputs filepaths.
	auto set_up_input() -> void;

	/// @brief Moves tank forward and backward.
	/// @param value struct in UE5s Enhanced Input system that encapsulates the value of an input action.
	auto move_forward(const FInputActionValue& value) -> void;

	/// @brief Side to Side Tank Motion.
	/// @param value struct in UE5s Enhanced Input system that encapsulates the value of an input action.
	auto turn(const FInputActionValue& value) -> void;

	/* --------------------- REFERENCES --------------------- */

	/// @brief Reference to player controller.
	APlayerController* player_controller_ref_;

	/* --------------------- COMPONENTS --------------------- */

	//// POINTERS TO COMPONENTS ////

	/// @brief Represents a camera viewpoint and settings.
	UPROPERTY()
	UCameraComponent* camera_;

	/// @brief Maintains fixed distance from parent, retracts the children in collision, and spring back when not.
	UPROPERTY()
	USpringArmComponent* spring_arm_;

	/// @brief: Updates position in tick, provides simple movement for any Pawn class. 
	UPROPERTY()
	UFloatingPawnMovement* floating_pawn_movement_;

	//// PATHS TO MESH COMPONENTS ////

	/// @brief Path to tank base static mesh in Content folder.
	FString base_mesh_path_{ "StaticMesh'/Game/Assets/Meshes/SM_TankBase.SM_TankBase'" };

	/// @brief Path to tank turret static mesh in Content folder.
	FString turret_mesh_path_{ "StaticMesh'/Game/Assets/Meshes/SM_TankTurret.SM_TankTurret'" };

	/* -------------------- INPUT ACTIONS ------------------- */

	//// POINTERS TO INPUT ACTIONS ////

	/// @brief Mapping Context for input, passed to player subsystem.
	UPROPERTY()
	UInputMappingContext* tank_mapping_context_;

	/// @brief Mapping Context for forward move input, passed to player subsystem.
	UPROPERTY()
	UInputAction* move_action_;

	/// @brief Mapping Context for turning movement input, passed to player subsystem.
	UPROPERTY()
	UInputAction* turn_action_;

	/// @brief Mapping Context for shooting input, passed to player subsystem.
	UPROPERTY()
	UInputAction* fire_action_;

	//// PATHS TO INPUT ACTIONS ////

	/// @brief Path to tank turret static mesh in Content folder.
	FString tank_mapping_context_path_{ "/Game/Inputs/IMC_TankContext.IMC_TankContext" };

	/// @brief Path to tank turret static mesh in Content folder.
	FString move_action_path_{ "/Game/Inputs/Actions/IA_Move.IA_Move" };

	/// @brief Path to tank turret static mesh in Content folder.
	FString turn_action_path_{ "/Game/Inputs/Actions/IA_Turn.IA_Turn" };

	/// @brief Path to tank turret static mesh in Content folder.
	FString fire_action_path_{ "/Game/Inputs/Actions/IA_Fire.IA_Fire" };

	//// PROPERTIES OF INPUT ACTIONS ////

	/// @brief Speed of tank for player.
	float speed_{ 300.f };

	/// @brief TurnRate of tank for player.
	float turn_rate_{ 120.f };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Pawn.
	friend class Tank_test;
	friend class Health_component_test;

	/// @brief Test classes to function test this Pawn.
	friend class ATT_functional_test_base;
	friend class ATT_functional_test_tank;
};
