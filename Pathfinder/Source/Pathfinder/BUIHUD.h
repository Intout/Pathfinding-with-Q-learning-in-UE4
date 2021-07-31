// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "BUIHUD.generated.h"

/**
 * 
 */
UCLASS()
class PATHFINDER_API ABUIHUD : public AHUD
{
	GENERATED_BODY()
public:
    ABUIHUD();
    
    virtual void BeginPlay() override;
	
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> HUDWidgetClass;
    
    UPROPERTY(EditAnywhere, Category = "UI")
    class UUserWidget* widget;
};
