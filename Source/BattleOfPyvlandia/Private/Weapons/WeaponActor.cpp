#include "..//Public/Weapons/WeaponActor.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponActor, WeaponOwner);
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
	GetShootTrace();
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

	bool IsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, CollisionTrace, CollisionParams);
	if (IsHit)
	{
		DrawDebugTrace(Start, End, HitResult.Location);
	}
}

void AWeaponActor::DrawInfo()
{

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