// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90, 0)
	);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>((TEXT("SpringArm")));
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	SpringArm->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//static bool bIdle = false;
	//static bool bJog = false;

	//if (GetCharacterMovement()->Velocity.SizeSquared() == 0)
	//{
	//	if (!bIdle)
	//	{
	//		bIdle != bIdle;
	//		bJog != bJog;
	//		GetMesh()->PlayAnimation(IdleAnimation,true);
	//		
	//	}
	//}
	//else 
	//{
	//	if (!bJog)
	//	{
	//		bIdle != bIdle;
	//		bJog != bJog;
	//		GetMesh()->PlayAnimation(JogAnimation, true);
	//	}
	//}

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
		UIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &ABaseCharacter::StopJumping);

		UIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		UIC->BindAction(IA_MouseLook, ETriggerEvent::Triggered, this, &ABaseCharacter::MouseLook);

		UIC->BindAction(IA_Anim, ETriggerEvent::Started, this, &ABaseCharacter::StartAnim);
		UIC->BindAction(IA_Anim, ETriggerEvent::Completed, this, &ABaseCharacter::StopAnim);
	}

}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	
	AddMovementInput(
		UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)) * Direction.X);
	AddMovementInput(
		UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)) * Direction.Y);
}

void ABaseCharacter::MouseLook(const FInputActionValue& Value)
{
	FVector2D Rotation = Value.Get<FVector2D>();

	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

void ABaseCharacter::StartAnim(const FInputActionValue& Value)
{
	bUseControllerRotationYaw = true;
	SpringArm->bUsePawnControlRotation = false;
}

void ABaseCharacter::StopAnim(const FInputActionValue& Value)
{
	bUseControllerRotationYaw = false;
	SpringArm->bUsePawnControlRotation = true;
}

