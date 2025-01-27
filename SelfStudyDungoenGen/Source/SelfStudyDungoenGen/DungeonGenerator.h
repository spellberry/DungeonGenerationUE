// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class AMasterDungeon;
class ADungeonRoom1;
class ADungeonRoom2;

UCLASS()
class SELFSTUDYDUNGOENGEN_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnStartRoom();
	
	UFUNCTION(BlueprintCallable)
	void SpawnNextRoom();
	
	UFUNCTION(BlueprintCallable)
	void AddOverlappedRooms();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMasterDungeon>ClassToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rooms|DungeonRoom")
	AMasterDungeon* DungeonRoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rooms|MasterRoom")
	AMasterDungeon* CurrentRoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rooms|DungeonExits")
	TArray<UActorComponent*>DungeonExits;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rooms|RoomList")
	TArray<AMasterDungeon*>RoomList;

	TArray<AMasterDungeon*>RoomTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_RoomAmount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_MaxRoomAmount = 20;

	TSet<UPrimitiveComponent*> m_OverlappingComponents;
};
