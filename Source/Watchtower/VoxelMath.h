#pragma once

#include "Engine.h"

class FVoxelMath
{
public:
	static float IntBound(float S, float DS)
	{
		if (DS < 0)
			return IntBound(-S, -DS);

		S = FMath::Fmod(S, 1);
		return (1 - S) / DS;
	};
};