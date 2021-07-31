// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPlayer.h"

// Sets default values
ARobotPlayer::ARobotPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    isBegin = false;
    
    meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
    SetRootComponent(meshComponent);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(TEXT("/Game/Assets/Shape_Cube.Shape_Cube"));
    
    if (VisualAsset.Succeeded()){
        meshComponent->SetStaticMesh(VisualAsset.Object);
        
    }
    
}

// Called when the game starts or when spawned
void ARobotPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobotPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

