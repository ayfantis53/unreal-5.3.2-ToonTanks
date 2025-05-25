// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //
#include "Components/TT_Health_component.h"
#include "Pawns/TT_Tank.h"


/**
 *	Test class suite to assist Unit testing for Health Component test to access private members of class
 */
class Health_component_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get health component.
    /// @return UTT_Health_component*.
    static auto get_health_component(ATT_Tank* tank) -> UTT_Health_component*
    {
        return tank->health_component_;
    }

    /// @brief Get health of health component.
    /// @return float.
    static auto get_health_value(UTT_Health_component* health_comp) -> float
    {
        return health_comp->health_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Calls toon tanks health component damage taken method.
    static auto call_take_damage(UTT_Health_component* health_comp,
                                 AActor* 		       damaged_actor, 
                                 float   		       damage, 
                                 const UDamageType*    damage_type, 
                                 class AController*    instigator, 
                                 AActor* 		       damage_causer) -> void
    {
        return health_comp->damage_taken(damaged_actor, 
                                         damage,  
                                         damage_type, 
                                         instigator, 
                                         damage_causer);
    }
};