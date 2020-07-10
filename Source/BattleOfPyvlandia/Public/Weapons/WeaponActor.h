#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class BATTLEOFPYVLANDIA_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeaponActor();

protected:

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_WeaponOwner)
		class APlayerCharacter* WeaponOwner;

	UFUNCTION(BlueprintCallable, Category = Shooting)
		void GetShootTrace();

	UFUNCTION()
		void OnRep_WeaponOwner();

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = Debug)
		void DrawDebugTrace(FVector Start, FVector End, FVector HitLoc, AActor* HitActor);
		void DrawDebugTrace_Implementation(FVector Start, FVector End, FVector HitLoc, AActor* HitActor);
		bool DrawDebugTrace_Validate(FVector Start, FVector End, FVector HitLoc, AActor* HitActor);

};
