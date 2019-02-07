#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UserWidget.h"
#include "BaseItem.h"
#include "CustomUserWidget.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;

UCLASS()
class UE4_INVENTORY_SYSTEM_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

	UPROPERTY(BlueprintReadOnly)
	ABaseItem* ItemInSight;

	UPROPERTY(BlueprintReadOnly)
	TArray<ABaseItem*> Inventory;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void MoveForward(float Val);
	void MoveRight(float Val);
	void PickupItem();
	void ToggleInventory();
	APlayerController* PlayerController;

private:
	int InventorySize;
	float TraceLength;
	UCameraComponent* CameraComponent;
	TSubclassOf <class UUserWidget> InventoryWidgetClass;
	TSubclassOf <class UUserWidget> RaycastInfoWidgetClass;
	UCustomUserWidget* RaycastInfoWidgetRef;
	UCustomUserWidget* InventoryWidgetRef;
	int GetFirstNonZeroedIndex(TArray<ABaseItem*> Array);

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SwapInventoryItems(int FirstIdx, int SecondIdx);

	UFUNCTION(BlueprintCallable)
	void DropItem(int ItemIdx);
};
