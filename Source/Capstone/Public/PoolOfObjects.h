// Fill out your copyright notice in the Description page of Project Settings.
//https://www.youtube.com/watch?v=aRpB3qPtloo&t=0s LesserDog Tutorials
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PooledObject.h"

#include "PoolOfObjects.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_API UPoolOfObjects : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoolOfObjects();

	// Return Pooled Object
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	APooledObject* SpawnPooledObject();

	// Only will look for blueprints that inherit from PoolObjects
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	TSubclassOf<class APooledObject> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
	float PooledObjectLifeSpan = 0.0f;

	// For Delegate
	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APooledObject*> ObjectPool;  
	TArray<int> SpawnedPoolIndexes;  // Will keep track of what each PooledObjects index is, when its added to the ObjectPool so we know specifically which object we are referring to
		
};
