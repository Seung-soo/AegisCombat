// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UAegisHealthHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UUAegisHealthHUDWidget::SetHealth(float Current, float Max)
{
	const float SafeMax = FMath::Max(1.f, Max);
	const float Pct = FMath::Clamp(Current / SafeMax, 0.f, 1.f);

	if (PB_Health)
	{
		PB_Health->SetPercent(Pct);
	}

	if (TXT_Health)
	{
		TXT_Health->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Current, SafeMax)));
	}
}
