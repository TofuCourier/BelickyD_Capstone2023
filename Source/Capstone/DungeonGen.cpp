// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonGen.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "EngineUtils.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADungeonGen::ADungeonGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGen::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ADungeonGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// If Room index = wanted index, save floor tile for player spawning
void ADungeonGen::GetPlayerSpawnTileArea(TArray<FIntVector> playerTile, int roomIndex)
{
	if (roomIndex == PlayerSpawnRoomIndex)
	{
		PlayerSpawnTile = playerTile;
	}
}

void ADungeonGen::MovePlayerSpawn()
{
	FIntVector Tile;

	// Player Starts
	TArray<AActor*> FoundActors;
	// Get All Player Starts
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("----------------test-------------------"));
	// Move Player spawn to room using Valid Tiles
	// Check that we have enough floor area for our player spawns
	if (FoundActors.Num() <= PlayerSpawnTile.Num())
	{
		for (AActor* PlayerStart : FoundActors)
		{
			// Get random index in the array of player spawn tile and set that to Tile
			int32 randomNum = RandomStream.RandRange(0, PlayerSpawnTile.Num());
			Tile = PlayerSpawnTile.Last(randomNum);
			//PlayerSpawnTile.Find(Tile, randomNum);
			UE_LOG(LogTemp, Warning, TEXT("We found a tile?"));
			UE_LOG(LogTemp, Warning, TEXT("random value %d"), randomNum);


			// Set actor location using tile location, scale and spawn offset
			FVector Tile2 = FVector(Tile);
			PlayerStart->SetActorLocation((Tile2 * Scale) + GetActorLocation() + PlayerSpawnOffset);

			// Remove from the list
			PlayerSpawnTile.Remove(Tile);
		}

		// TODO Still need to add rotation
	}



}

void ADungeonGen::SpawnTilesWalls()
{
	for (int index = 0; index < 2; index++)
	{
		// The tiles we are building walls on are going to be either floortiles or corridortiles based off index value 0 or 1
		TArray<FIntVector> Tiles = index ? FloorTiles : CorridorTiles;


		for (FIntVector FoundTiles : Tiles)
		{
			bool bIsInArray = false;

			for (int counter = 0; counter > 4; counter++)
			{
				//// Checking to see if this direction does NOT have a another tile connected. If there is not
				//// Infront X=1 Y=0
				//int TileInfrontX = FoundTiles.X;
				//int TileInfrontY = FoundTiles.Y;
				//int TileInfrontZ = FoundTiles.Z;

				//TileInfrontX = TileInfrontX + (1);
				//TileInfrontY = TileInfrontY + (0);
				//FIntVector TileInfront = FIntVector(TileInfrontX, TileInfrontY, TileInfrontZ);
				//if (!Tiles.Contains(TileInfront))
				//{
				//	FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(FoundTiles.X, FoundTiles.Y, FoundTiles.Z), FVector(Scale, Scale, Scale));
				//	WallMesh->AddInstance()
				//}


				//// Right X=0, Y=1
				//int TileRightX = FoundTiles.X;
				//int TileRightY = FoundTiles.Y;
				//int TileRightZ = FoundTiles.Z;

				//TileRightX = TileRightX + (0);
				//TileRightY = TileRightY + (1);
				//FIntVector TileRight = FIntVector(TileRightX, TileRightY, TileRightZ);
				//if (!Tiles.Contains(TileRight))
				//{
				//	
				//}


				//// Behind X=-1, Y=0
				//int TileBehindX = FoundTiles.X;
				//int TileBehindY = FoundTiles.Y;
				//int TileBehindZ = FoundTiles.Z;

				//TileBehindX = TileBehindX + (-1);
				//TileBehindY = TileBehindY + (0);
				//FIntVector TileBehind = FIntVector(TileBehindX, TileBehindY, TileBehindZ);
				//if (!Tiles.Contains(TileBehind))
				//{
				//	
				//}


				//// Left X=0, Y=-1
				//int TileLeftX = FoundTiles.X;
				//int TileLeftY = FoundTiles.Y;
				//int TileLeftZ = FoundTiles.Z;

				//TileLeftX = TileLeftX + (0);
				//TileLeftY = TileLeftY + (-1);
				//FIntVector TileLeft = FIntVector(TileLeftX, TileLeftY, TileLeftZ);
				//if (!Tiles.Contains(TileLeft))
				//{
				//	
				//}

			
				

			}
		}
	}
}
