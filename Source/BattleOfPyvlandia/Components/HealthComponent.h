#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEnded);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEOFPYVLANDIA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

protected:

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
		float Health;

	UPROPERTY(BlueprintAssignable, Category = Health)
		FHealthEnded OnHealthEnded;

	UFUNCTION(BlueprintCallable, Category = Health)
		void GetDamage(float Damage, bool & CharacterDeath);
};
