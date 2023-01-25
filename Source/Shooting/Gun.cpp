// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	meshComponent -> SetupAttachment(root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, meshComponent, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(muzzleSound, meshComponent, TEXT("MuzzleFlashSocket"));

	FHitResult hit;
	FVector shotDirection;
	bool isSuccess = GunTrace(hit, shotDirection);
	if(isSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impactEffect, hit.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), impactSound, hit.Location);
		AActor* hitActor = hit.GetActor();
		if(hitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(damage, hit, shotDirection, nullptr);
			AController *ownerController = GetOwnerController();
			hitActor -> TakeDamage(damage, DamageEvent, ownerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& _hit, FVector& _shotDirection)
{
	AController *ownerController = GetOwnerController();
	if(ownerController == nullptr) return false;
	FVector location;
	FRotator rotation;
	ownerController -> GetPlayerViewPoint(location, rotation);
	_shotDirection = -rotation.Vector();

	FVector end = location + rotation.Vector() * maxRange;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());
	return GetWorld() -> LineTraceSingleByChannel(_hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, params);	
}

AController* AGun::GetOwnerController() const
{
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if(ownerPawn == nullptr) return nullptr;
	return ownerPawn -> GetController();
}

