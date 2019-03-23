Texture2D BaseMap;
SamplerState BaseSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D LayerMap;
SamplerState LayerSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D AlphaMap;
SamplerState AlphaSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

float4 GetTerrainColor(float2 uv)
{    
    float4 base = BaseMap.Sample(BaseSampler, uv);
    float4 layer = LayerMap.Sample(LayerSampler, uv);
    float4 alpha = AlphaMap.Sample(AlphaSampler, uv);

    return lerp(base, layer, (1 - alpha.g) * 0.2f);
}

//-----------------------------------------------------------------------------
// Brush
//-----------------------------------------------------------------------------
cbuffer CB_Brush // C버퍼는 16미트 맞추는거 잊지말고
{
    float4 BrushColor;
    float3 BrushLocation;
    int BrushType;
    int BrushRange;
};

float3 GetBrushColor(float3 position)
{
    [flatten]
    if (BrushType == 0)
        return float3(0, 0, 0); // 브러쉬타입이 0이면 아무것도 리턴하지않음

    if (BrushType == 1
        || BrushType == 3) // 사각형모양으로
    {
        if ((position.x >= (BrushLocation.x - BrushRange)) && // 사각형 범위 판단
            (position.x <= (BrushLocation.x + BrushRange)) &&
            (position.z >= (BrushLocation.z - BrushRange)) &&
            (position.z <= (BrushLocation.z + BrushRange)))
        {
            return BrushColor.rgb;
        }
    }

    if (BrushType == 2) // 원으로할거임
    {
        float dx = position.x - BrushLocation.x; // 거리구하기
        float dz = position.z - BrushLocation.z;

        float dist = sqrt(dx * dx + dz * dz); // 피타고라스정리로 거리구하기
        //float dist = distance(dx, dz);

        if (dist <= BrushRange)
            return BrushColor.rgb;
    }

    return float3(0, 0, 0);
}

//-----------------------------------------------------------------------------
// GridLine
//-----------------------------------------------------------------------------

cbuffer CB_GridLine
{
    float4 GridLineColor;

    int VisibleGridLine;
    float GridLineThickness;
    float GridLineSize;
};

//float3 GetGridLineColor(float3 position)
//{
//    [flatten]
//    if (VisibleGridLine == 0)
//        return float3(0, 0, 0);

//    float2 grid = position.xz / GridLineSize;
//    //grid = frac(grid);
//    grid = abs(frac(grid - 0.5f) - 0.5f); // abs는 절대값,, 가운데를 중점으로 맞춤

//    float thick = GridLineThickness / GridLineSize;

//    [flatten]
//    if (grid.x < thick || grid.y < thick)
//        return GridLineColor.rgb;

//    return float3(0, 0, 0);
//}

float3 GetGridLineColor(float3 position)
{
    [flatten]
    if (VisibleGridLine == 0)
        return float3(0, 0, 0);

    float2 grid = position.xz / GridLineSize;
    //grid = frac(grid);
    float2 range = abs(frac(grid - 0.5f) - 0.5f); // abs는 절대값
    
    float2 speed = fwidth(grid); // fwidth 편미분,, 안티 얼리어싱,, 멀어지는거에대한 비례값(fwidth)을 구해서 계산해줌
    
    float2 pixel = range / speed;

    float weight = saturate(min(pixel.x, pixel.y) - GridLineThickness); // 픽셀x,y중에 작은값,, 0 or 0.1~0.9

    return lerp(GridLineColor.rgb, float3(0, 0, 0), weight);

    // lerp(A,B,t)
    // t = 구하고싶은 비율값 (0부터1)
    // (1 - t) * A + t * B
}