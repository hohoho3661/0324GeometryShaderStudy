#include "000_Header.fx"
#include "000_Terrain.fx"

//-----------------------------------------------------------------------------
struct VertexOutput
{
    float4 Position : SV_Position0;
    float3 oPosition : Position1;
    float3 Normal : Normal0;
    float2 Uv : UV0;
};

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
  
    output.Position = WorldPosition(input.Position);
    output.Position = ViewProjection(output.Position);
    output.Normal = WorldNormal(input.Normal); // 월드공간 변화를 무조건 하고난후 Normal 해야됨

    
    output.oPosition = input.Position.xyz;
    output.Uv = input.Uv;

    return output;
}

float4 PS(VertexOutput input) : SV_TARGET0
{
    float4 diffuse = GetTerrainColor(input.Uv);
    //float4 diffuse = float4(0.5f, 0.7f, 0.5f, 1);
    
    float3 normal = normalize(input.Normal);
    float3 light = -LightDirection;
    float NdotL = dot(normal, light);

    float3 color = GetGridLineColor(input.oPosition);
    float3 BrushColor = GetBrushColor(input.oPosition);

    //return float4(color, 1);
    return (diffuse * NdotL) + float4(color, 1) + float4(BrushColor, 1);
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

RasterizerState RS
{
    FillMode = Wireframe;
};

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(RS);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}