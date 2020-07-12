#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadFinished);

UCLASS()
class BATTLEOFPYVLANDIA_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeaponActor();

protected:

	virtual void BeginPlay() override;

	void GetShootTrace();


protected:

	bool IsReload;

	FTimerHandle ReloadTimer;

	bool AbleToReload();
	void StartReload();
	void StopReload();
	
public:	

	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(BlueprintAssignable, Category = Reload)
		FReloadStarted OnReloadStarted;

	UPROPERTY(BlueprintAssignable, Category = Reload)
		FReloadFinished OnReloadFinished;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpreanAndRecoil)
		float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Ammo)
		int CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Ammo)
		int TotalAmmo;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Ammo)
		int AmmoForReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reload)
		float ReloadSpeed;

	UFUNCTION(BlueprintCallable, Category = Shooting)
		void UseWeapon();

	UFUNCTION(BlueprintPure, Category = Shooting)
		FVector GetShootDirection();

	UFUNCTION(BlueprintPure, Category = Shooting)
		bool AbleForUseWeapon();

	UFUNCTION(BlueprintCallable, Category = Reload)
		void ReloadWeapon();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_WeaponOwner)
		class APlayerCharacter* WeaponOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Reloading, Category = Reload)
		bool Reloading;

	UFUNCTION()
		virtual void OnRep_Reloading();

	UFUNCTION()
		void OnRep_WeaponOwner();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void DrawDebugTrace(FVector Start, FVector End, FVector HitLocation);
		void DrawDebugTrace_Implementation(FVector Start, FVector End, FVector HitLocation);
		bool DrawDebugTrace_Validate(FVector Start, FVector End, FVector HitLocation);

private:

	UPROPERTY(Replicated)
		int Ammo;
		
};
