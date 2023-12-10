#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#pragma pack(push, 1)
struct Vertex
{
    float vertex[3];
    float texture[2];
    float normal[3];


};
#pragma pack(pop)