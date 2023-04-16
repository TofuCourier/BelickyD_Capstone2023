// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAttributeSet.h"

#include "FPSCharacter.h"


UFPSAttributeSet::UFPSAttributeSet()
{
}

// Clamp the new value between 0 and 100
void UFPSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	AFPSCharacter* FPSChar = Cast<AFPSCharacter>(GetOwningActor());

	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxHealth);
	else if (Attribute == GetArmorAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxArmor);
	else if (Attribute == GetBulletsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxBullets);
	else if (Attribute == GetRocketsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxRockets);
	else if (Attribute == GetShellsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->MaxShells);
	else if (Attribute == GetKillsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, FPSChar->EnemyKills);
}

bool UFPSAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	//// Declare absolute value variable that is the magnitude(value) of the evaluated data
	//float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude); // (armor damage)

	//// Cast to character so we are able to get and update attributes
	//AFPSCharacter* FPSChar = Cast<AFPSCharacter>(GetOwningActor());
	//

	//if (Data.EvaluatedData.Magnitude > 0)
	//{
	//	// Is the current health + the magnitude of the effect (current health being given) greater or equal to 100. And apply to all attributes.
	//	if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() + AbsoluteMagnitude >= FPSChar->MaxArmor)
	//	{
	//		SetArmor(FPSChar->MaxArmor);
	//		return false;
	//	}
	//	else if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= FPSChar->MaxHealth)
	//	{
	//		SetHealth(FPSChar->MaxHealth);
	//		return false;
	//	}
	//	else if (Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() + AbsoluteMagnitude >= FPSChar->MaxBullets)
	//	{
	//		SetBullets(FPSChar->MaxBullets);
	//		return false;
	//	}
	//	else if (Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() + AbsoluteMagnitude >= FPSChar->MaxRockets)
	//	{
	//		SetRockets(FPSChar->MaxRockets);
	//		return false;
	//	}
	//}
	//else if (Data.EvaluatedData.Magnitude < 0)
	//{
	//	// Is the amount of damage received exceed the characters armor value? If so do the calculation for damaging players heath as well
	//	if (Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor())
	//		Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
	//}

	//if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetArmor() <= 0)
	//{
	//	Health.SetCurrentValue(Health.GetCurrentValue() + AbsoluteMagnitude); return false;
	//}

	//if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() <= 0)
	//{
	//	SetArmor(0);
	//}

	//return true;

	AFPSCharacter* FPSChar = Cast<AFPSCharacter>(GetOwningActor());

	float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	if (Data.EvaluatedData.Magnitude > 0)
	{
		if (Data.EvaluatedData.Attribute == GetArmorAttribute())
		{
			if (GetArmor() + AbsoluteMagnitude >= FPSChar->MaxArmor)
			{
				SetArmor(FPSChar->MaxArmor);
				return false;
			}
			else
			{
				Armor.SetCurrentValue(Armor.GetCurrentValue() + AbsoluteMagnitude);
				return false;
			}
		}

		if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			if (GetHealth() + AbsoluteMagnitude >= FPSChar->MaxHealth)
			{
				SetHealth(FPSChar->MaxHealth);
				return false;
			}
			else
			{
				Health.SetCurrentValue(Health.GetCurrentValue() + AbsoluteMagnitude);
				return false;
			}
		}
	}
	else
	{
		if (Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor())
			Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
	}

	return true;
}

// Set the value of the attribute to be 0 if less than 0
void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() < 0)
		SetHealth(0);
	else if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() < 0)
		SetArmor(0);
	else if (Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() < 0)
		SetBullets(0);
	else if (Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() < 0)
		SetRockets(0);
	else if (Data.EvaluatedData.Attribute == GetShellsAttribute() && GetShells() < 0)
		SetShells(0);

}

