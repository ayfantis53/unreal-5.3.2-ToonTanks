// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#include "Pawns/TT_Tower.h"


/**
 *	Test class suite to assist Unit testing for Tower test to access private members of class
 */
class Tower_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get the tower capsule component.
    /// @return the tower UCapsuleComponent.
    static auto get_tower_capsule_comp(ATT_Tower* tower) -> UCapsuleComponent*
    {
        return tower->capsule_comp_;
    }

    /// @brief Get the tower base mesh component.
    /// @return the tower base UStaticMeshComponent.
    static auto get_tower_base_mesh(ATT_Tower* tower) -> UStaticMeshComponent*
    {
        return tower->base_mesh_;
    }

    /// @brief Get the tower turret mesh component.
    /// @return the tower turret UStaticMeshComponent.
    static auto get_tower_turret_mesh(ATT_Tower* tower) -> UStaticMeshComponent*
    {
        return tower->turret_mesh_;
    }

    /// @brief Get the tower projectile spawn location.
    /// @return the tower projectile location USceneComponent.
    static auto get_projectile_spawn_point(ATT_Tower* tower) -> USceneComponent*
    {
        return tower->projectile_spawn_point_;
    }

    /// @brief Get the tower fire rate timer handle.
    /// @return the tower fire timer handle FTimerHandle.
    static auto get_fire_rate_timer_handle(ATT_Tower* tower) -> FTimerHandle
    {
        return tower->fire_rate_timer_handle_;
    }

    /* --------------------- REFERENCES --------------------- */

    /// @brief Get the tower's tank reference.
    /// @return the pawns tank's ATT_Tank reference.
    static auto get_towers_tank_ref(ATT_Tower* tower) -> ATT_Tank*
    {
        return tower->tank_ref_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Get the tower fire rate timer handle.
    static auto call_in_fire_range(ATT_Tower* tower) -> bool
    {
        return tower->in_fire_range();
    }

    /// @brief Get the tower fire rate timer handle.
    static auto call_handle_destruction(ATT_Tower* tower) -> void
    {
        return tower->handle_destruction();
    }
};