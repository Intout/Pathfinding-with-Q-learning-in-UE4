// Fill out your copyright notice in the Description page of Project Settings.

#include "Observer.h"
#include <string.h>
#include "utils.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "RLShortestPath.h"
#include <math.h>

using namespace RL;
using namespace std;
#define MATRIX_ROW 6
#define MATRIX_COLUMN 6
#define STATE_NUM 6
#define ACTION_NUM 6
#define DES_STATE 5
#define MAX_EPISODE 1000
#define alpha 0.8

// Q-Learning parameters
double R[625][625];
double Q[2500][2500];
int possible_action[10];
int possible_action_num;
int destenation;
int start_point;
int state_num;
int action_num;
int size;
// Q-Learning methods
void run_training(int init_state);

size_t GRAPHS_MATRIX_SIZE;
size_t REWARD_MATRIX_SIZE;
size_t QLEARN_MATRIX_SIZE;
uint32_t GOAL_NODE;
ArrayInt steps;
ArrayInt stepArray;
ArrayInt rewardArray;
int START_POINT;
const double GAMMA = 0.9f;
const uint32_t ITERATIONS = 90000;

// Sets default values
AObserver::AObserver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    
    // Mouse Controls
   // APlayerController* playerController = GetWorld()->GetFirstPlayerController();
    //playerController->bShowMouseCursor = true;
    //playerController->bEnableClickEvents = true;
    //playerController->bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
    cameraRotation = FRotator(-90.0, 0.0, 0.0);
    // 35.0 focal length, sensor width 23.76, sensor height 13.365
    cameraFOV = 90.0f;
    isTraining = false;
    isResultsReady = false;
    canDoGraph2 = false;
    canDoGraph1 = false;
    float sceneWidth = 50.0f;
    float sceneHeight = 50.0f;
    
    collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("   PlayerCollision"));
    SetRootComponent(collisionSphere);
    collisionSphere->InitSphereRadius(30.0);
    collisionSphere->SetWorldScale3D(FVector(0.30, 0.30, 0.30));
    
    
    // Disable unnecessary movements for observer.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    // construct camera arm and init the sight to map size.
    cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
    cameraArm->SetupAttachment(RootComponent);
    cameraArm->SetRelativeRotation(cameraRotation);
    cameraArm->TargetArmLength = 7500.0f;
    
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ObserverCamera"));
    camera->SetupAttachment(cameraArm, USpringArmComponent::SocketName);
    camera->FieldOfView = cameraFOV;
    camera->AspectRatio = sceneWidth/sceneHeight;
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    
    
}

// Called when the game starts or when spawned
void AObserver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObserver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    int a = 0;
    if(this->isTraining){
        this->runTraining();
        this->isTraining = false;
        this->isResultsReady = true;
    }
    if(this->isResultsReady){
        bool isTherePath = false;
        for (int i = 1; i < steps.size()-1; i++) {
            for(int j = 0; j < this->gridMap->getHeight(); j++){
                for(int k = 0; k < this->gridMap->getWidth(); k++){
                    if(this->gridMap->gridMatrix[j].gridBlocks[k]->getBlockNum() == steps[i]){
                        isTherePath = true;
                        this->gridMap->gridMatrix[j].gridBlocks[k]->makeHighlightPath();
                    }
                }
            }
        }
        
        if(!isTherePath){
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("There is no valid path for given points!"));
        }
        convertRewardArray();
        this->isResultsReady = false;
        this->canDoGraph1 = true;
    }

}

// Called to bind functionality to input
void AObserver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AObserver::getIsResultReady(){
    return this->canDoGraph1;
}

void AObserver::setIsResultReady(bool value){
    this->canDoGraph1 = value;
}

float AObserver::calcFOV(int distanceToTarget, float focalLength, float sensorHeight){
    
    float FOV = 90.0f;
    
    // Angle of View.
    float AOV = 2 * atan(sensorHeight/(2*focalLength)) * (180/M_PI);
    
    FOV = 2 * tan(AOV/2) * distanceToTarget;
    
    
    return FOV;
}

