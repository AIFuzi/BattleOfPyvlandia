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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Grenade)
		int GrenadeCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Grenade)
		int AbilityCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		float SpawnDelayRate;

	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SpawnGrenade(TSubclassOf<AActor> SpawnedObject);

	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SpawnAbilityObject(TSubclassOf<AActor> AbilityObject);

	UFUNCTION(BlueprintPure, Category = Spawn)
		bool AbleToSpawnGrenade();

	UFUNCTION(BlueprintPure, Category = Spawn)
		bool AbleToUseAbility();

};
