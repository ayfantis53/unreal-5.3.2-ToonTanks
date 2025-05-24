// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "Pawns/TT_Tower.h"

// Unreal headers
#include "TimerManager.h"
#include "Engine/StaticMesh.h"


// Sets default values.
ATT_Tower::ATT_Tower()
{
    // Set Capsule Component Properties.
    capsule_comp_->SetCapsuleHalfHeight(74.f);
    capsule_comp_->SetCapsuleRadius(32.f);

    // Set Projectile Spawn Properties.
    projectile_spawn_point_->SetRelativeLocation(FVector(90.f, 0.f, 95.f));

    set_up_meshes();
}

auto ATT_Tower::set_up_meshes() -> void
{
    // set path for Components.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> base_mesh_path(*base_mesh_path_);
    if (base_mesh_path.Succeeded())
    {
        base_mesh_->SetStaticMesh(base_mesh_path.Object);
        base_mesh_->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> turret_mesh_path(*turret_mesh_path_);
    if (turret_mesh_path.Succeeded())
    {
        turret_mesh_->SetStaticMesh(turret_mesh_path.Object);
    }
}

auto ATT_Tower::BeginPlay() -> void
{
    Super::BeginPlay();

    tank_ref_ = Cast<ATT_Tank>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    // bound a function to our timer to be called every 2 seconds.
    GetWorldTimerManager().SetTimer(fire_rate_timer_handle_, this, &ATT_Tower::check_fire_condition, fire_rate_, true);
}

auto ATT_Tower::check_fire_condition() -> void
{
    if (tank_ref_ == nullptr)
    {
        return;
    }

    if (in_fire_range() && tank_ref_->b_alive)
    {
        fire();
    }
}

auto ATT_Tower::in_fire_range() -> bool
{
    if (tank_ref_)
    {
        float distance = FVector::Dist(GetActorLocation(), tank_ref_->GetActorLocation());

        if (distance <= fire_range_)
        {
            return true;
        }
    }

    return false;
}

auto ATT_Tower::handle_destruction() -> void
{
    Super::handle_destruction();
    Destroy();
}

// Called every frame.
auto ATT_Tower::Tick(float delta_time) -> void
{
    Super::Tick(delta_time);

    if (in_fire_range())
    {
        rotate_turret(tank_ref_->GetActorLocation());
    }
}