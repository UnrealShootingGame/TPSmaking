// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableVendor.generated.h"

/**
 * InteractableVendor ������Ʈ�� �����ϰ� �� ĳ���ʹ� ������ CameraComponent�� �����ؾ��Ѵ�.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5COOP_API UInteractableVendor : public UInteractable
{
	GENERATED_BODY()
	
public:
	UInteractableVendor();

private:
	UPROPERTY(EditAnywhere)
	class UUserWidget* Widget;

protected:

public:
	virtual void Interacted(ACharacter* InteractingOne) override;

};