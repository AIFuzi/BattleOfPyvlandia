#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	Assault				UMETA(DisplayName = "Assault"),
	Medic				UMETA(DisplayName = "Medic"),
	Engineer			UMETA(DisplayName = "Engineer")
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEOFPYVLANDIA_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAbilityComponent();

protected:

	FTimerHandle SpawnDelayTimer;
	FTimerHandle RestoreAbilityTimer;

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;

	void SpawnDelay();
	void AbilityCountRestore();
	void RestoreAbility();

	UPROPERTY(Replicated)
		class APlayerCharacter* PlayerOwner;

	float RestoreTime;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		EAbilityType AbilityType;

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
