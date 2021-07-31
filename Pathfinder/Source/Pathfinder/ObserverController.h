// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "ObserverController.generated.h"

/**
 * 
 */
UCLASS()
class PATHFINDER_API AObserverController : public APlayerController
{
	GENERATED_BODY()
public:
    AObserverController();
    
    UPROPERTY()
    bool isStartSelected;
    bool isFinishSelected;
    
    int startPoint;
    int finishPoint;
    
    UFUNCTION()
    void onClick();
    
    bool getIsStartSelected();
    bool getIsFinishSelected();
    
    int getStartPoint();
    int getFinishPoint();
    
    void Test();
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
