// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Public/TimerManager.h"
#include "Apparition.h"

// Sets default values
AApparition::AApparition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->zapp = CreateDefaultSubobject<UBoxComponent>(TEXT("Zone d'apparition"));
	this->RootComponent = zapp;

}

FVector AApparition::getPHasard()
{
	FVector origine = this->getZapp()->Bounds.Origin;
	FVector etendue = this->getZapp()->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(origine, etendue);
}

void AApparition::apparaitre()
{
	UWorld* monde = GetWorld();
	FVector point = this->getPHasard();

	FRotator rotation;
	rotation.Yaw = FMath::FRand() * 360.0f;
	rotation.Pitch = FMath::FRand() * 360.0f;
	rotation.Roll = FMath::FRand() * 360.0f;

	FActorSpawnParameters parametres;
	parametres.Owner = this;
	parametres.Instigator = GetInstigator();

	monde->SpawnActor<APoison>(this->objet, point, rotation, parametres);
}

// Called when the game starts or when spawned
void AApparition::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(minuteur, this, &AApparition::apparaitre, 4.0f, true);

}

// Called every frame
void AApparition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

