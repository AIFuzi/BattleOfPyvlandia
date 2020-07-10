#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEOFPYVLANDIA_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(Replicated)
		class APlayerCharacter* PlayerOwner;

	class AWeaponActor* Weapon;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentWeapon)
		class AWeaponActor* CurrentWeapon;

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void CreateWeapon(TSubclassOf<class AWeaponActor> WeaponClass);

	UFUNCTION()
		void OnRep_CurrentWeapon();
};
