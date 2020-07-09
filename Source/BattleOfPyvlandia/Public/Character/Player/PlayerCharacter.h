#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BATTLEOFPYVLANDIA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;

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
		class UCameraComponent* FPS_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		class USkeletalMeshComponent* FPS_Arms;

};
