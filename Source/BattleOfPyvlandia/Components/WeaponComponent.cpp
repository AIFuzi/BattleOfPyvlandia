#include "WeaponComponent.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"
#include "..//Public/Weapons/WeaponActor.h"

UWeaponComponent::UWeaponComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicated(true);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerOwner = Cast<APlayerCharacter>(GetOwner());
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, PlayerOwner);
}

void UWeaponComponent::CreateWeapon(TSubclassOf<class AWeaponActor> WeaponClass)
{
	FVector Loc(0, 0, 0);
	FRotator Rot(0, 0, 0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Weapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass, Loc, Rot, SpawnParams);
	Weapon->WeaponOwner = PlayerOwner;
	Weapon->OnRep_WeaponOwner();

	CurrentWeapon = Weapon;
	OnRep_CurrentWeapon();
}

void UWeaponComponent::OnRep_CurrentWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(PlayerOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Sk_Weapon"));
		CurrentWeapon = Weapon;
	}
}

