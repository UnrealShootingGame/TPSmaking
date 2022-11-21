#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AShooterCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Jump);
}

void AShooterCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		FRotator Rotation;
		FVector Direction;
		switch (PlayerStatus)
		{
		case EPlayerStatus::EPS_Walking:
			Rotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
			Direction = FVector(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X));

			break;
		case EPlayerStatus::EPS_Flying:
			Rotation = Controller->GetControlRotation();
			Direction = FVector(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X));
			break;
		}	
		AddMovementInput(Direction, Value);
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		FRotator Rotation;
		FVector Direction;
		switch (PlayerStatus)
		{
		case EPlayerStatus::EPS_Walking:
			Rotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
			Direction = FVector(FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y));

			break;
		case EPlayerStatus::EPS_Flying:
			Rotation = Controller->GetControlRotation();
			Direction = FVector(FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y));
			break;
		}
		AddMovementInput(Direction, Value);
	}
}

void AShooterCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AShooterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AShooterCharacter::Jump()
{
	switch (PlayerStatus)
	{
	case EPlayerStatus::EPS_Walking:
		FlyingOrJump();
		break;
	case EPlayerStatus::EPS_Flying:
		PlayerStatus = EPlayerStatus::EPS_Walking;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		break;
	}
}

void AShooterCharacter::FlyingOrJump()
{
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		PlayerStatus = EPlayerStatus::EPS_Flying;
	}
	else
	{
		Super::Jump();
	}
}

