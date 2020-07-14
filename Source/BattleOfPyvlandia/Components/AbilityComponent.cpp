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
}

void UAbilityComponent::SpawnObject(TSubclassOf<AActor> SpawnedObject)
{
	if (PlayerOwner && AbleToSpawnObject())
	{
		FVector SpawnLoc(PlayerOwner->GetActorLocation() + (PlayerOwner->GetActorForwardVector() * 100.f));
		SpawnLoc = FVector(SpawnLoc.X, SpawnLoc.Y, SpawnLoc.Z + 50.f);
		FRotator SpawnRot(PlayerOwner->GetActorForwardVector().ToOrientationRotator());

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(SpawnedObject, SpawnLoc, SpawnRot, SpawnParams);

		GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimer, this, &UAbilityComponent::SpawnDelay, SpawnDelayRate);
	}
}

void UAbilityComponent::SpawnDelay()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnDelayTimer);
}

bool UAbilityComponent::AbleToSpawnObject()
{
	if (!SpawnDelayTimer.IsValid() && GrenadeCount > 0) return true;
	else return false;
}