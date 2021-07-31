// Fill out your copyright notice in the Description page of Project Settings.

#include "ObserverController.h"
#include "Pathfinder.h"
#include "GridBlock.h"


AObserverController::AObserverController():APlayerController(){

    startPoint = 0;
    finishPoint = 0;
    
    
    isStartSelected = false;
    isFinishSelected = false;
    
    
     this->bShowMouseCursor = true;
     this->bEnableClickEvents = true;
     this->bEnableMouseOverEvents = true;
    
}
void AObserverController::BeginPlay()
{
    Super::BeginPlay();
    Super::SetupInputComponent();
    // Handling mouse click
    if(InputComponent)
    {
     InputComponent->BindAction("MouseClick", IE_Pressed, this, &AObserverController::onClick);
    }
    
}

void AObserverController::onClick(){
    FHitResult hitResult;
    if (!isStartSelected || !isFinishSelected){
        GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);
        if(hitResult.GetActor()){
            AGridBlock* gridActor;
            TActorIterator< AGridBlock > ActorItr = TActorIterator< AGridBlock >(GetWorld());
            UE_LOG(LogTemp, Warning, TEXT("%s"),*hitResult.GetActor()->GetName());
            while(ActorItr){
                if(ActorItr->GetName() == hitResult.GetActor()->GetName()){
                    gridActor = *ActorItr;
                    break;
                }
                ++ActorItr;
            }
            if (!isStartSelected){
                this->isStartSelected = true;
                gridActor->setIsStart(true);
                gridActor->makeHighlight();
                this->startPoint = gridActor->getBlockNum();
                UE_LOG(LogTemp, Warning, TEXT("Start Selected!"));
            }
            else if(!isFinishSelected && !gridActor->getIsStart()){
                this->isFinishSelected = true;
                gridActor->setIsFinish(true);
                gridActor->makeHighlight();
                this->finishPoint = gridActor->getBlockNum();
                UE_LOG(LogTemp, Warning, TEXT("Finish Selected!"));
            }
        }
    }
}

void AObserverController::Test(){
    UE_LOG(LogTemp, Warning, TEXT("WOW!!!"));
}

bool AObserverController::getIsStartSelected(){
    return this->isStartSelected;
}
bool AObserverController::getIsFinishSelected(){
    return this->isFinishSelected;
}

int AObserverController::getStartPoint(){
    return this->startPoint;
}
int AObserverController::getFinishPoint(){
    return this->finishPoint;
}
