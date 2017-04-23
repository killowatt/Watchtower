// Copyright 2016 Chris Conway (Koderz). All Rights Reserved.

#pragma once

#include "RuntimeMeshCore.h"
#include "RuntimeMeshSection.h"

//////////////////////////////////////////////////////////////////////////
//	
//	This file contains a generic vertex structure capable of efficiently representing a vertex with anywhere between 
//	1 and 8 UV channels, including half precision UVs //
//
//	Example use: (This defines a vertex with 1 full precision UV channel)
//
//	typdef FRuntimeMeshVertex<1, false> MyVertex;
//
//	MyVertex Vertex;
//	Vertex.Position = FVector(0,0,0);
//	Vertex.Normal = FVector(0,0,0);
//	Vertex.UV0 = FVector2D(0,0);
//
//
//////////////////////////////////////////////////////////////////////////


template<int32 TextureChannels, bool HalfPrecisionUVs, bool HasPositionComponent>
RuntimeMeshVertexStructure CreateVertexStructure(const FVertexBuffer& VertexBuffer);



//////////////////////////////////////////////////////////////////////////
// Texture Components
//////////////////////////////////////////////////////////////////////////

/* Defines the UV coordinates for a vertex (Defaulted to 0 channels) */
template<int32 TextureChannels, bool HalfPrecision> struct FRuntimeMeshUVComponents
{ 
	static_assert(TextureChannels >= 1 && TextureChannels <= 8, "You must have between 1 and 8 (inclusive) UV channels");
};

/* Defines the UV coordinates for a vertex (Specialized to 1 channels) */
template<> struct FRuntimeMeshUVComponents<1, false>
{
	FVector2D UV0;

	FRuntimeMeshUVComponents() : UV0(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) : UV0(InUV0) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 1 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<1, true>
{
	FVector2DHalf UV0;

	FRuntimeMeshUVComponents() : UV0(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) : UV0(InUV0) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 2 channels) */
template<> struct FRuntimeMeshUVComponents<2, false>
{
	FVector2D UV0;
	FVector2D UV1;

	FRuntimeMeshUVComponents() : UV0(0, 0), UV1(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) : UV0(InUV0), UV1(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) : UV0(InUV0), UV1(InUV1) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 2 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<2, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;

	FRuntimeMeshUVComponents() : UV0(0, 0), UV1(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) : UV0(InUV0), UV1(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) : UV0(InUV0), UV1(InUV1) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 3 channels) */
template<> struct FRuntimeMeshUVComponents<3, false>
{
	FVector2D UV0;
	FVector2D UV1;
	FVector2D UV2;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 3 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<3, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;
	FVector2DHalf UV2;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 4 channels) */
template<> struct FRuntimeMeshUVComponents<4, false>
{
	FVector2D UV0;
	FVector2D UV1;
	FVector2D UV2;
	FVector2D UV3;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 4 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<4, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;
	FVector2DHalf UV2;
	FVector2DHalf UV3;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 5 channels) */
template<> struct FRuntimeMeshUVComponents<5, false>
{
	FVector2D UV0;
	FVector2D UV1;
	FVector2D UV2;
	FVector2D UV3;
	FVector2D UV4;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) : UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 5 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<5, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;
	FVector2DHalf UV2;
	FVector2DHalf UV3;
	FVector2DHalf UV4;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) : UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 6 channels) */
template<> struct FRuntimeMeshUVComponents<6, false>
{
	FVector2D UV0;
	FVector2D UV1;
	FVector2D UV2;
	FVector2D UV3;
	FVector2D UV4;
	FVector2D UV5;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 6 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<6, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;
	FVector2DHalf UV2;
	FVector2DHalf UV3;
	FVector2DHalf UV4;
	FVector2DHalf UV5;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 7 channels) */
