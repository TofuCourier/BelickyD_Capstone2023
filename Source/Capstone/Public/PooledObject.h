// Fill out your copyright notice in the Description page of Project Settings.
//https://www.youtube.com/watch?v=aRpB3qPtloo&t=0s LesserDog Tutorials
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);  // Creates a delegate that will use to tell the object pool when this object has despawned.

UCLASS()
class CAPSTONE_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;  

	// Called Whenever the 
	UFUNCTION(BlueprintCallable, Category = "PooledObject")
	void Deactivate();

	void SetActive(bool isActive);   // Set bool Active
	void SetLifeSpan(float LifeTime);  // Set Life Span value to passed in variable
	void SetPoolIndex(int Index);	// Pass in Int that will set Pool Index

	bool IsActive();  // Returns a bool that returns the value of the variable Active
	int GetPoolIndex();  // Returns the Pool Index Integer

protected:

	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;

	FTimerHandle LifeSpanTimer;  // Will be the timer that we set with the length of LifeTime in SetLifeSpan()
};
