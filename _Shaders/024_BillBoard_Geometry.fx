#include "000_Header.fx"
#include "000_Terrain.fx"
//-----------------------------------------------------------------------------
struct VertexInput
{
    float4 Position : Position0;
    float2 Scale : Scale0;

    uint VertexID : SV_VertexID; // 정점 배열번호
};

struct VertexOutput
{
    float4 Position : Position0;    
    float2 Scale : Scale0;


    uint VertexID : VertexID;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    //input.Position.x += input.VertexID * 5.0f;

    output.Position = input.Position;
    output.Scale = input.Scale;
    output.VertexID = input.VertexID;


    return output;
}

struct GeometryOutput
{
    float4 Position : SV_Position0; // sv(시스템 벨류)는 픽셀세이더에 들어가는거,,, rs완료된 ndc좌표
    float2 Uv : Uv0;
        
    uint VertexID : VertexID;
};

static const float2 Uvs[4] = //static const(상수로만든거)
{
    float2(0, 1), float2(0, 0), float2(1, 1), float2(1, 0)
};

[maxvertexcount(4)] // 리턴할 최대 정점 갯수
void GS(point VertexOutput input[1], inout TriangleStream<GeometryOutput> stream)
{
    float3 up = float3(0, 1, 0);
    float3 right = float3(1, 0, 0);

    float2 size = input[0].Scale * 0.5f;

    float3 position[4];
    position[0] = float3(input[0].Position.xyz - size.x * right - size.y * up);
    position[1] = float3(input[0].Position.xyz - size.x * right + size.y * up);
    position[2] = float3(input[0].Position.xyz + size.x * right - size.y * up);
    position[3] = float3(input[0].Position.xyz + size.x * right + size.y * up);
    
    GeometryOutput output;

    [roll(4)]
    for (int i = 0; i < 4; i++)
    {
        output.Position = WorldPosition(float4(position[i], 1));
        output.Position = ViewProjection(output.Position);
        output.Uv = Uvs[i];
        output.VertexID = input[0].VertexID;        

        stream.Append(output);
    }
}

Texture2DArray Map; // Texture2DArray = 텍스쳐 배열, 텍스쳐크기가 일정해야됨

float4 PS(GeometryOutput input) : SV_TARGET0
{
    float3 uvw = float3(input.Uv, input.VertexID);
    float4 diffuse = Map.Sample(Sampler, uvw);
            
    if (diffuse.a < 0.3)
        discard;

    return diffuse;
}
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
        SetGeometryShader(CompileShader(gs_5_0, GS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(RS);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetGeometryShader(CompileShader(gs_5_0, GS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}