template<> struct FRuntimeMeshUVComponents<7, false>
{
	FVector2D UV0;
	FVector2D UV1;
	FVector2D UV2;
	FVector2D UV3;
	FVector2D UV4;
	FVector2D UV5;
	FVector2D UV6;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5, const FVector2D& InUV6) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(InUV6) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 7 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<7, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;
	FVector2DHalf UV2;
	FVector2DHalf UV3;
	FVector2DHalf UV4;
	FVector2DHalf UV5;
	FVector2DHalf UV6;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(0, 0), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5, const FVector2D& InUV6) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(InUV6) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 8 channels) */
template<> struct FRuntimeMeshUVComponents<8, false>
{
	FVector2D UV0;
	FVector2D UV1;
	FVector2D UV2;
	FVector2D UV3;
	FVector2D UV4;
	FVector2D UV5;
	FVector2D UV6;
	FVector2D UV7;

	FRuntimeMeshUVComponents() :
		UV0(0, 0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5, const FVector2D& InUV6) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(InUV6), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5, const FVector2D& InUV6, const FVector2D& InUV7) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(InUV6), UV7(InUV7) { }
};

/* Defines the UV coordinates for a vertex (Specialized to 8 channels, Half Precision) */
template<> struct FRuntimeMeshUVComponents<8, true>
{
	FVector2DHalf UV0;
	FVector2DHalf UV1;
	FVector2DHalf UV2;
	FVector2DHalf UV3;
	FVector2DHalf UV4;
	FVector2DHalf UV5;
	FVector2DHalf UV6;
	FVector2DHalf UV7;

	FRuntimeMeshUVComponents() :
		UV0(0,0), UV1(0, 0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0) :
		UV0(InUV0), UV1(0,0), UV2(0, 0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1) :
		UV0(InUV0), UV1(InUV1), UV2(0,0), UV3(0, 0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(0,0), UV4(0, 0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(0,0), UV5(0, 0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(0,0), UV6(0, 0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(0,0), UV7(0, 0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5, const FVector2D& InUV6) :
		UV0(InUV0), UV1(InUV1), UV2(InUV2), UV3(InUV3), UV4(InUV4), UV5(InUV5), UV6(InUV6), UV7(0,0) { }
	FRuntimeMeshUVComponents(const FVector2D& InUV0, const FVector2D& InUV1, const FVector2D& InUV2, const FVector2D& InUV3,
		const FVector2D& InUV4, const FVector2D& InUV5, const FVector2D& InUV6,	const FVector2D& InUV7) :
		UV0(InUV0),	UV1(InUV1),	UV2(InUV2),	UV3(InUV3),	UV4(InUV4),	UV5(InUV5),	UV6(InUV6),	UV7(InUV7) { }
};






template<bool HasPosition = true>
struct FRuntimeMeshVertexBase
{

	FVector Position;
	FPackedNormal Normal;
	FPackedNormal Tangent;
	FColor Color;

	FRuntimeMeshVertexBase(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor)
		: Position(InPosition), Normal(InNormal), Tangent(InTangent.TangentX), Color(InColor)
	{
		InTangent.AdjustNormal(Normal);
	}

	FRuntimeMeshVertexBase(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor)
		: Position(InPosition), Normal(InTangentZ), Tangent(InTangentX), Color(InColor)
	{
		// store determinant of basis in w component of normal vector
		Normal.Vector.W = GetBasisDeterminantSign(InTangentX, InTangentY, InTangentZ) < 0.0f ? 0 : 255;
	}

	void SetNormalAndTangent(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ)
	{
		Normal = InTangentZ;
		Tangent = InTangentX;

		// store determinant of basis in w component of normal vector
		Normal.Vector.W = GetBasisDeterminantSign(InTangentX, InTangentY, InTangentZ) < 0.0f ? 0 : 255;
	}
};

template<>
struct FRuntimeMeshVertexBase<false>
{
	// We drop position here as it will be supplied in a separate buffer.
	FPackedNormal Normal;
	FPackedNormal Tangent;
	FColor Color;

	FRuntimeMeshVertexBase(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor)
		: Normal(InNormal), Tangent(InTangent.TangentX), Color(InColor)
	{
		InTangent.AdjustNormal(Normal);
	}

	FRuntimeMeshVertexBase(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor)
		: Normal(InTangentZ), Tangent(InTangentX), Color(InColor)
	{
		// store determinant of basis in w component of normal vector
		Normal.Vector.W = GetBasisDeterminantSign(InTangentX, InTangentY, InTangentZ) < 0.0f ? 0 : 255;
	}

	void SetNormalAndTangent(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ)
	{
		Normal = InTangentZ;
		Tangent = InTangentX;

		// store determinant of basis in w component of normal vector
		Normal.Vector.W = GetBasisDeterminantSign(InTangentX, InTangentY, InTangentZ) < 0.0f ? 0 : 255;
	}
};


template<int32 TextureChannels, bool HalfPrecisionUVs, bool HasPositionComponent>
struct FRuntimeMeshVertexTypeInfo_GenericVertex : public FRuntimeMeshVertexTypeInfo
{
	FRuntimeMeshVertexTypeInfo_GenericVertex() :
		FRuntimeMeshVertexTypeInfo(FString::Printf(TEXT("RuntimeMeshVertex<%d, %d, %d>"), TextureChannels, HalfPrecisionUVs, HasPositionComponent), FGuid(0x00FFEB44, 0x31094597, 0x93918032, 0x015678C3)) { }

	const int32 TexChannels = TextureChannels;
	const bool HalfPrecUVs = HalfPrecisionUVs;
	const bool HasPosComponent = HasPositionComponent;

	virtual bool EqualsAdvanced(const FRuntimeMeshVertexTypeInfo* Other) const
	{
		const FRuntimeMeshVertexTypeInfo_GenericVertex* OtherGenericVertex = static_cast<const FRuntimeMeshVertexTypeInfo_GenericVertex*>(Other);

		return TexChannels == OtherGenericVertex->TexChannels &&
			HalfPrecUVs == OtherGenericVertex->HalfPrecUVs &&
			HasPosComponent == OtherGenericVertex->HasPosComponent;
	}
};

template<int32 TextureChannels, bool HalfPrecisionUVs = false, bool HasPositionComponent = true>
struct FRuntimeMeshVertex :
	public FRuntimeMeshVertexBase<HasPositionComponent>,
	public FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>
{
	static_assert(TextureChannels >= 1 && TextureChannels <= 8, "You must have between 1 and 8 (inclusive) UV channels)");

	typedef FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs, HasPositionComponent> SelfType;

	static RuntimeMeshVertexStructure GetVertexStructure(const FRuntimeMeshVertexBuffer<SelfType>& VertexBuffer)
	{
		return CreateVertexStructure<TextureChannels, HalfPrecisionUVs, HasPositionComponent>(VertexBuffer);
	}

	static const FRuntimeMeshVertexTypeInfo_GenericVertex<TextureChannels, HalfPrecisionUVs, HasPositionComponent> TypeInfo;


	FRuntimeMeshVertex() :
		FRuntimeMeshVertexBase<HasPositionComponent>(FVector::ZeroVector, FVector(0, 0, 1), FRuntimeMeshTangent(), FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }
 	FRuntimeMeshVertex(const FVector& InPosition) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, FVector(0, 0, 1), FRuntimeMeshTangent(), FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }
 	FRuntimeMeshVertex(const FVector& InPosition, const FColor& InColor) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, FVector(0, 0, 1), FRuntimeMeshTangent(), InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }

 	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }

	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }


	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }

	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }
};


