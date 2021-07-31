// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "GridBlock.h"
#include "GameFramework/Actor.h"
#include "GridMap.generated.h"

USTRUCT()
struct FCoulmnTGrids{
    GENERATED_USTRUCT_BODY()
public:
    TArray<AGridBlock*> gridBlocks;
    void add(AGridBlock* newGridBlock){
        gridBlocks.Add(newGridBlock);
    }
};

UCLASS()
class PATHFINDER_API AGridMap : public AActor
{
    GENERATED_BODY()
    
private:
    UPROPERTY()
    int32 width;
    int32 height;
    
    int32 coordinates[2];
    
    FVector collisionBoxOfBlocks;
    
    USceneComponent* root;
    UInstancedStaticMeshComponent* meshInstance;
    UInstancedStaticMeshComponent* obstacleMeshInstance;
    UMaterialInstanceDynamic* DynamicMaterialInst;
    
    int32 numOfNonobstacle;
    
public:
    // Sets default values for this actor's properties
    AGridMap();
    TArray<FCoulmnTGrids> gridMatrix;
    
    UFUNCTION()
    int32 getNumOfNonObstacle();
    void generateMap();
    void generateObstacle();
    void chooseRandomIndex();
    
    void setHeight(int x);
    void setWidth(int y);
    
    int32 getHeight();
    int32 getWidth();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
