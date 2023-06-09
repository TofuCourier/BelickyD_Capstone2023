// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "FPSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class CAPSTONE_API UFPSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UFPSAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Bullets;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Bullets);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Rockets;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Rockets);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Shells;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Shells);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Kills;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, Kills);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