template<int32 TextureChannels, bool HalfPrecisionUVs, bool HasPositionComponent>
const FRuntimeMeshVertexTypeInfo_GenericVertex<TextureChannels, HalfPrecisionUVs, HasPositionComponent> 
		FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs, HasPositionComponent>::TypeInfo;


template<bool HalfPrecisionUVs, bool HasPositionComponent>
struct FRuntimeMeshVertex<1, HalfPrecisionUVs, HasPositionComponent> :
	public FRuntimeMeshVertexBase<HasPositionComponent>,
	public FRuntimeMeshUVComponents<1, HalfPrecisionUVs>
{
	typedef FRuntimeMeshVertex<1, HalfPrecisionUVs, HasPositionComponent> SelfType;

	static RuntimeMeshVertexStructure GetVertexStructure(const FRuntimeMeshVertexBuffer<SelfType>& VertexBuffer)
	{
		return CreateVertexStructure<1, HalfPrecisionUVs, HasPositionComponent>(VertexBuffer);
	}

	static const FRuntimeMeshVertexTypeInfo_GenericVertex<1, HalfPrecisionUVs, HasPositionComponent> TypeInfo;

	FRuntimeMeshVertex() :
		FRuntimeMeshVertexBase<HasPositionComponent>(FVector::ZeroVector, FVector(0, 0, 1), FRuntimeMeshTangent(), FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FVector& InPosition) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, FVector(0, 0, 1), FRuntimeMeshTangent(), FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FVector& InPosition, const FColor& InColor) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, FVector(0, 0, 1), FRuntimeMeshTangent(), InColor),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }

	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InNormal, InTangent, InColor),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InPosition, const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<HasPositionComponent>(InPosition, InTangentX, InTangentY, InTangentZ, InColor),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }
};

