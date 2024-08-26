// Fill out your copyright notice in the Description page of Project Settings.


#include "TopViewCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATopViewCharacter::ATopViewCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	Spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));

	Spring->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(Spring);

	Spring->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	Spring->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void ATopViewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	

}

// Called every frame
void ATopViewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATopViewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ATopViewCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ATopViewCharacter::MoveUpDown);

	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &ATopViewCharacter::LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &ATopViewCharacter::LookUpDown);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ATopViewCharacter::Jump);
}
void ATopViewCharacter::MoveLeftRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);

}
void ATopViewCharacter::MoveUpDown(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);

}
void ATopViewCharacter::LookLeftRight(float Value)
{
	AddControllerYawInput(Value);

}
void ATopViewCharacter::LookUpDown(float Value)
{
	AddControllerPitchInput(Value);

}

