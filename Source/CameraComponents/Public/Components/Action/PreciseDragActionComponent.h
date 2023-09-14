// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PreciseDragActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMERACOMPONENTS_API UPreciseDragActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPreciseDragActionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StartDrag(ULocationCameraComponent* InLocationCameraComponent);

	UFUNCTION(BlueprintCallable)
	void StopDrag();

protected:
	FVector CalculateNewLocation() const;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ECollisionChannel> PreciseMouseDragCollisionChannel;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere)
	bool PreciseMouseDragTraceComplex;

protected:
	UPROPERTY(BlueprintReadOnly)
	ULocationCameraComponent* DraggedLocationCameraComponent;

	UPROPERTY(BlueprintReadOnly)
	FVector PreciseMouseDragOrigin;
};
