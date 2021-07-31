// Fill out your copyright notice in the Description page of Project Settings.


#include "GridBlock.h"

// Sets default values
AGridBlock::AGridBlock()
{
    
    
    isStart = false;
    isFinish = false;
    isMaterialChanged = false;
    blockNum = 0;
    
    PrimaryActorTick.bCanEverTick = true;
    isPlayerSpawned = false;
    isWithObstacle = false;
    
    dimensionHeight = 300;
    dimensionWidth = 300;
    dimensionDepth = 300;
    
    panelMesh = CreateDefaultSubobject<UBoxComponent>( TEXT("MeshPanel"));
    RootComponent = panelMesh;
    panelMesh->SetBoxExtent(FVector(100, 100, 100));
    panelMesh->SetCollisionProfileName(TEXT("GridBlock"));
    panelMesh->bDynamicObstacle = true;
    
}

// Called when the game starts or when spawned
void AGridBlock::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AGridBlock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
  //  if (this-isStart && !isMaterialChanged){
       // this->highlightComponent->SetupAttachment(arm, USpringArmComponent::SocketName);
    //    this->isMaterialChanged = true;
    //}

}

void AGridBlock::setObstacle(bool isObstacle){
    this->isWithObstacle = isObstacle;
}

bool AGridBlock::getObstacle(){
    return this->isWithObstacle;
}

void AGridBlock::setPlayerSpawn(bool isSpawned){
    this->isPlayerSpawned = isSpawned;
}

bool AGridBlock::getPlayerSpawn(){
    return this->isPlayerSpawned;
}

void AGridBlock::setMatrixIndex(int32 row, int32 coulmn){
    this->matrixIndex[0] = row;
    this->matrixIndex[1] = coulmn;
}

int32* AGridBlock::getMatrixIndex(){
    return this->matrixIndex;
}

void AGridBlock::onClick(){
    UE_LOG(LogTemp, Warning, TEXT("Actor Selected!"));
}

bool AGridBlock::getIsStart(){
    return this->isStart;
}
bool AGridBlock::getIsFinish(){
    return this->isFinish;
}

void AGridBlock::setIsStart(bool isIt){
    this->isStart = isIt;
}
void AGridBlock::setIsFinish(bool isIt){
    this->isFinish = isIt;
}

void AGridBlock::markGrid(){
    FVector locaiton(this->GetActorLocation());
}

void AGridBlock::makeHighlight(){
    if(this->isStart){
        DrawDebugPoint(GetWorld(), this->GetActorLocation(), 12, FColor(200,106,130), true);
    }
    else if(this->isFinish){
        DrawDebugPoint(GetWorld(), this->GetActorLocation(), 12, FColor(52,220,239), true);
    }
}

void AGridBlock::makeHighlightPath(){
    DrawDebugPoint(GetWorld(), this->GetActorLocation(), 12, FColor(226,184,95), true);
}

void AGridBlock::setBlockNum(int index){
    this->blockNum = index;
}
int AGridBlock::getBlockNum(){
    return  this->blockNum;
}
