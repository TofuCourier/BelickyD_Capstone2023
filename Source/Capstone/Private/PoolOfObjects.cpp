// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolOfObjects.h"

// Sets default values for this component's properties
UPoolOfObjects::UPoolOfObjects()
{

}

// Called when the game starts
void UPoolOfObjects::BeginPlay()
{
	Super::BeginPlay();

	// Check if pooledObject subclass is not null
	if (PooledObjectSubclass != nullptr)
	{
		// Get the World
		UWorld* const World = GetWorld();

		// Check if the World exists
		if (World != nullptr)
		{
			// Increment PoolSize until decided value
			for (int i = 0; i < PoolSize; i++)
			{
				// Create a Poolable Actor for each of the entries in PoolSize and assign temp pointer and spawn
				APooledObject* PoolableActor = World->SpawnActor<APooledObject>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);

				// Is Poolable Actor valid
				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false); // Set false / not active
					PoolableActor->SetPoolIndex(i); // Set an index to the object
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UPoolOfObjects::OnPooledObjectDespawn); // Point to the delegate and bind function
					ObjectPool.Add(PoolableActor); // Add PoolableActor to the ObjectPool array
				}
			}
		}
	}
}

APooledObject* UPoolOfObjects::SpawnPooledObject()
{
	// For each Actor in Object Pool
	for (APooledObject* PoolableActor : ObjectPool)
	{
		// Check if Actor is not null and not active
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			// Teleport Actor, Set Life Span and set to Active
			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());  // Add its Pool Index to the SpawnedPoolIndexes Array. Keeps track of spawned object in the world

			return PoolableActor;
		}
	}

	// If indexes exist
	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		APooledObject* PoolableActor = ObjectPool[PooledObjectIndex];

		if (PoolableActor != nullptr)
		{
			PoolableActor->SetActive(false);

			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());

			return PoolableActor;
		}
	}
	return nullptr;
}

// Remove the PoolIndex of the PooledActor passed in from the SpawnedPoolIndexes array
void UPoolOfObjects::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

