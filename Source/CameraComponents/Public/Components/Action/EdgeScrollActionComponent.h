// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EdgeScrollActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMERACOMPONENTS_API UEdgeScrollActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEdgeScrollActionComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool GetRelevantData(FVector2D& MousePosition, FIntPoint& ViewportSize) const;
	FVector2D CalculateEdgeScrolling(const FVector2D MousePosition, const FVector2D ViewportSize) const;

public:
	//	If enabled, the speed will adapt depending on the distance your cursor is from the border
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	bool UseEdgeScrollingStrength = true;
	
	//	The distance ratio from the edges of the screen at which your cursor must be to edge scroll
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "0.5", UIMax = "0.5"))
	float EdgeScrollingSensitivity = 0.2f;

	UPROPERTY(BlueprintReadOnly)
	bool IsEdgeScrolling = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateChanged);

	UPROPERTY(BlueprintAssignable)
	FStateChanged OnBeginEdgeScrolling;

	UPROPERTY(BlueprintAssignable)
	FStateChanged OnEndEdgeScrolling;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateUpdated, FVector2D, Direction);

	UPROPERTY(BlueprintAssignable)
	FStateUpdated OnUpdateEdgeScrolling;
};
