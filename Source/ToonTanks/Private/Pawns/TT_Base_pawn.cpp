// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Pawns/TT_Base_pawn.h"
#include "Pawns/TT_Projectile.h"
#include "FX/TT_Camera_shake_death.h"
#include "Components/TT_Health_component.h"

// Unreal headers
#include "Particles/ParticleSystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
//#include "DrawDebugHelpers.h"


ATT_Base_pawn::ATT_Base_pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Capsule setup
	capsule_comp_           = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	capsule_comp_->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(capsule_comp_);

	// Base mesh setup.
	base_mesh_              = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	base_mesh_->SetupAttachment(capsule_comp_);

	// Turret mesh setup.
	turret_mesh_            = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turret_mesh_->SetupAttachment(base_mesh_);

	// Projectile spawn setup.
	projectile_spawn_point_ = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectile_spawn_point_->SetupAttachment(turret_mesh_);

	// Health setup
	health_component_       = CreateDefaultSubobject<UTT_Health_component>(TEXT("Health Component"));

	// Find uassets that correlate with the death FX.
	set_up_base_pawn();
}

auto ATT_Base_pawn::set_up_base_pawn() -> void
{
	// Set Death Particles.
	static  ConstructorHelpers::FObjectFinder<UParticleSystem>death_particle_path(*death_particle_path_);
	if (death_particle_path.Succeeded())
	{
		death_particles_ = death_particle_path.Object;
	}

	// Set Death Sound.
	static  ConstructorHelpers::FObjectFinder<USoundBase>death_sound_path(*death_sound_path_);
	if (death_sound_path.Succeeded())
	{
		death_sound_ = death_sound_path.Object;
	}
}
	

auto ATT_Base_pawn::rotate_turret(FVector look_at_target) -> void
{
	FVector to_target         = look_at_target - turret_mesh_->GetComponentLocation();
	FRotator look_at_rotation = FRotator(0.f, to_target.Rotation().Yaw, 0.f);

	// Have the tank turret point to where mouse is on screen.
	turret_mesh_->SetWorldRotation(FMath::RInterpTo(turret_mesh_->GetComponentRotation(), look_at_rotation, UGameplayStatics::GetWorldDeltaSeconds(this), 13.f));
}

auto ATT_Base_pawn::fire() -> void
{
	FVector location           = projectile_spawn_point_->GetComponentLocation();
	FRotator rotation          = projectile_spawn_point_->GetComponentRotation();

	ATT_Projectile* projectile = GetWorld()->SpawnActor<ATT_Projectile>(location, rotation);

	// Let Projectile know who is firing it.
	projectile->SetOwner(this);

	//DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, false, 3.f);
}

auto ATT_Base_pawn::handle_destruction() -> void
{
	if (death_particles_)
	{
		// Death Particle Effects.
		UGameplayStatics::SpawnEmitterAtLocation(this, death_particles_, GetActorLocation(), GetActorRotation());
	}
	if (death_sound_)
	{
		// Death Sound Effects.
		UGameplayStatics::PlaySoundAtLocation(this, death_sound_, GetActorLocation(), GetActorRotation());
	}
	// Camera Shake Anim.
	if (auto controller = GetWorld()->GetFirstPlayerController())
	{
		controller->ClientStartCameraShake(UTT_Camera_shake_death::StaticClass());
	}
}
