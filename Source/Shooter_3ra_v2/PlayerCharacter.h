// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SHOOTER_3RA_V2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
private:
	//REGION: Configuraciond de la camara para que sea en 3ra persona y siga al personaje.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) // Permite que podamos editar con Blueprints.
	class USpringArmComponent * CameraBoom; // Sigue al personaje a una distancia fija.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent * FollowCamera; // Agrega una perspectiva para ver.
	//ENDREGION

	
	//REGION: Configuracion del movimiento de la camara al precionar las flechas del teclado o el Gamepad derecho del mando.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	//ENDREGION
	
	
public:
	// Sets default values for this character's properties
	APlayerCharacter(); //constructor

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // Es como lo que aria la funcion Start de Unity

	// REGION: Cremos las funciones de movimiento
	void MoveForward(float value);
	void MoveRight(float value);
	// ENDREGION

	// REGION: Creamos las funciones del movimiento de lacamara
	void TurnAtRate(float rate);
	void LookAtRate(float rate);
	// ENDREGION

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Es como la funcion update de Unity

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //Se enlazaran los input del keyboard

};
