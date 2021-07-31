// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "GridBlock.generated.h"

UCLASS()
class PATHFINDER_API AGridBlock : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    AGridBlock();
    
    UPROPERTY(VisibleAnywhere)
    UInstancedStaticMeshComponent* meshInstance;
    UBoxComponent* panelMesh;
    UStaticMesh* mesh;
    
    float xCord;
    float yCord;
    float zCord;
    
    bool isWithObstacle;
    bool isPlayerSpawned;
    
    bool isStart;
    bool isFinish;
    bool isMaterialChanged;
    
    int32 matrixIndex[2];
    
    float dimensionHeight;
    float dimensionWidth;
    float dimensionDepth;
    
    int blockNum;
    
    UFUNCTION()
    void setPlayerSpawn(bool isSpawned);
    bool getPlayerSpawn();
    
    void setObstacle(bool isObstacle);
    bool getObstacle();
    
    void setMatrixIndex(int32 row, int32 coulmn);
    int32* getMatrixIndex();
    
    void onClick();
    
    bool getIsStart();
    bool getIsFinish();
    
    void setIsStart(bool isIt);
    void setIsFinish(bool isIt);
    
    void makeHighlight();
    void makeHighlightPath();
    
    void markGrid();
    
    void setBlockNum(int index);
    int getBlockNum();
    
    UPROPERTY(EditAnywhere)
    class UMaterialInterface* starthMaterial;
    
    UPROPERTY(EditAnywhere)
    class UMaterialInterface* finishMaterial;
    
    //bool GetPlayerSpawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
