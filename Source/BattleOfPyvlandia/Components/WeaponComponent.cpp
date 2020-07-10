#include "WeaponComponent.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"
#include "..//Public/Weapons/WeaponActor.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerOwner = Cast<APlayerCharacter>(GetOwner());
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, PlayerOwner);
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::CreateWeapon(TSubclassOf<class AWeaponActor> WeaponClass)
{
	FVector SpawnLoc(0.f, 0.f, 0.f);
	FRotator SpawnRot(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Weapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass, SpawnLoc, SpawnRot, SpawnParams);
	Weapon->OnRep_WeaponOwner();

	CurrentWeapon = Weapon;
	OnRep_CurrentWeapon();
}

void UWeaponComponent::OnRep_CurrentWeapon()
{
	if (!GetWorld()->IsServer())
	{
		if (CurrentWeapon)
		{
			CurrentWeapon->AttachToComponent(PlayerOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Sk_Weapon"));
		}
	}
}

