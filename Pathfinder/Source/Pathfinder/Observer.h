// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ObserverController.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GridMap.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Observer.generated.h"

UCLASS()
class PATHFINDER_API AObserver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AObserver();
    
    FRotator cameraRotation;
    
    UCameraComponent* camera;
    USpringArmComponent* cameraArm;
    USphereComponent* collisionSphere;
    bool isTraining;
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    bool isResultsReady;
    bool canDoGraph1;
    bool canDoGraph2;
    AGridMap* gridMap;
    int start;
    int finish;
    
    UPROPERTY(EditAnywhere)
    float cameraFOV;
    UPROPERTY()
    class AObserverController* pawnController;
    
    TArray<int> unrealRewardArray;
    TArray<int> unrealStepArray;
    TArray<int> path;
    
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    
    UFUNCTION()
    float calcFOV(int distanceToTarget, float focalLength, float sensorHeight);
    void setIsTraining(bool value, AGridMap* gridmap, int startValue, int finishValue);
    void runTraining();
    TArray<int> getPath();
    void convertRewardArray();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable)
    bool getIsResultReady();
    UFUNCTION(BlueprintCallable)
    void setIsResultReady(bool value);
    UFUNCTION(BlueprintCallable)
    bool getcanDoGraph2();
    UFUNCTION(BlueprintCallable)
    void setcanDoGraph2(bool value);
    UFUNCTION(BlueprintCallable)
    TArray<int> getUnrealRewardArray();
    UFUNCTION(BlueprintCallable)
    TArray<int> getUnrealStepArray();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
