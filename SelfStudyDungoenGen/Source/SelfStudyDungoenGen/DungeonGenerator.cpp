// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "MasterDungeon.h"
#include "DungeonRoom1.h"
#include "DungeonRoom2.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	for(TObjectIterator<UClass> it; it; ++it)
	{
		if(it->IsChildOf(AMasterDungeon::StaticClass()) && it->HasAnyClassFlags(CLASS_CompiledFromBlueprint) && !it->GetName().StartsWith(TEXT("SKEL"))
			&& it->GetName() != TEXT("BP_MasterDungeon_C"))
		{
			AMasterDungeon* DefaultObject = Cast<AMasterDungeon>(it->GetDefaultObject());
			if (DefaultObject)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, it->GetName());
				RoomTypes.Add(DefaultObject);
			}
		}
	}

	if (!RoomTypes.IsEmpty())
	{
		int randomIndexRoom = FMath::RandRange(0, RoomTypes.Num() - 1);
		ClassToSpawn = RoomTypes[randomIndexRoom]->GetClass();
	}

	SpawnStartRoom();
	SpawnNextRoom();
}

void ADungeonGenerator::SpawnStartRoom()
{
	if (ClassToSpawn)
	{
		//spawn a new room
		
		DungeonRoom = GetWorld()->SpawnActor<AMasterDungeon>(ClassToSpawn, GetActorTransform());

		//get all the exits of the room
		TArray<UActorComponent*> exits = DungeonRoom->GetComponentsByTag(UArrowComponent::StaticClass(), FName("Exit"));
		for(auto exit : exits)
		{
			//and store them inside of our array of dungeon exits
			DungeonExits.Add(exit);
		}
	}
}

void ADungeonGenerator::SpawnNextRoom()
{
	if (!DungeonExits.IsEmpty())
	{
		//choose a random exit
		int randomIndexExit = FMath::RandRange(0, DungeonExits.Num() - 1);
		UActorComponent* selectedExit = DungeonExits[randomIndexExit];

		//choose a random room from the array
		int randomIndexRoom = FMath::RandRange(0, RoomTypes.Num() - 1);

		//get the exti component so we can get the world transform
		USceneComponent* exitComponent = Cast<USceneComponent>(selectedExit);
		FTransform exitTransform = exitComponent->GetComponentTransform();

		//spawn a new room and make it the current master room
		CurrentRoom = Cast<AMasterDungeon>(GetWorld()->SpawnActor<AMasterDungeon>(RoomTypes[randomIndexRoom]->GetClass(), exitTransform));

		//removing the overlapped rooms
		AddOverlappedRooms();

		//remove the exit where we just spawned our room
		DungeonExits.RemoveAt(randomIndexExit);

		//add the new exits to the array of exits in the whole dungeon
		TArray exits = CurrentRoom->GetComponentsByTag(UArrowComponent::StaticClass(), FName("Exit"));
		DungeonExits.Append(exits);


		//increase the variable that tracks how many rooms we have
		m_RoomAmount++;

		if (m_RoomAmount < m_MaxRoomAmount)
		{
			SpawnNextRoom();
		}
	}
}

void ADungeonGenerator::AddOverlappedRooms()
{
	//getting the box collider
	auto boxCollision = CurrentRoom->GetComponentsByTag(UBoxComponent::StaticClass(), TEXT("OverlapBox"));

	//getting the single box that out 
	for(auto box : boxCollision)
	{
		auto myBox = Cast<UBoxComponent>(box);
		myBox->GetOverlappingComponents(m_OverlappingComponents);
	}

	if(m_OverlappingComponents.Num() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("IT AIN'T EMPTY!!! WE GOT THIS SHIT!!!"));
		GetWorld()->DestroyActor(CurrentRoom);
		m_OverlappingComponents.Reset();
	}
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

