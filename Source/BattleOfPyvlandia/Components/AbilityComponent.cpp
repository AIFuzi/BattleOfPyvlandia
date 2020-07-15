#include "AbilityComponent.h"
#include "Net/UnrealNetwork.h"
#include "..//Public/Character/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

UAbilityComponent::UAbilityComponent()
{

}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerOwner = Cast<APlayerCharacter>(GetOwner());
}

void UAbilityComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAbilityComponent, PlayerOwner);

	DOREPLIFETIME(UAbilityComponent, GrenadeCount);
	DOREPLIFETIME(UAbilityComponent, AbilityCount);
}

void UAbilityComponent::SpawnGrenade(TSubclassOf<AActor> SpawnedObject)
{
	if (PlayerOwner && AbleToSpawnGrenade())
	{
		FVector SpawnLoc(PlayerOwner->GetActorLocation() + (PlayerOwner->GetActorForwardVector() * 100.f));
		SpawnLoc = FVector(SpawnLoc.X, SpawnLoc.Y, SpawnLoc.Z + 50.f);
		FRotator SpawnRot(PlayerOwner->GetActorForwardVector().ToOrientationRotator());

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(SpawnedObject, SpawnLoc, SpawnRot, SpawnParams);

		GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimer, this, &UAbilityComponent::SpawnDelay, SpawnDelayRate);

		GrenadeCount--;
	}
}

void UAbilityComponent::SpawnAbilityObject(TSubclassOf<AActor> AbilityObject)
{
	if (PlayerOwner && AbleToUseAbility())
	{
		FVector SpawnLoc(PlayerOwner->GetActorLocation() + (PlayerOwner->GetActorForwardVector() * 100.f));
		SpawnLoc = FVector(SpawnLoc.X, SpawnLoc.Y, SpawnLoc.Z + 50.f);
		FRotator SpawnRot(PlayerOwner->GetActorForwardVector().ToOrientationRotator());

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(AbilityObject, SpawnLoc, SpawnRot, SpawnParams);

		GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimer, this, &UAbilityComponent::SpawnDelay, SpawnDelayRate);

		AbilityCount--;

		AbilityCountRestore();
	}
}

void UAbilityComponent::SpawnDelay()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnDelayTimer);
}

void UAbilityComponent::AbilityCountRestore()
{
	switch (AbilityType)
	{
	case EAbilityType::Assault:
		RestoreTime = 10.f;
		break;
	case EAbilityType::Medic:
		RestoreTime = 20.f;
		break;
	case EAbilityType::Engineer:
		RestoreTime = 35.f;
		break;
	}
	GetWorld()->GetTimerManager().SetTimer(RestoreAbilityTimer, this, &UAbilityComponent::RestoreAbility, RestoreTime, true);
}

void UAbilityComponent::RestoreAbility()
{
	if(AbilityCount >= 2.f) GetWorld()->GetTimerManager().ClearTimer(RestoreAbilityTimer);
	AbilityCount++;
}

bool UAbilityComponent::AbleToSpawnGrenade()
{
	if (!SpawnDelayTimer.IsValid() && GrenadeCount > 0) return true;
	else return false;
}

bool UAbilityComponent::AbleToUseAbility()
{
	if (AbilityCount > 0 && !SpawnDelayTimer.IsValid()) return true;
	else return false;
}
