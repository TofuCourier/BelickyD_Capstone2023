// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"


#include "FPSCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestEvent);

UCLASS()
class CAPSTONE_API AFPSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	// Each character derived from this will get its own attribute set
	UPROPERTY()
	class UFPSAttributeSet* Attributes;

public:

	// Sets default values for this character's properties
	AFPSCharacter();

	// Overridden from IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxArmor = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxBullets = 250;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxRockets = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxShells = 64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int EnemyKills = 0;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Effect that initializes our default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayAbilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	// Array of starting abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayAbilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	UFUNCTION(BlueprintCallable)
	void TransferStatInfo(float health, float armor, float bullets, float shells);
};
