// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "FPSAttributeSet.h"



// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	Attributes = CreateDefaultSubobject<UFPSAttributeSet>("Attributes");

}

UAbilitySystemComponent* AFPSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Check if it is valid
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		// Apply default attributes to character
		if (DefaultAttributeEffect)
		{
			
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();	// Effects will be applied to *this*// Create Effect Context Handle
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);   // Making Gameplay Effect Spec Handle

			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}

		// Give Abilities
		if (HasAuthority())
		{
			for (TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0));
			}
		}
	}
	
}


void AFPSCharacter::TransferStatInfo(float health, float armor, float bullets, float shells)
{
	Attributes->SetHealth(health);
	Attributes->SetArmor(armor);
	Attributes->SetBullets(bullets);
	Attributes->SetShells(shells);
}




