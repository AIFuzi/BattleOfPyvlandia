#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

//UENUM(BlueprintType)
//enum class EClassType : uint8
//{
//	Assault				UMETA(DisplayName = "Assault"),
//	Medic				UMETA(DisplayName = "Medic"),
//	Engineer			UMETA(DisplayName = "Engineer")
//};

UCLASS()
class BATTLEOFPYVLANDIA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void MoveForward(float Val);
	void MoveRight(float Val);

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		class UCameraComponent* TPS_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		class USkeletalMeshComponent* FPS_Arms;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	//	EClassType PlayerClassType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
		bool IsSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = Player)
		FVector LookAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = Player)
		float LookVerticaleAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = Animation)
		bool Reload;

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = Movement)
		void Client_Sprint(float Val);
		void Client_Sprint_Implementation(float Val);
		bool Client_Sprint_Validate(float Val);

	UFUNCTION(Server, Reliable, WithValidation, Category = Movement)
		void Server_Sprint(float Val);
		void Server_Sprint_Implementation(float Val);
		bool Server_Sprint_Validate(float Val);

};
