// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SHOOTING_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	void Shoot();


private:
	void MoveForward(float _axisValue);
	void MoveRight(float _axisValue);
	void LookUpRate(float _axisValue);
	void LookRightRate(float _axisValue);

	UPROPERTY(EditAnywhere)
	float rotationRate = 10;
	UPROPERTY(EditDefaultsOnly)
	float maxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> gunClass;

	UPROPERTY()
	AGun* gun;
};
