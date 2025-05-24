// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#include "Pawns/TT_Tank.h"


/**
 *	Test class suite to assist Unit testing for Tank test to access private members of class
 */
class Tank_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get the tank base mesh component.
    /// @return the tank base UStaticMeshComponent.
    static auto get_tank_base_mesh(ATT_Tank* tank) -> UStaticMeshComponent*
    {
        return tank->base_mesh_;
    }

    /// @brief Get the tank turret mesh component.
    /// @return the tank turret UStaticMeshComponent.
    static auto get_tank_turret_mesh(ATT_Tank* tank) -> UStaticMeshComponent*
    {
        return tank->turret_mesh_;
    }


    /// @brief Get the tank's movement component.
    /// @return the pawns tank's movement component.
    static auto get_tank_movement_component(ATT_Tank* tank) -> UFloatingPawnMovement*
    {
        return tank->floating_pawn_movement_;
    }

    /// @brief Get the tank's camera component.
    /// @return the pawns tank's camera component.
    static auto get_tank_camera(ATT_Tank* tank) -> UCameraComponent*
    {
        return tank->camera_;
    }

    /// @brief Get the tank's spring_arm component.
    /// @return the pawns tank's spring_arm component.
    static auto get_tank_spring_arm(ATT_Tank* tank) -> USpringArmComponent*
    {
        return tank->spring_arm_;
    }

    /* --------------------- REFERENCES --------------------- */

    /// @brief Get the tank's player controller reference.
    /// @return the pawns tank's APlayerController reference.
    static auto get_player_controller(ATT_Tank* tank) -> APlayerController*
    {
        return tank->player_controller_ref_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Destroy the tank.
    static auto call_handle_destruction(ATT_Tank* tank) -> void
    {
        return tank->handle_destruction();
    }
};