// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "TT_Game_mode.h"
#include "Pawns/TT_Tank.h"
#include "Pawns/TT_Tower.h"
#include "TT_Player_controller.h"
#include "UI/TT_Start_game_widget.h"
#include "UI/TT_End_game_widget.h"

// Unreal headers.
#include "Kismet/GameplayStatics.h"


ATT_Game_mode::ATT_Game_mode()
{
	// Make Tank main player in the game and will spawn at the player start.
	DefaultPawnClass      = ATT_Tank::StaticClass();
	// Make our player controller the default one for game.
	PlayerControllerClass = ATT_Player_controller::StaticClass();
}

auto ATT_Game_mode::BeginPlay() -> void
{
	Super::BeginPlay();

	handle_game_start();
}

auto ATT_Game_mode::start_game() -> void
{
	// Draw Widget.
	if (GEngine && GEngine->GameViewport)
	{
		// Get viewport.
		UGameViewportClient* view_port = GEngine->GameViewport;

		// Initialize widget.
		start_game_widget_ref_ = SNew(STT_Start_game_widget);
		view_port->AddViewportWidgetContent(SAssignNew(start_game_widget_container_, SWeakWidget)
												.PossiblyNullContent(start_game_widget_ref_));

		// Make widget seen on screen.
		start_game_widget_ref_->SetVisibility(EVisibility::Visible);
	}

}

auto ATT_Game_mode::game_over(bool b_won_game) -> void
{
	// Draw Widget.
	if (GEngine && GEngine->GameViewport)
	{
		// Get viewport.
		UGameViewportClient* view_port = GEngine->GameViewport;

		// Initialize widget.
		end_game_widget_ref_ = SNew(STT_End_game_widget);
		view_port->AddViewportWidgetContent(SAssignNew(end_game_widget_container_, SWeakWidget)
												.PossiblyNullContent(end_game_widget_ref_));

		// Set text and make widget seen on screen.
		end_game_widget_ref_->set_game_over_text(b_won_game);
		end_game_widget_ref_->SetVisibility(EVisibility::Visible);
	}
}

auto ATT_Game_mode::handle_game_start() -> void
{
	// Find out how many towers are in world.
	target_towers_ 			  = get_target_tower_count();

	tank_ref_      			  = Cast<ATT_Tank>(UGameplayStatics::GetPlayerPawn(this, 0));
	tt_player_controller_ref_ = Cast<ATT_Player_controller>(UGameplayStatics::GetPlayerController(this, 0));

	start_game();

	// Set Timer that counts down Game Start.
	if (tt_player_controller_ref_)
	{
		tt_player_controller_ref_->set_player_enabled_state(false);

		// Call another classes function to enable player control.
		FTimerHandle player_enable_timer_handle;
		FTimerDelegate player_enable_timer_delegate = FTimerDelegate::CreateUObject(tt_player_controller_ref_, 
																					&ATT_Player_controller::set_player_enabled_state, 
																					true);
		GetWorldTimerManager().SetTimer(player_enable_timer_handle, player_enable_timer_delegate, start_delay_, false);
		
		// Call this classes function to remove widget.
		FTimerHandle widget_remove_timer_handle;
		GetWorldTimerManager().SetTimer(widget_remove_timer_handle, this, &ATT_Game_mode::remove_widget, start_delay_, false);
	}
}

auto ATT_Game_mode::remove_widget() -> void
{
	// Remove Widget.
	if (GEngine && GEngine->GameViewport && start_game_widget_container_.IsValid())
	{
		// Get viewport.
		UGameViewportClient* view_port = GEngine->GameViewport;

		// Take widget off viewport.
		view_port->RemoveViewportWidgetContent(start_game_widget_container_.ToSharedRef());
	}
}

auto ATT_Game_mode::actor_died(AActor* dead_actor) -> void
{
	if (dead_actor == tank_ref_)
	{
		// Tank Player Died.
		tank_ref_->handle_destruction();
		
		if (tt_player_controller_ref_)
		{
			tt_player_controller_ref_->set_player_enabled_state(false);
		}

		game_over(false);
	}
	else if (ATT_Tower* destroyed_tower_ = Cast<ATT_Tower>(dead_actor))
	{
		// Enemy Turret Died.
		destroyed_tower_->handle_destruction();
		--target_towers_;

		if (target_towers_ == 0)
		{
			game_over(true);
		}
	}
}

auto ATT_Game_mode::get_target_tower_count() -> int32
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATT_Tower::StaticClass(), towers);

	return towers.Num();
}