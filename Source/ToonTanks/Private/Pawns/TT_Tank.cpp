// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "Pawns/TT_Tank.h"

// Unreal headers
#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ATT_Tank::ATT_Tank()
{
    set_up_meshes();
    set_up_input();
    
    // Set Capsule Component Properties
    capsule_comp_->SetCapsuleHalfHeight(77.f);
    capsule_comp_->SetCapsuleRadius(75.f);

    // Set Projectile Spawn Properties
    projectile_spawn_point_->SetRelativeLocation(FVector(150.f, 10.f, 90.f));

    // get camera setup correctly
    spring_arm_                           = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    spring_arm_->TargetArmLength          = 600.f;
    spring_arm_->SetRelativeRotation(FRotator(-33.f, 0.f, 0.f));
    spring_arm_->bEnableCameraLag         = true;
    spring_arm_->CameraLagSpeed           = 4.f;
    spring_arm_->bEnableCameraRotationLag = true;
    spring_arm_->CameraRotationLagSpeed   = 4.f;
    spring_arm_->SetupAttachment(RootComponent);

    camera_                               = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera_->SetupAttachment(spring_arm_);

    // need to make tank actually move
    floating_pawn_movement_               = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

}

auto ATT_Tank::BeginPlay() -> void
{
    Super::BeginPlay();

    // Add input mapping context
    player_controller_ref_ = Cast<APlayerController>(GetController());

    if (player_controller_ref_)
    {
        // store the enhanced input subsystem for getting which key is triggered.
        if (const auto enhanced_input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller_ref_->GetLocalPlayer()))
        {
            enhanced_input_subsystem->AddMappingContext(tank_mapping_context_, 0);
        }
    }
}

auto ATT_Tank::Tick(float delta_time) -> void
{
    Super::Tick(delta_time);

    if (player_controller_ref_)
    {
        // turret turning.
        FHitResult hit_result;
        player_controller_ref_->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_result);
        rotate_turret(hit_result.ImpactPoint);
    }
}

auto ATT_Tank::set_up_meshes() -> void
{
    // Set base mesh.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> base_mesh_path(*base_mesh_path_);
    if (base_mesh_path.Succeeded())
    {
        base_mesh_->SetStaticMesh(base_mesh_path.Object);
        base_mesh_->SetRelativeLocation(FVector(0.f, 0.f, -89.f));
    }

    // Set turret mesh.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> turret_mesh_path(*turret_mesh_path_);
    if (turret_mesh_path.Succeeded())
    {
        turret_mesh_->SetStaticMesh(turret_mesh_path.Object);
    }

}

auto ATT_Tank::set_up_input() -> void
{
    // Set tank mapping context.
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> tank_mapping_context_path(*tank_mapping_context_path_);
    if (tank_mapping_context_path.Succeeded())
    {
        tank_mapping_context_ = tank_mapping_context_path.Object;
    }

    // Set move input action.
    static ConstructorHelpers::FObjectFinder<UInputAction> move_action_path(*move_action_path_);
    if (move_action_path.Succeeded())
    {
        move_action_ = move_action_path.Object;
    }

    // Set turn input action.
    static ConstructorHelpers::FObjectFinder<UInputAction> turn_action_path(*turn_action_path_);
    if (turn_action_path.Succeeded())
    {
        turn_action_ = turn_action_path.Object;
    }

    // Set fire input action.
    static ConstructorHelpers::FObjectFinder<UInputAction> fire_action_path(*fire_action_path_);
    if (fire_action_path.Succeeded())
    {
        fire_action_ = fire_action_path.Object;
    }

}

// Called to bind functionality to input.
auto ATT_Tank::SetupPlayerInputComponent(UInputComponent* player_input_component) -> void
{
    Super::SetupPlayerInputComponent(player_input_component);

    // set up action bindings.
    if (UEnhancedInputComponent* enhanced_input_component = CastChecked<UEnhancedInputComponent>(player_input_component))
    {
        // moving forward and backward.
        enhanced_input_component->BindAction(move_action_, ETriggerEvent::Triggered, this, &ATT_Tank::move_forward);

        // turning side to side.
        enhanced_input_component->BindAction(turn_action_, ETriggerEvent::Triggered, this, &ATT_Tank::turn);

        // turning side to side.
        enhanced_input_component->BindAction(fire_action_, ETriggerEvent::Triggered, this, &ATT_Tank::fire);
    }

}

auto ATT_Tank::handle_destruction() -> void
{
    Super::handle_destruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    b_alive = false;
}

auto ATT_Tank::move_forward(const FInputActionValue& value) -> void
{
    // input is a float.
    auto direction_input = value.Get<float>();

    if (Controller && (direction_input != 0.f))
    {
        FVector forward_move = GetActorForwardVector();
        AddMovementInput(forward_move, direction_input * speed_ * UGameplayStatics::GetWorldDeltaSeconds(this));
    }

}

auto ATT_Tank::turn(const FInputActionValue& value) -> void
{
    // input is a float.
    float turn_input = value.Get<float>();

    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = turn_input * turn_rate_ * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

