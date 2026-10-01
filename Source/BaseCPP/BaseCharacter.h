// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputAction;
struct FInputActionValue;

UCLASS()
class BASECPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<USpringArmComponent>SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent>Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction>IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction>IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction>IA_MouseLook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction>IA_Anim;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	//TObjectPtr<UAnimationAsset>IdleAnimation;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	//TObjectPtr<UAnimationAsset>JogAnimation;

public:
	void Move(const FInputActionValue& Value);
	void MouseLook(const FInputActionValue& Value);
	void StartAnim(const FInputActionValue& Value);
	void StopAnim(const FInputActionValue& Value);

};
