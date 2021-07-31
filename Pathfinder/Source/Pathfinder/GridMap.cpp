// Fill out your copyright notice in the Description page of Project Settings.

#include "GridMap.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values
AGridMap::AGridMap()
{

    numOfNonobstacle = 0;
    
    PrimaryActorTick.bCanEverTick = false;
    root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = root;
    
    // default GridMap size is 50x50.
    width = 50;
    height = 50;
    collisionBoxOfBlocks = FVector(1.0, 1.0, 1.0);
    
    
    // Visual blocks instance for the grid (Instance of Mesh).
    meshInstance = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("VisualBlock"));
    //meshInstance->SetupAttachment(RootComponent);
    meshInstance->bCastDynamicShadow = false;
    meshInstance->CastShadow = false;
    meshInstance->SetMobility(EComponentMobility::Static);
    meshInstance->SetCollisionProfileName(TEXT("MeshInstance"));
    
    // Visual instance for obstacle mesh.
    obstacleMeshInstance = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ObstacleBlock"));
    obstacleMeshInstance->bCastDynamicShadow = false;
    obstacleMeshInstance->CastShadow = false;
    obstacleMeshInstance->SetMobility(EComponentMobility::Static);
    obstacleMeshInstance->SetCollisionProfileName(TEXT("ObstacleMeshInstance"));
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    obstacleVisualAsset(TEXT("/Game/Assets/Traffic_Cone_Mesh.Traffic_Cone_Mesh"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    cubeVisualAsset(TEXT("/Game/Assets/SM_Ground.SM_Ground"));
    if (cubeVisualAsset.Succeeded() && obstacleVisualAsset.Succeeded()){
        meshInstance->SetStaticMesh(cubeVisualAsset.Object);
        obstacleMeshInstance->SetStaticMesh(obstacleVisualAsset.Object);
    }
    
  //  RootComponent->IsSelectable(false);
    
   // meshInstance->SetMaterial(0, DynamicMaterialInst);
    

}

// Called when the game starts or when spawned
void AGridMap::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AGridMap::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AGridMap::generateMap(){
    // Cleare blocks when function reruns;
    meshInstance->ClearInstances();
    
    for (int coulmn = 0; coulmn < this->height; coulmn++) {
        FVector gridMapLocation = GetActorLocation();
        struct FCoulmnTGrids coulmnTGrids = FCoulmnTGrids();
        for (int row = 0; row < this->width; row++) {
            
            // Spawn location of block.
            
            FActorSpawnParameters spawnInfo;
            FVector Location((300*coulmn),(300*row), 1);
            FRotator Rotation(0.0f, 0.0f, 0.0f);
            
            //Construct and edit new block.
            AGridBlock* gridBlock = GetWorld()->SpawnActor<AGridBlock>(Location, Rotation);
            gridBlock->SetActorScale3D(this->collisionBoxOfBlocks);
            gridBlock->setMatrixIndex(coulmn, row);
            gridBlock->setBlockNum(numOfNonobstacle);
            // Add Visual block.
            //meshInstance->SetupAttachment(gridBlock->GetRootComponent());
            meshInstance->AddInstance(FTransform(Rotation ,Location, this->collisionBoxOfBlocks));
            
            // Add new block to 1D Array.
            coulmnTGrids.add(gridBlock);
            numOfNonobstacle++;
        }
        // Add block array to another array to create a Matrix.
        this->gridMatrix.Add(coulmnTGrids);
    }
    generateObstacle();
}

void AGridMap::generateObstacle(){
    
    // Number of obstacles must be minimum %30 percent of total number girds (I have set the interval between 30% to 70%).
    int32 numberOfObstacels = FMath::RoundHalfFromZero((this->width*this->height)* FMath::FRandRange(3,7)/10);
    
    while(numberOfObstacels != 0){
        
        chooseRandomIndex();
        
        FVector Location(this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorLocation().X, this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorLocation().Y, 1);
        
        FRotator Rotation(this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorRotation().Pitch, this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorRotation().Roll, this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorRotation().Yaw);
        
        this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->setObstacle(true);
        //obstacleMeshInstance->SetupAttachment(this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetRootComponent());
        obstacleMeshInstance->AddInstance(FTransform(Rotation, Location, FVector(4, 4, 4)));
        numOfNonobstacle--;
        if(this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->getObstacle()){
            UE_LOG(LogTemp, Warning, TEXT("%d. Obstacle at:%d, %d, %d"), numberOfObstacels ,this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorLocation().X,this->gridMatrix[this->coordinates[0]].gridBlocks[this->coordinates[1]]->GetActorLocation().Y, Location.Z);
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Nope!"))
        }
        
        
        numberOfObstacels--;
    }
    
}

void AGridMap::chooseRandomIndex(){
    // indexes must be between 0 to height/width length. +1 for last indexes.
    this->coordinates[0] = FMath::FRandRange(1, this->height+1) - 1;
    this->coordinates[1] = FMath::FRandRange(1, this->width+1) - 1;
}


void AGridMap::setHeight(int x){
    this->height = x;
}
void AGridMap::setWidth(int y){
    this->width = y;
}

int32 AGridMap::getHeight(){
    return this->height;
}
int32 AGridMap::getWidth(){
    return this->width;
}

int32 AGridMap::getNumOfNonObstacle(){
    return this->numOfNonobstacle;
}
