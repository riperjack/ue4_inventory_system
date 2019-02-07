#include "BaseItem.h"

ABaseItem::ABaseItem()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* ABaseItem::GetStaticMeshComponent()
{
	return StaticMeshComponent;
}

void ABaseItem::PrepareForPickup()
{
	StaticMeshComponent->SetVisibility(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseItem::PrepareForDrop()
{
	StaticMeshComponent->SetVisibility(true);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
