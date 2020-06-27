// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	/// <summary>
	/// IMPORTANT
	/// Will give error if HasAuthority() check is not provided
	/// Replicates functions only run on Servers.
	/// Which makes sense as we don't want Clients to update data on the Server,
	/// but Vice-Versa.
	/// </summary>
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/// HasAuthority() return TRUE if the instance of the game is the Server.
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	}

}