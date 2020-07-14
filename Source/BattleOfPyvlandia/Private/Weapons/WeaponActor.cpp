#include "..//Public/Weapons/WeaponActor.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicatingMovement(true);
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	WeaponOwner = Cast<APlayerCharacter>(GetOwner());
	Ammo = CurrentAmmo;
}

void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponActor, WeaponOwner);

	DOREPLIFETIME(AWeaponActor, Ammo);
	DOREPLIFETIME(AWeaponActor, CurrentAmmo);
	DOREPLIFETIME(AWeaponActor, TotalAmmo);
	DOREPLIFETIME(AWeaponActor, ShootingSpeed);
}

void AWeaponActor::OnRep_WeaponOwner()
{
	if (WeaponOwner)
	{
		SetInstigator(WeaponOwner);
		SetOwner(GetInstigator()->GetController());
		if (GetLocalRole() == ROLE_Authority)
			AttachToActor(WeaponOwner, FAttachmentTransformRules::SnapToTargetIncludingScale);
		else
			AttachToComponent(WeaponOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Sk_Weapon"));
	}
	else
	{
		SetOwner(nullptr);
		SetInstigator(nullptr);
	}
}

void AWeaponActor::UseWeapon()
{
	switch (WeaponType)
	{
	case EWeaponType::Autorifle:
		GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &AWeaponActor::GetShootTrace, ShootingSpeed, true, 0.f);
		break;
	}
}

void AWeaponActor::StopUseWeapon()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

FVector AWeaponActor::GetShootDirection()
{
	float SpreadAngle;
	FVector SpreadRight;
	FVector SpreadUp;

	if (WeaponOwner)
	{
		SpreadAngle = FMath::RandRange(Spread * (-1.f), Spread);

		FVector OwnerRotaion = UKismetMathLibrary::RotateAngleAxis(
			WeaponOwner->GetActorForwardVector(),
			WeaponOwner->LookVerticaleAngle * (-1.f),
			WeaponOwner->GetActorRightVector());

		SpreadRight = UKismetMathLibrary::RotateAngleAxis(OwnerRotaion, SpreadAngle, OwnerRotaion.RightVector);

		SpreadUp = UKismetMathLibrary::RotateAngleAxis(SpreadRight, SpreadAngle, OwnerRotaion.UpVector);
	}

	return SpreadUp;
}

bool AWeaponActor::AbleForUseWeapon()
{
	if (CurrentAmmo > 0 && !Reloading) return true;
	else return false;
}

void AWeaponActor::GetShootTrace()
{
	FHitResult HitResult;

	FVector Start = WeaponOwner->GetMesh()->GetSocketLocation("Sk_Weapon");
	FVector End = Start + (GetShootDirection() * 10000.f);

	FCollisionQueryParams CollisionParams;
	FCollisionObjectQueryParams CollisionTrace;

	CollisionTrace.AllObjects;

	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(WeaponOwner);

	CurrentAmmo--;
	if (CurrentAmmo < 1) StopUseWeapon();

	OnPlayWeaponEffect.Broadcast();

	bool IsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, CollisionTrace, CollisionParams);
	if (IsHit)
	{

		DrawDebugTrace(Start, End, HitResult.Location);
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, GetInstigatorController(), WeaponOwner, UDamageType::StaticClass());
	}
}

bool AWeaponActor::AbleToReload()
{
	if (CurrentAmmo != Ammo && !IsReload && TotalAmmo > 0) return true;
	else return false;
}

void AWeaponActor::StartReload()
{
	if (!Reloading)
	{
		IsReload = true;
		Reloading = true;
		OnRep_Reloading();

		WeaponOwner->Reload = true;
	}
}

void AWeaponActor::StopReload()
{
	Reloading = false;
	OnRep_Reloading();

	IsReload = false;

	CurrentAmmo = CurrentAmmo + AmmoForReload;
	TotalAmmo = TotalAmmo - AmmoForReload;

	WeaponOwner->Reload = false;
}

void AWeaponActor::ReloadWeapon()
{
	if (AbleToReload()) StartReload();
}

void AWeaponActor::OnRep_Reloading()
{
	if (Reloading)
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AWeaponActor::StopReload, ReloadSpeed, false);
		AmmoForReload = FMath::Min(Ammo - CurrentAmmo, TotalAmmo);
		OnReloadStarted.Broadcast();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
		OnReloadFinished.Broadcast();
	}
}

void AWeaponActor::DrawDebugTrace_Implementation(FVector Start, FVector End, FVector HitLocation)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 5.f, 0, 0.f);
	DrawDebugSphere(GetWorld(), HitLocation, 15.f, 12, FColor::Red, false, 5.f, 0, 0.f);
}

bool AWeaponActor::DrawDebugTrace_Validate(FVector Start, FVector End, FVector HitLocation)
{
	return true;
}