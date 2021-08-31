#pragma once

#include "pch.h"

using namespace DirectX;

namespace GameProject
{
    // Constant buffer used to send MVP matrices to the vertex shader.
    struct ConstantBuffer
    {
        XMFLOAT4X4 model;
        XMFLOAT4X4 view;
        XMFLOAT4X4 projection;
    };

    // Used to send per-vertex data to the vertex shader.
    struct VertexPositionColor
    {
        XMFLOAT3 pos;
        XMFLOAT3 color;
    };
}