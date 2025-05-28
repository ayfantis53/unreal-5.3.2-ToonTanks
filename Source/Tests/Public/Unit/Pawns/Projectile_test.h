// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //
#include "Pawns/TT_Projectile.h"


/**
 *	Test class suite to assist Unit testing for Projectile test to access private members of class
 */
class Projectile_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get the projectile mesh component.
    /// @return the projectile mesh component.
    static auto get_projectile_mesh(ATT_Projectile* projectile) -> UStaticMeshComponent*
    {
        return projectile->projectile_mesh_;
    }

    /// @brief Get the projectile's movement component.
    /// @return the pawns projectile's movement component.
    static auto get_projectile_movement_component(ATT_Projectile* projectile) -> UProjectileMovementComponent*
    {
        return projectile->projectile_movement_component_;
    }

    /// @brief Get the projectile's trail particle's component.
    /// @return the projectile's trail particle's component.
    static auto get_trail_particles_component(ATT_Projectile* projectile) -> UParticleSystemComponent*
    {
        return projectile->trail_particles_component_;
    }

    /* ----------------------- EFFECTS ---------------------- */

    /// @brief Get the projectile's hit particles.
    /// @return the projectile's hit particles.
    static auto get_hit_particles_fx(ATT_Projectile* projectile) -> UParticleSystem*
    {
        return projectile->hit_particles_;
    }

    /// @brief Get the projectile's USoundBase for launching sound.
    /// @return the projectile's USoundBase for launching sound.
    static auto get_launch_sound_fx(ATT_Projectile* projectile) -> USoundBase*
    {
        return projectile->launch_sound_;
    }

    /// @brief Get the projectile's USoundBase for making impact sound.
    /// @return the projectile's USoundBase for making impact sound.
    static auto get_hit_sound_fx(ATT_Projectile* projectile) -> USoundBase*
    {
        return projectile->hit_sound_;
    }
};