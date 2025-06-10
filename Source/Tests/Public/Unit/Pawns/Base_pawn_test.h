// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //
#include "Pawns/TT_Base_pawn.h"


/**
 *	Test class suite to assist Unit testing for BasePawn test to access private members of class
 */
class Base_pawn_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get the pawns capsule component.
    /// @return the pawns capsule component.
    static auto get_capsule_comp(ATT_Base_pawn* base_pawn) -> UCapsuleComponent*
    {
        return base_pawn->capsule_comp_;
    }

    /// @brief Get the pawns base mesh component.
    /// @return the pawns base mesh component.
    static auto get_base_mesh(ATT_Base_pawn* base_pawn) -> UStaticMeshComponent*
    {
        return base_pawn->base_mesh_;
    }

    /// @brief Get the pawns turret mesh component.
    /// @return the pawns turret mesh component.
    static auto get_turret_mesh(ATT_Base_pawn* base_pawn) -> UStaticMeshComponent*
    {
        return base_pawn->turret_mesh_;
    }

    /// @brief Get the pawns projectile spawn point component.
    /// @return the pawns projectile spawn point component.
    static auto get_projectile_spawn_point(ATT_Base_pawn* base_pawn) -> USceneComponent*
    {
        return base_pawn->projectile_spawn_point_;
    }

    /// @brief Get the pawns health component.
    /// @return the pawns health component.
    static auto get_health_component(ATT_Base_pawn* base_pawn) -> UTT_Health_component*
    {
        return base_pawn->health_component_;
    }

    /* ----------------------- EFFECTS ---------------------- */

    /// @brief Get the pawns UParticleSystem for death particles.
    /// @return the pawns UParticleSystem for death particles.
    static auto get_death_particles_fx(ATT_Base_pawn* base_pawn) -> UParticleSystem*
    {
        return base_pawn->death_particles_;
    }

    /// @brief Get the pawns USoundBase for death sound.
    /// @return the pawns USoundBase for death sound.
    static auto get_death_sound_fx(ATT_Base_pawn* base_pawn) -> USoundBase*
    {
        return base_pawn->death_sound_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Calls toon tanks pawns fire method.
    static auto call_fire(ATT_Base_pawn* base_pawn) -> void
    {
        base_pawn->fire();
    }

    /// @brief Calls toon tanks pawns destroy method.
    static auto call_handle_destruction(ATT_Base_pawn* base_pawn) -> void
    {
        base_pawn->handle_destruction();
    }
};