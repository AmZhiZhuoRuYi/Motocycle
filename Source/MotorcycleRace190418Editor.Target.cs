// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MotorcycleRace190418EditorTarget : TargetRules
{
	public MotorcycleRace190418EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "MotorcycleRace190418" } );
	}
}
