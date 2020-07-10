#include "..//Public/Weapons/WeaponActor.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"

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
		DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		SetInstigator(nullptr);
		SetOwner(nullptr);
	}
}

