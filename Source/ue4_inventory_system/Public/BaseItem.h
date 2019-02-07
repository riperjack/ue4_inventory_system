#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseItem.generated.h"

UCLASS()
class UE4_INVENTORY_SYSTEM_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RoundsPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MagSize;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* GetStaticMeshComponent();
	void PrepareForPickup();
	void PrepareForDrop();
};
