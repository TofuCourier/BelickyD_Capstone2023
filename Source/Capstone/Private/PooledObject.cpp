// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APooledObject::SetActive(bool isActive)
{
	Active = isActive; // Set Active to the bool that we passed in
	SetActorHiddenInGame(!isActive); // Set the Actor to be hidden based on Active
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Deactivate, LifeSpan, false);  // Set the timer the lifespan timer, call Deactivate when timer runs out
}

// Set the LifeSpan of the objects
void APooledObject::SetLifeSpan(float LifeTime)
{
	LifeSpan = LifeTime;
}

// Set the Pool Index
void APooledObject::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

// Returns the state of Active
bool APooledObject::IsActive()
{
	return Active;
}


void APooledObject::Deactivate()
{
	SetActive(false);  // Set Active False
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}


// Return Pool Index
int APooledObject::GetPoolIndex()
{
	return PoolIndex;
}


