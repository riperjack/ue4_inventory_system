#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

AFPSCharacter::AFPSCharacter()
{
	InventorySize = 36;
	TraceLength = 300.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->GetRelativeLocation() = FVector(0, 0, BaseEyeHeight);
	CameraComponent->bUsePawnControlRotation = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryObj(TEXT("/Game/FirstPerson/UI/InventoryWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> RaycastInfoObj(TEXT("/Game/FirstPerson/UI/RaycastInfoWidget"));
	InventoryWidgetClass = InventoryObj.Class;
	RaycastInfoWidgetClass = RaycastInfoObj.Class;

	Inventory.AddZeroed(InventorySize);
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryWidgetRef = CreateWidget <UCustomUserWidget>(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass);
	InventoryWidgetRef->AddToViewport();
	InventoryWidgetRef->SetVisibility(ESlateVisibility::Hidden);

	RaycastInfoWidgetRef = CreateWidget <UCustomUserWidget>(GetWorld()->GetFirstPlayerController(), RaycastInfoWidgetClass);
	RaycastInfoWidgetRef->AddToViewport();
	RaycastInfoWidgetRef->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (!PickupTraceDelegate.IsBound())
	{
		PickupTraceDelegate.BindUObject(this, &AFPSCharacter::PickupTraceComplete);
	}
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FVector CameraForward = CameraComponent->GetComponentRotation().Vector();
	FVector TraceEnd = CameraLocation + CameraForward * TraceLength;

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Single, CameraLocation, TraceEnd, ECollisionChannel::ECC_Visibility, RV_TraceParams, FCollisionResponseParams::DefaultResponseParam, &PickupTraceDelegate);

}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AFPSCharacter::PickupItem);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AFPSCharacter::ToggleInventory);
}

void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSCharacter::PickupItem()
{
	if (ItemInSight != nullptr) {
		int index = GetFirstNonZeroedIndex(Inventory);
		if (index == -1) return;
		ItemInSight->PrepareForPickup();
		ItemInSight->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Inventory[index] = ItemInSight;	
		InventoryWidgetRef->RefreshInventory();
	}
}

void AFPSCharacter::ToggleInventory()
{
	if (InventoryWidgetRef->GetVisibility() == ESlateVisibility::Visible) {
		InventoryWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		RaycastInfoWidgetRef->SetVisibility(ESlateVisibility::HitTestInvisible);
		FInputModeGameOnly InputModeGameOnly = FInputModeGameOnly();
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeGameOnly);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(false);
	} 
	else if (InventoryWidgetRef->GetVisibility() == ESlateVisibility::Hidden) {
		InventoryWidgetRef->RefreshInventory();
		InventoryWidgetRef->SetVisibility(ESlateVisibility::Visible);
		RaycastInfoWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		FInputModeGameAndUI InputModeGameAndUI = FInputModeGameAndUI();
		InputModeGameAndUI.SetWidgetToFocus(InventoryWidgetRef->GetCachedWidget());
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeGameAndUI);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->SetIgnoreLookInput(true);
	}
}

int AFPSCharacter::GetFirstNonZeroedIndex(TArray<ABaseItem*> Array)
{
	for (int i = 0; i < Array.Num(); i++) {
		if (Array[i] == nullptr) {
			return i;
		}
	}

	return -1;
}

void AFPSCharacter::SwapInventoryItems(int FirstIdx, int SecondIdx)
{
	Inventory.Swap(FirstIdx, SecondIdx);
}

void AFPSCharacter::DropItem(int ItemIdx)
{
	ABaseItem* DroppedItem = Inventory[ItemIdx];
	if (DroppedItem != nullptr) {
		DroppedItem->PrepareForDrop();
		DroppedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Inventory[ItemIdx] = nullptr;
	}
}

void AFPSCharacter::PickupTraceComplete(const FTraceHandle& TraceHandle, FTraceDatum& TraceDatum)
{
	for (const FHitResult& HitResult : TraceDatum.OutHits)
	{
		ItemInSight = nullptr;

		if (HitResult.bBlockingHit)
		{
			ABaseItem* BaseItem = Cast<ABaseItem>(HitResult.GetActor());
			if (BaseItem)
			{
				ItemInSight = BaseItem;
			}
		}
	}
}