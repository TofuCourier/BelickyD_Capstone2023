// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/RandomStream.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGen.generated.h"

UCLASS()
class CAPSTONE_API ADungeonGen : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ADungeonGen();



protected:

	/// Global for the random generation ///
	//////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRandomStream RandomStream;

	// Save Previous Location so we know where to build next Room or Corridor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector PrevLocation;

	// Save NextLocation, this is where our next room will be
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector NextLocation;

	// Array of Floor Tiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector> FloorTiles;

	// Array of Corridor Tiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector> CorridorTiles;

	// World Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale = 200;



	// Player Spawning //////

	// Room # the Player will spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawning")
	int32 PlayerSpawnRoomIndex;

	// Spawn Offset from Tile
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerSpawnOffset;

	// Array of Tiles of the room the player will spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector> PlayerSpawnTile;

	// Room # the End will spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndLevelRoomSpawning")
	int32 EndLevelRoomIndex;

	// Array of Tiles of the room the End will spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector> EndLevelRoomTiles;






	UPROPERTY(EditAnywhere, Category = "EnvironmentSpawning")
	class UInstancedStaticMeshComponent* WallMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GetPlayerSpawnTileArea(TArray<FIntVector> playerTile, int roomIndex);

	// Move player spawn to the room we want
	UFUNCTION(BlueprintCallable)
	void MovePlayerSpawn();

	UFUNCTION(BlueprintCallable)
	void SpawnTilesWalls();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
