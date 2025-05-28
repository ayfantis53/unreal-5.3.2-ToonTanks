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
#include "FX/TT_Camera_shake.h"

// Unreal headers
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ATT_Projectile::ATT_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick                 = true;

	// Setup Projectile mesh.
	projectile_mesh_ 			                  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(projectile_mesh_);

	// set path for Components.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>projectile_mesh_path(*projectile_mesh_path_);
	if (projectile_mesh_path.Succeeded())
	{
		projectile_mesh_->SetStaticMesh(projectile_mesh_path.Object);
	}

	// Setup movement.
	projectile_movement_component_               = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	projectile_movement_component_->MaxSpeed     = 1300.f;
	projectile_movement_component_->InitialSpeed = 1300.f;

	// Projectile Smoke Trail.
	trail_particles_component_                   = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	trail_particles_component_->SetupAttachment(RootComponent);

	// set path for death_particles.
	static ConstructorHelpers::FObjectFinder<UParticleSystem>trail_particles_path(*trail_particles_path_);
	if (trail_particles_path.Succeeded())
	{
		trail_particles_component_->SetTemplate(trail_particles_path.Object);
	}

	// Find uassets that correlate with the launch and hit FX.
	set_up_projectile();
}

auto ATT_Projectile::BeginPlay() -> void
{
	Super::BeginPlay();

	// Bind to delegate.
	projectile_mesh_->OnComponentHit.AddDynamic(this, &ATT_Projectile::on_hit);

	// Play launch sound.
	if (launch_sound_)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launch_sound_, GetActorLocation(), GetActorRotation());
	}

}

auto ATT_Projectile::Tick(float delta_time) -> void
{
	Super::Tick(delta_time);
}

auto ATT_Projectile::set_up_projectile() -> void
{
	// Set Fire Sound.
	static ConstructorHelpers::FObjectFinder<USoundBase>launch_sound_path(*launch_sound_path_);
	if (launch_sound_path.Succeeded())
	{
		launch_sound_ = launch_sound_path.Object;
	}
	// Set hit particles.
	static ConstructorHelpers::FObjectFinder<UParticleSystem>hit_particles_path(*hit_particles_path_);
	if (hit_particles_path.Succeeded())
	{
		hit_particles_ = hit_particles_path.Object;
	}
	// Set Hit Sound.
	static ConstructorHelpers::FObjectFinder<USoundBase>hit_sound_path(*launch_sound_path_);
	if (hit_sound_path.Succeeded())
	{
		hit_sound_ = hit_sound_path.Object;
	}
}

auto ATT_Projectile::on_hit(UPrimitiveComponent* hit_comp, 
							AActor*              other_actor, 
							UPrimitiveComponent* other_comp, 
							FVector              normal_impulse, 
							const FHitResult&    hit) -> void
{
	// Find out who is Firing projectile(this).
	AActor* my_owner = GetOwner();
	if (my_owner == nullptr)
	{
		Destroy();
		return;
	}

	AController* my_owner_instigator = my_owner->GetInstigatorController();
	UClass*      damage_type_class   = UDamageType::StaticClass();

	if (other_actor && other_actor != this && other_actor != my_owner)
	{
		UGameplayStatics::ApplyDamage(other_actor, damage_, my_owner_instigator, this, damage_type_class);
		
		// Hit Effects.
		if (hit_particles_)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hit_particles_, GetActorLocation(), GetActorRotation());
		}
		// Hit Sounds.
		if (hit_sound_)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hit_sound_, GetActorLocation(), GetActorRotation());
		}
		// Camera Shake Anim.
		if (auto controller = GetWorld()->GetFirstPlayerController())
		{
			controller->ClientStartCameraShake(UTT_Camera_shake::StaticClass());
		}
	}

	Destroy();
}

