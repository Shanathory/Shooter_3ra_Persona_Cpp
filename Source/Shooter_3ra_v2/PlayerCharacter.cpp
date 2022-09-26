// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter() :
	BaseTurnRate(45.0f),
	BaseLookUpRate(45.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Constructor. Lo que dice es que se puede usar la funcion tick (Update de unity)

	//REGION: Creaciond de la camara (UCameraComponent) en tercera persona con la implementacion del seguimiento mediante el uso del USpringArmComponent.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // Creamos el componente USpringArmComponent al cual vamos a enlasar el CameraBoom para que se muestre el blueprint. CameraBoom es la clase que creamos en PlayerCharacter.h
	CameraBoom -> SetupAttachment (RootComponent); // Nos permite enlasar entre comoponente, inclusos a mayas.
	CameraBoom -> TargetArmLength = 450; // Modificamos la distancia de la camara con respecto a la capsula.
	CameraBoom -> bUsePawnControlRotation = true; // Configuaramos para que cuando nuestro personaje rote, tambien lo haga el Spring con sigo la camara.

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera -> SetupAttachment(CameraBoom,USpringArmComponent::SocketName); // Enlasamos al FollowCamera con el CameraBoom y lo enlasamos con el SocketName, para que cuando se mueva el CameraBoom, tambien se mueva la camara.
	FollowCamera -> bUsePawnControlRotation = false; // Configuramso para que cuando rotemos la camara, no se rote el personaje.

	bUseControllerRotationYaw = true; // Para que cuando rote la camara en orizontal, tambien lo haga el personaje.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	//ENDREGION
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay(); // Se ejecuta apenas empieza el juego.
	/*
	 *UE_LOG(LogTemp,Warning,TEXT("Hi hi in Unreal Engine")); //Se utiliza para mandar mensajes por consola.
	 *int numero = 3;
	 *float numeroFloat = 3.5;
	 *numeroFloat = numero + numeroFloat;
	 *FString cadena = "Mamalon";
	 *UE_LOG(LogTemp, Warning, TEXT("%f %s Contando: %d"), numeroFloat, *cadena, numero);

	 *if (GEngine) 
	 *{
	 *	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Yellow,TEXT("Esto es un mensaje de GEngine"));// Genera un cartel en pantalla. Por defecto colocamos -1 en el primer argunto. El segundo argumento es el tiempo en segundos. El tercer argumetno es el color del texto. El cuarto argunte es el texto.
	 *}
	 */
	
}

// REGION: Mvoimientos
void APlayerCharacter::MoveForward(float value)
{
	if (Controller != nullptr && value != 0.0f)
	{
		const FRotator Rotation = Controller -> GetControlRotation(); //Para poder controlar la rotacion del personaje.
		const FRotator YawRotation(0,Rotation.Yaw,0); //Configuramos la rotacion en el eje Z.
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Controlamos la direccion del desplazamiento segun su rotacion.
	
		AddMovementInput(Direction,value); // Movimiento del personaje en la direccion configura con una velocidad que depende de la entrada configurada en el inputManager.
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (Controller != nullptr && value != 0.0f)
	{
		const FRotator Rotation = Controller -> GetControlRotation(); //Para poder controlar la rotacion del personaje.
		const FRotator YawRotation(0,Rotation.Yaw,0); //Configuramos la rotacion en el eje Z.
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Controlamos la direccion del desplazamiento segun su rotacion.
	
		AddMovementInput(Direction,value); // Movimiento del personaje en la direccion configura con una velocidad que depende de la entrada configurada en el inputManager.
	}
}

void APlayerCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // Movimiento de la camara en el eje Z.
															// GetDeltaSeconds(), es para que la rotacion no dependa de los frames, sino de delta seconds el cial va de 0 a 1 en un segundo.
}

void APlayerCharacter::LookAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // Movimiento de la camara en el eje X.
}
// ENDREGION: Mvoimiento


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	/* Super::Tick(DeltaTime);
	 * FString cadena = "Repiticion dentro del Tick";
	 *UE_LOG(LogTemp, Warning, TEXT("Contando: %s"), *cadena);
	*/
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movimiento del personaje
	PlayerInputComponent -> BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Movimiento camara flechas teclado y Gamepad derecho del mando.
	PlayerInputComponent -> BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent -> BindAxis("LookUpRate", this, &APlayerCharacter::LookAtRate);

	// Movimiento camara con raton
	PlayerInputComponent -> BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis("Look", this, &APawn::AddControllerPitchInput);
}