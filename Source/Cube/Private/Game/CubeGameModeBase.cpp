// Copyright EderSantander developer


#include "Game/CubeGameModeBase.h"

#include "Interfaces/ShooterInterface.h"
#include "Kismet/GameplayStatics.h"

void ACubeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Debussy", ActorsDebussy);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Nyeh", ActorsNyeh);

	UE_LOG(LogTemp, Warning, TEXT("DEBUSSY ACTORS = [%i] NYEH ACTORS = [%i]"), ActorsDebussy.Num(), ActorsNyeh.Num());
}

void ACubeGameModeBase::CallDebussyShoot()
{
	for (AActor* Shooter : ActorsDebussy)
	{
		if (Shooter->Implements<UShooterInterface>())
		{
			IShooterInterface::Execute_PerformShoot(Shooter);			
		}
	}
}

void ACubeGameModeBase::CallNyehShoot()
{
	for (AActor* Shooter : ActorsNyeh)
	{
		if (Shooter->Implements<UShooterInterface>())
		{
			IShooterInterface::Execute_PerformShoot(Shooter);			
		}
	}
}
