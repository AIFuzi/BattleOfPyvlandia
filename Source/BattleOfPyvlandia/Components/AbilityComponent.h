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

	virtual void BeginPlay() override;

		
};