template<bool HalfPrecisionUVs, bool HasPositionComponent>
const FRuntimeMeshVertexTypeInfo_GenericVertex<1, HalfPrecisionUVs, HasPositionComponent>
	FRuntimeMeshVertex<1, HalfPrecisionUVs, HasPositionComponent>::TypeInfo;


template<int32 TextureChannels, bool HalfPrecisionUVs>
struct FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs, false> :
	public FRuntimeMeshVertexBase<false>,
	public FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>
{
	static_assert(TextureChannels >= 1 && TextureChannels <= 8, "You must have between 1 and 8 (inclusive) UV channels)");

	typedef FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs, false> SelfType;

	static RuntimeMeshVertexStructure GetVertexStructure(const FRuntimeMeshVertexBuffer<SelfType>& VertexBuffer)
	{
		return CreateVertexStructure<TextureChannels, HalfPrecisionUVs, false>(VertexBuffer);
	}

	static const FRuntimeMeshVertexTypeInfo_GenericVertex<TextureChannels, HalfPrecisionUVs, false> TypeInfo;

	FRuntimeMeshVertex() :
		FRuntimeMeshVertexBase<false>(FVector(0, 0, 1), FRuntimeMeshTangent(), FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FColor& InColor) :
		FRuntimeMeshVertexBase<false>(FVector(0, 0, 1), FRuntimeMeshTangent(), InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0) { }


	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor, const FVector2D& InUV0, const FVector2D& InUV1) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, InColor),
		FRuntimeMeshUVComponents<TextureChannels, HalfPrecisionUVs>(InUV0, InUV1) { }
};

template<int32 TextureChannels, bool HalfPrecisionUVs>
const FRuntimeMeshVertexTypeInfo_GenericVertex<TextureChannels, HalfPrecisionUVs, false>
	FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs, false>::TypeInfo;


template<bool HalfPrecisionUVs>
struct FRuntimeMeshVertex<1, HalfPrecisionUVs, false> :
	public FRuntimeMeshVertexBase<false>,
	public FRuntimeMeshUVComponents<1, HalfPrecisionUVs>
{
	typedef FRuntimeMeshVertex<1, HalfPrecisionUVs, false> SelfType;

	static RuntimeMeshVertexStructure GetVertexStructure(const FRuntimeMeshVertexBuffer<SelfType>& VertexBuffer)
	{
		return CreateVertexStructure<1, HalfPrecisionUVs, false>(VertexBuffer);
	}

	static const FRuntimeMeshVertexTypeInfo_GenericVertex<1, HalfPrecisionUVs, false> TypeInfo;

	FRuntimeMeshVertex() :
		FRuntimeMeshVertexBase<false>(FVector(0, 0, 1), FRuntimeMeshTangent(), FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FColor& InColor) :
		FRuntimeMeshVertexBase<false>(FVector(0, 0, 1), FRuntimeMeshTangent(), InColor),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>() { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, FColor::White),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }

	FRuntimeMeshVertex(const FVector& InNormal, const FRuntimeMeshTangent& InTangent, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InNormal, InTangent, InColor),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }
	FRuntimeMeshVertex(const FVector& InTangentX, const FVector& InTangentY, const FVector& InTangentZ, const FColor& InColor, const FVector2D& InUV0) :
		FRuntimeMeshVertexBase<false>(InTangentX, InTangentY, InTangentZ, InColor),
		FRuntimeMeshUVComponents<1, HalfPrecisionUVs>(InUV0) { }
};

