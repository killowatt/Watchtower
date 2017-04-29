#pragma once

#include "Engine.h"

class FVoxelMath
{
public:
	static float Rem(float Value, float Modulus)
	{
		return FMath::Fmod((FMath::Fmod(Value, Modulus) + Modulus), Modulus);
	};
	static float IntBound(float S, float DS)
	{
		if (DS < 0)
			return IntBound(-S, -DS);

		S = Rem(S, 1);
		return (1 - S) / DS;
	};
};