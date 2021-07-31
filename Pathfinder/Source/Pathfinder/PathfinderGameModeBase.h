// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "ObserverController.h"
#include "GridMap.h"
#include "RobotPlayer.h"
#include "Observer.h"
#include <iostream>
#include <string>
#include <string.h>
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "utils.h"
#include "BUIHUD.h" 
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PathfinderGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class PATHFINDER_API APathfinderGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
    APathfinderGameModeBase();
    
public:
    UPROPERTY()
    AGridMap* gridMap;
    ARobotPlayer* robot;
    
    AObserver* observer;
    AObserverController* controller;
    
    FString obstacleFilePath;
    FString matrixString;
    
    bool isSimulationDone;
    
    UFUNCTION()
    void writeToFile();
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
};
