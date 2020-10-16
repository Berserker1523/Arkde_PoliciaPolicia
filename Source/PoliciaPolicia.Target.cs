// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class PoliciaPoliciaTarget : TargetRules
{
	public PoliciaPoliciaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "PoliciaPolicia" } );
	}
}