void AObserver::runTraining(){
    
    // 100 value to finish point.
    R[finish][finish] = 100;
    destenation = finish;
    state_num =  gridMap->getWidth() * gridMap->getHeight();
    action_num = gridMap->getWidth() * gridMap->getHeight();
    // Get neigbour matrix from grid map.
    int neighbourIndex = 0;
    for (int i = 0; i < gridMap->getHeight(); i++){
        for(int j = 0; j < gridMap->getWidth(); j++){
            // Get neigbours of grid block if it doesn't have obstacle.
            // set all neighbours -1
            for(int k = 0; k < gridMap->getHeight()*gridMap->getWidth(); k++){
                R[neighbourIndex][k] = -1;
            }
            if(!gridMap->gridMatrix[i].gridBlocks[j]->getObstacle()){
                // check 4 neigbours of the block and set values.
                if(j <  gridMap->getWidth()-1){
                    if(!gridMap->gridMatrix[i].gridBlocks[j+1]->getObstacle()){
                        R[neighbourIndex][neighbourIndex+1] = 0;
                    }
                }
                if(j >  0){
                    if(!gridMap->gridMatrix[i].gridBlocks[j-1]->getObstacle()){
                        R[neighbourIndex][neighbourIndex-1] = 0;
                    }
                }
                if(i <  gridMap->getHeight()-1){
                    if(!gridMap->gridMatrix[i+1].gridBlocks[j]->getObstacle()){
                        R[neighbourIndex][neighbourIndex + gridMap->getWidth()] = 0;
                    }
                }
                if(i >  0){
                    if(!gridMap->gridMatrix[i-1].gridBlocks[j]->getObstacle()){
                        R[neighbourIndex][neighbourIndex - gridMap->getWidth()] = 0;
                    }
                }
                }
            neighbourIndex++;
            }
        }
    UE_LOG(LogTemp, Warning, TEXT("%d"), neighbourIndex);
    for(int i = 0; i < neighbourIndex; i++){
        FString output;
        for(int j = 0; j < neighbourIndex; j++){
            output += FString::FromInt(R[i][j]);
            output += ", ";
            // init Q as zeros
            Q[i][j] = 0;
        }
        UE_LOG(LogTemp, Warning, TEXT("%s"), *output);
    }
    GRAPHS_MATRIX_SIZE = neighbourIndex;
    REWARD_MATRIX_SIZE = neighbourIndex;
    QLEARN_MATRIX_SIZE = neighbourIndex;
    GOAL_NODE = this->finish;
    START_POINT = this->start;
    
    // R is ready.
    
    run_training(1);

}

// Q-Learning
void run_training(int init_state){
    RLShortestPath rlShortestPath(GRAPHS_MATRIX_SIZE, REWARD_MATRIX_SIZE, QLEARN_MATRIX_SIZE, GOAL_NODE, GAMMA);
    ArrayEdge edges;
    for (int i = 0; i < GRAPHS_MATRIX_SIZE; i++) {
        int k = 0;
        for (int j = 0; j < GRAPHS_MATRIX_SIZE; j++) {
            if (R[i][j] == 0) {
                edges.push_back(createEdge(i, j));
                k++;
            }
            
        }
        if (k == 0){
            edges.push_back(createEdge(i, i));
        }
    }
    std::vector<ArrayInt> results;
    
    rlShortestPath.addEdges(edges);
    rlShortestPath.printGraphNodes();
    results = rlShortestPath.learn(ITERATIONS, R, destenation);
    
    rewardArray = results[0];
    std::cout << "Cost Size:" << rewardArray.size() << std::endl;
 //   for(int r: rewardArray)
   //     std::cout << r << "";
    
    stepArray = results[1];
    std::cout << "Step Size: " << stepArray.size() << std::endl;
   // for(int r: stepArray)
     //   std::cout << r << "";
    steps = rlShortestPath.solve(START_POINT, R, GRAPHS_MATRIX_SIZE);
    //rlShortestPath.printArrayDebug(steps);
    int arrSize = steps.size();
    std::cout << "Size: " << steps.size() << std::endl;
    for (int i = 0; i < arrSize; i++) {
        
        std::cout << steps[i] << std::endl;
    }
}


void AObserver::setIsTraining(bool value, AGridMap* gridmap, int startValue, int finishValue){
    this->gridMap = gridmap;
    this->start = startValue;
    this->finish = finishValue;
    this->isTraining = value;
}

TArray<int> AObserver::getPath(){
    for (int i = 1; i < steps.size()-1; i++) {
        
        path.Add(steps[i]);
    }
    return path;
}

void AObserver::convertRewardArray(){
    for (int i = 0; i < rewardArray.size(); i++) {
        unrealRewardArray.Add(rewardArray[i]);
    }
    for (int i = 0; i < stepArray.size(); i++)
        unrealStepArray.Add(stepArray[i]);
}

TArray<int> AObserver::getUnrealRewardArray(){
    return unrealRewardArray;
}

TArray<int> AObserver::getUnrealStepArray(){
    return unrealStepArray;
}

bool AObserver::getcanDoGraph2(){
    return this->canDoGraph2;
}

void AObserver::setcanDoGraph2(bool value){
    this->canDoGraph2 = value;
}
