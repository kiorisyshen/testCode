#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <simd/simd.h>
#include <metal_stdlib>

struct vert_in {
    vector_float2 inputPosition;
    vector_float4 inputColor;
};

struct vert_out {
    vector_float4 position [[position]];
    vector_float4 color;
};

vertex vert_out
vertexShader(uint vertexID [[vertex_id]],
             constant vert_in *vertices [[buffer(0)]]) {
    vert_out out;

    // Index into the array of positions to get the current vertex.
    // The positions are specified in pixel dimensions (i.e. a value of 100
    // is 100 pixels from the origin).
    vector_float2 pixelSpacePosition = vertices[vertexID].inputPosition.xy;

    // To convert from positions in pixel space to positions in clip-space,
    //  divide the pixel coordinates by half the size of the viewport.
    out.position    = vector_float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixelSpacePosition;

    // Pass the input color directly to the rasterizer.
    out.color = vertices[vertexID].inputColor;

    return out;
}

fragment float4 fragmentShader(vert_out in [[stage_in]]) {
    // Return the interpolated color.
    return in.color;
}
