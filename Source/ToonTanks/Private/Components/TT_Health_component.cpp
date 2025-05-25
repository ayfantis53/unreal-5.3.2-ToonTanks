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
#include "TT_Game_mode.h"

// Unreal headers
#include "Kismet/GameplayStatics.h"


UTT_Health_component::UTT_Health_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

auto UTT_Health_component::BeginPlay() -> void
{
	Super::BeginPlay();

	// Initialize Full health at Start of Game.
	health_ = max_health_;

	// Bind Function to Unreal Delegate.
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UTT_Health_component::damage_taken);

	toon_tanks_game_mode_ref_ = Cast<ATT_Game_mode>(UGameplayStatics::GetGameMode(this));
}

auto UTT_Health_component::TickComponent(float      				  delta_time, 
										 ELevelTick 				  tick_type, 
										 FActorComponentTickFunction* this_tick_function) -> void
{
	Super::TickComponent(delta_time, tick_type, this_tick_function);
}

auto UTT_Health_component::damage_taken(AActor* 		   damaged_actor, 
									    float   		   damage, 
										const UDamageType* damage_type, 
										class AController* instigator, 
										AActor* 		   damage_causer) -> void
{
	// Health cannot be less than 0.
	if (damage <= 0.f)
	{
		return;
	}

	// Subtract damage recieved from health.
	health_ -= damage;

	// Kill Pawn if its health reaches 0 or less.
	if (health_ <= 0.f && toon_tanks_game_mode_ref_)
	{
		toon_tanks_game_mode_ref_->actor_died(damaged_actor);
	}
}