template<bool HalfPrecisionUVs>
const FRuntimeMeshVertexTypeInfo_GenericVertex<1, HalfPrecisionUVs, false>
	FRuntimeMeshVertex<1, HalfPrecisionUVs, false>::TypeInfo;
















/** Simple vertex with 1 UV channel */
using FRuntimeMeshVertexSimple = FRuntimeMeshVertex<1, false, true>;

/** Simple vertex with 2 UV channels */
using FRuntimeMeshVertexDualUV = FRuntimeMeshVertex<2, false, true>;

/** Simple vertex with 1 UV channel and NO position component (Meant to be used with separate position buffer) */
using FRuntimeMeshVertexNoPosition = FRuntimeMeshVertex<1, false, false>;

/** Simple vertex with 2 UV channels and NO position component (Meant to be used with separate position buffer) */
using FRuntimeMeshVertexNoPositionDualUV = FRuntimeMeshVertex<2, false, false>;



//////////////////////////////////////////////////////////////////////////
//	Texture Channels Vertex Structure
//////////////////////////////////////////////////////////////////////////

template<typename RuntimeVertexType, int32 TextureChannels, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
	}
};

template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 1, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, OneChannelType));
	}
};

template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 2, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
	}
};


template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 3, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV2, OneChannelType));
	}
};


template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 4, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV2, TwoChannelType));
	}
};


template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 5, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV2, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV4, OneChannelType));
	}
};


template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 6, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV2, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV4, TwoChannelType));
	}
};

template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 7, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV2, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV4, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV6, OneChannelType));
	}
};


template<typename RuntimeVertexType, bool HalfPrecision>
struct FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, 8, HalfPrecision>
{
	static void AddChannels(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		EVertexElementType OneChannelType = HalfPrecision ? VET_Half2 : VET_Float2;
		EVertexElementType TwoChannelType = HalfPrecision ? VET_Half4 : VET_Float4;

		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV0, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV2, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV4, TwoChannelType));
		VertexStructure.TextureCoordinates.Add(RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, UV6, TwoChannelType));
	}
};


template<typename RuntimeVertexType, bool HasPositionComponent>
struct FRuntimeMeshPositionComponentVertexStructure
{
	static void AddComponent(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
		VertexStructure.PositionComponent = RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, Position, VET_Float3);
	}
}; 

template<typename RuntimeVertexType>
struct FRuntimeMeshPositionComponentVertexStructure<RuntimeVertexType, false>
{
	static void AddComponent(const FVertexBuffer& VertexBuffer, RuntimeMeshVertexStructure& VertexStructure)
	{
	}
};



/* Creates the vertex structure definition for a particular configuration */
template <int32 TextureChannels, bool HalfPrecisionUVs, bool HasPositionComponent>
RuntimeMeshVertexStructure CreateVertexStructure(const FVertexBuffer& VertexBuffer)
{
	typedef FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs, HasPositionComponent> RuntimeVertexType;

	RuntimeMeshVertexStructure VertexStructure;

	// Add Position component if necessary
	FRuntimeMeshPositionComponentVertexStructure<RuntimeVertexType, HasPositionComponent>::AddComponent(VertexBuffer, VertexStructure);

	// Add Normal/Tangent components
	VertexStructure.TangentBasisComponents[0] = RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, Tangent, VET_PackedNormal);
	VertexStructure.TangentBasisComponents[1] = RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, Normal, VET_PackedNormal);

	// Add color component
	VertexStructure.ColorComponent = RUNTIMEMESH_VERTEXCOMPONENT(VertexBuffer, RuntimeVertexType, Color, VET_Color);
		
	// Add all texture channels using template specialization.
	FRuntimeMeshTextureChannelsVertexStructure<RuntimeVertexType, TextureChannels, HalfPrecisionUVs>::AddChannels(VertexBuffer, VertexStructure);

	return VertexStructure;
}






