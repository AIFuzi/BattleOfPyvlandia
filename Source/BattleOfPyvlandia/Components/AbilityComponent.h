#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEOFPYVLANDIA_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAbilityComponent();

protected:

	FTimerHandle SpawnDelayTimer;

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;

	void SpawnDelay();

	UPROPERTY(Replicated)
		class APlayerCharacter* PlayerOwner;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grenade)
		int GrenadeCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		float SpawnDelayRate;

	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SpawnGrenade(TSubclassOf<AActor> SpawnedObject);

	UFUNCTION(BlueprintPure, Category = Spawn)
		bool AbleToSpawnGrenade();


};
