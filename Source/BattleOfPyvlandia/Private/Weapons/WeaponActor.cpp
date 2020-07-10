#include "..//Public/Weapons/WeaponActor.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

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
}

void AWeaponActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponActor, WeaponOwner);


}

void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::GetShootTrace()
{
	FHitResult HitOut;
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetInstigator());
	if (Player)
	{
		FVector Start = Player->TPS_Camera->GetComponentLocation();
		FVector End = Start + (Player->TPS_Camera->GetForwardVector() * 10000.f);

		DrawDebugTrace(Start, End, End, nullptr);
	}
}

void AWeaponActor::OnRep_WeaponOwner()
{
	if (WeaponOwner)
	{
		SetInstigator(WeaponOwner);
		SetOwner(GetInstigator()->GetController());

		if (GetLocalRole() != ROLE_Authority)
			AttachToActor(WeaponOwner, FAttachmentTransformRules::SnapToTargetIncludingScale);
		else
			AttachToComponent(WeaponOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Sk_Weapon"));
	}
	else
	{
		DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		SetInstigator(nullptr);
		SetOwner(nullptr);
	}
}

void AWeaponActor::DrawDebugTrace_Implementation(FVector Start, FVector End, FVector HitLoc, AActor* HitActor)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 5.f, 0, 0.f);
	DrawDebugSphere(GetWorld(), HitLoc, 15.f, 12, FColor::Green, false, 5.f, 0, 0.f);
}

bool AWeaponActor::DrawDebugTrace_Validate(FVector Start, FVector End, FVector HitLoc, AActor* HitActor)
{
	return true;
}