/** Section meant to support the old style interface for creating/updating sections */
template <int32 TextureChannels, bool HalfPrecisionUVs>
struct FRuntimeMeshSectionInternal :
	public FRuntimeMeshSection<FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs>>
{
public:

	typedef FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs> VertexType;


	template<typename Type, bool HasSecondUV>
	struct FUVSetter
	{
		FORCEINLINE static void Set(Type& Vertex, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, int32 VertexIndex, bool bShouldDefault)
		{
			if (UV0.Num() > VertexIndex)
			{
				Vertex.UV0 = UV0[VertexIndex];
			}
			else if (bShouldDefault)
			{
				Vertex.UV0 = FVector2D(0, 0);
			}
		}

		FORCEINLINE static void Serialize(FArchive& Ar, Type& Vertex)
		{
			Ar << Vertex.UV0;
		}
	};

	template<typename Type>
	struct FUVSetter<Type, true>
	{
		FORCEINLINE static void Set(Type& Vertex, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, int32 VertexIndex, bool bShouldDefault)
		{
			if (UV0.Num() > VertexIndex)
			{
				Vertex.UV0 = UV0[VertexIndex];
			}
			else if (bShouldDefault)
			{
				Vertex.UV0 = FVector2D(0, 0);
			}

			if (UV1.Num() > VertexIndex)
			{
				Vertex.UV1 = UV1[VertexIndex];
			}
			else if (bShouldDefault)
			{
				Vertex.UV1 = FVector2D(0, 0);
			}
		}

		FORCEINLINE static void Serialize(FArchive& Ar, Type& Vertex)
		{
			Ar << Vertex.UV0;
			Ar << Vertex.UV1;
		}
	};


	typedef FRuntimeMeshSection<FRuntimeMeshVertex<TextureChannels, HalfPrecisionUVs>> Super;


	FRuntimeMeshSectionInternal(bool bWantsSeparatePositionBuffer /*Ignored for this section type*/) : Super(false) { }
	virtual ~FRuntimeMeshSectionInternal() override { }

	virtual bool UpdateVertexBufferInternal(const TArray<FVector>& Positions, const TArray<FVector>& Normals, const TArray<FRuntimeMeshTangent>& Tangents, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FColor>& Colors) override
	{
		int32 NewVertexCount = (Positions.Num() > 0) ? Positions.Num() : Super::VertexBuffer.Num();
		int32 OldVertexCount = FMath::Min(Super::VertexBuffer.Num(), NewVertexCount);

		// Check existence of data components
		const bool HasPositions = Positions.Num() == NewVertexCount;
		
		// Size the vertex buffer correctly
		if (NewVertexCount != Super::VertexBuffer.Num())
		{
			Super::VertexBuffer.SetNumZeroed(NewVertexCount);
		}

		// Clear the bounding box if we have new positions
		if (HasPositions)
		{
			Super::LocalBoundingBox.Init();
		}
		
		// Loop through existing range to update data
		for (int32 VertexIdx = 0; VertexIdx < OldVertexCount; VertexIdx++)
		{
			auto& Vertex = Super::VertexBuffer[VertexIdx];

			// Update position and bounding box
			if (Positions.Num() == NewVertexCount)
			{
				Vertex.Position = Positions[VertexIdx];
				Super::LocalBoundingBox += Vertex.Position;
			}

			// see if we have a new normal and/or tangent
			bool HasNormal = Normals.Num() > VertexIdx;
			bool HasTangent = Tangents.Num() > VertexIdx;

			// Update normal and tangent together
			if (HasNormal && HasTangent)
			{
				Vertex.Normal = Normals[VertexIdx];
				Vertex.Normal.Vector.W = Tangents[VertexIdx].bFlipTangentY ? 0 : 255;
				Vertex.Tangent = Tangents[VertexIdx].TangentX;
			}
			// Else update only normal keeping the W component 
			else if (HasNormal)
			{
				float W = Vertex.Normal.Vector.W;
				Vertex.Normal = Normals[VertexIdx];
				Vertex.Normal.Vector.W = W;
			}
			// Else update tangent updating the normals W component
			else if (HasTangent)
			{
				Vertex.Tangent = Tangents[VertexIdx].TangentX;
				Vertex.Normal.Vector.W = Tangents[VertexIdx].bFlipTangentY ? 0 : 255;
			}

			// Update color
			if (Colors.Num() > VertexIdx)
			{
				Vertex.Color = Colors[VertexIdx];
			}

			// Set the UVs
			FUVSetter<VertexType, (TextureChannels > 1)>::Set(Vertex, UV0, UV1, VertexIdx, false);
		}

		// Loop through additional range to add new data
		for (int32 VertexIdx = OldVertexCount; VertexIdx < NewVertexCount; VertexIdx++)
		{
			auto& Vertex = Super::VertexBuffer[VertexIdx];

			// Set position
			Vertex.Position = Positions[VertexIdx];
			// Update bounding box
			Super::LocalBoundingBox += Vertex.Position;

			// see if we have a new normal and/or tangent
			bool HasNormal = Normals.Num() > VertexIdx;
			bool HasTangent = Tangents.Num() > VertexIdx;

			// Set normal and tangent both
			if (HasNormal && HasTangent)
			{
				Vertex.Normal = Normals[VertexIdx];
				Vertex.Normal.Vector.W = Tangents[VertexIdx].bFlipTangentY ? 0 : 255;
				Vertex.Tangent = Tangents[VertexIdx].TangentX;
			}
			// Set normal and default tangent
			else if (HasNormal)
			{
				Vertex.Normal = Normals[VertexIdx];
				Vertex.Normal.Vector.W = 255;
				Vertex.Tangent = FVector(1.0f, 0.0f, 0.0f);
			}
			// Default normal and set tangent
			else if (HasTangent)
			{
				Vertex.Normal = FVector(0.0f, 0.0f, 1.0f);
				Vertex.Normal.Vector.W = Tangents[VertexIdx].bFlipTangentY ? 0 : 255;
				Vertex.Tangent = Tangents[VertexIdx].TangentX;
			}
			// Default normal and tangent
			else
			{
				Vertex.Normal = FVector(0.0f, 0.0f, 1.0f);
				Vertex.Normal.Vector.W = 255;
				Vertex.Tangent = FVector(1.0f, 0.0f, 0.0f);
			}

			// Set color or default 
			Vertex.Color = Colors.Num() > VertexIdx ? Colors[VertexIdx] : FColor::White;

			// Set UVs or default
			FUVSetter<VertexType, (TextureChannels > 1)>::Set(Vertex, UV0, UV1, VertexIdx, true);
		}

		return true;
	}

	virtual void GetInternalVertexComponents(int32& NumUVChannels, bool& WantsHalfPrecisionUVs) override
	{
		NumUVChannels = TextureChannels;
		WantsHalfPrecisionUVs = HalfPrecisionUVs;
	}

	virtual void Serialize(FArchive& Ar) override
	{
		Super::Serialize(Ar);
	
		int32 VertexBufferLength = Super::VertexBuffer.Num();
		Ar << VertexBufferLength;
		if (Ar.IsLoading())
		{
			Super::VertexBuffer.SetNum(VertexBufferLength);
		}

		for (int32 Index = 0; Index < VertexBufferLength; Index++)
		{
			auto& Vertex = Super::VertexBuffer[Index];

			Ar << Vertex.Position;
			Ar << Vertex.Normal;
			Ar << Vertex.Tangent;
			Ar << Vertex.Color;
			FUVSetter<VertexType, (TextureChannels > 1)>::Serialize(Ar, Vertex);
		}
	}

};