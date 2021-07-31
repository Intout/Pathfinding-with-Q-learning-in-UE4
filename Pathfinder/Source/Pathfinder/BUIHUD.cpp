// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIHUD.h"

ABUIHUD::ABUIHUD()
{
    
    static ConstructorHelpers::FClassFinder<UUserWidget> widgetObj(TEXT("/Game/Blueprints/CameraSwitch"));
    HUDWidgetClass = widgetObj.Class;
}


void ABUIHUD::BeginPlay(){
    
    Super::BeginPlay();
    
    if(HUDWidgetClass != nullptr){
        widget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        
        if(widget){
            widget->AddToViewport();
        }
    }
    
    
}
