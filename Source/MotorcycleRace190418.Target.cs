// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MotorcycleRace190418Target : TargetRules
{
	public MotorcycleRace190418Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "MotorcycleRace190418" } );
	}
}
