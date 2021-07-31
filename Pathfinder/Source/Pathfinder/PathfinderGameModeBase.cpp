// Copyright Epic Games, Inc. All Rights Reserved.

#include "PathfinderGameModeBase.h"
#include <iostream>
#include <string>
#include "Kismet/GameplayStatics.h"
#include <string.h>
#include "utils.h"
#include <stdlib.h>
#include "Pathfinder.h"

void test(){
    int a = 4;
    int b = 5;
    int c = a + b;
    UE_LOG(LogTemp, Warning, TEXT("%d OUT!!!!"), c);
}

APathfinderGameModeBase::APathfinderGameModeBase():AGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
    isSimulationDone = false;
    //DefaultPawnClass = AObserver::StaticClass();
    HUDClass = ABUIHUD::StaticClass();
    PlayerControllerClass = AObserverController::StaticClass();
    
    // matrix out file path.
    obstacleFilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSourceDir()) + TEXT("/engel.txt");
    
}

// Called when the game starts or when spawned
void APathfinderGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
    // Create Grid Map
    
    FVector MapLocation(0.0f, 0.0f, 0.0f);
    FRotator MapRotation(0.0f, 0.0f, 0.0f);
    gridMap = GetWorld()->SpawnActor<AGridMap>(MapLocation, MapRotation);
    gridMap->setWidth(25);
    gridMap->setHeight(25);
    gridMap->generateMap();
    
    // Spawn Observer in middle of gridMap.
    MapLocation.X = gridMap->getHeight()/2 * 300;
    MapLocation.Y = gridMap->getWidth()/2 * 300;
    MapLocation.Z = 300;
    observer = GetWorld()->SpawnActor<AObserver>(MapLocation, MapRotation);
   
    FVector origin;
    FVector boxExtent;
    gridMap->GetActorBounds(false, origin, boxExtent);
    writeToFile();
    test();
    UE_LOG(LogTemp, Warning, TEXT("Bounds: %d, %d, %d"), boxExtent.X, boxExtent.Y, boxExtent.Z);
    controller = Cast<AObserverController>(GetWorld()->GetFirstPlayerController());
    if( controller )
    {
        controller->Test();
        
    }
}
// Called every frame
void APathfinderGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(controller->getIsStartSelected() && controller->getIsFinishSelected() && !isSimulationDone){
        
        //start_point = controller->getStartPoint();
        //destenation = controller->getFinishPoint();
        //UE_LOG(LogTemp, Warning, TEXT("Start: %d, Finish: %d"), start_point, destenation);
        //run_training(1);
        observer->setIsTraining(true, gridMap, controller->getStartPoint(), controller->getFinishPoint());
        controller->Test();
        this->isSimulationDone = true;
    }

}

void APathfinderGameModeBase::writeToFile(){
    FString outputStirng = "{E: Engelli blok}, {A: Acik (Engelsiz) blok}, {P: Pembe (Baslangic Blogu)}, {M: Mavi (Bitis Blogu)} \n\n";
    FFileHelper::SaveStringToFile(outputStirng, *obstacleFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
    for (int i = 0; i < this->gridMap->getHeight() ; i++) {
        outputStirng = " ";
        for (int j = 0; j < gridMap->getWidth(); j++) {
            if(this->gridMap->gridMatrix[i].gridBlocks[j]->getIsStart()){
                outputStirng += " (" + FString::FromInt(i+1) + ", " + FString::FromInt(j+1) + ", P) ";
                continue;
            }
               if(this->gridMap->gridMatrix[i].gridBlocks[j]->getIsStart()){
                outputStirng += " (" + FString::FromInt(i+1) + ", " + FString::FromInt(j+1) + ", M) ";
                continue;
            }
            if(this->gridMap->gridMatrix[i].gridBlocks[j]->getObstacle()){
                outputStirng += " (" + FString::FromInt(i+1) + ", " + FString::FromInt(j+1) + ", E) ";
            }
            else{
                outputStirng += " (" + FString::FromInt(i+1) + ", " + FString::FromInt(j+1) + ", A) ";
            }
        }
        outputStirng += "\n";
        FFileHelper::SaveStringToFile(outputStirng, *obstacleFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
    }
}
