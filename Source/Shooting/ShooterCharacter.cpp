// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include "ShootingGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;
	
	gun = GetWorld() -> SpawnActor<AGun>(gunClass);
	GetMesh() -> HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	gun -> AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	gun -> SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	//GamePad
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	damageApply = FMath::Min(health, damageApply);
	health -= damageApply;

	if(IsDead())
	{
		AShootingGameModeBase* gameMode = GetWorld() -> GetAuthGameMode<AShootingGameModeBase>();		
		if (gameMode != nullptr)
		{
			gameMode -> PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return damageApply;

}

bool AShooterCharacter::IsDead() const
{
	return health <= 0;
}

float AShooterCharacter::GetHealth() const
{
	return health / maxHealth;
}

void AShooterCharacter::MoveForward(float _axisValue)
{
	AddMovementInput(GetActorForwardVector() * _axisValue);
}

void AShooterCharacter::MoveRight(float _axisValue)
{
	AddMovementInput(GetActorRightVector() * _axisValue);
}

// GamePad
void AShooterCharacter::LookUpRate(float _axisValue)
{
	AddControllerPitchInput(_axisValue * rotationRate * GetWorld() -> GetDeltaSeconds());
}
// GamePad
void AShooterCharacter::LookRightRate(float _axisValue)
{
	AddControllerYawInput(_axisValue * rotationRate * GetWorld() -> GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	gun -> PullTrigger();
}

