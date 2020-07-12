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

	void GetShootTrace();

	void DrawInfo();
	
public:	

	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpreanAndRecoil)
		float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Ammo)
		int CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Ammo)
		int TotalAmmo;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Ammo)
		int AmmoForReload;

	UFUNCTION(BlueprintCallable, Category = Shooting)
		void UseWeapon();

	UFUNCTION(BlueprintPure, Category = Shooting)
		FVector GetShootDirection();

	UFUNCTION(BlueprintPure, Category = Shooting)
		bool AbleForUseWeapon();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_WeaponOwner)
		class APlayerCharacter* WeaponOwner;

	UFUNCTION()
		void OnRep_WeaponOwner();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void DrawDebugTrace(FVector Start, FVector End, FVector HitLocation);
		void DrawDebugTrace_Implementation(FVector Start, FVector End, FVector HitLocation);
		bool DrawDebugTrace_Validate(FVector Start, FVector End, FVector HitLocation);

private:

	int Ammo;
		
};
