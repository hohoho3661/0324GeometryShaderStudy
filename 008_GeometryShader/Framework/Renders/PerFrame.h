#pragma once

class PerFrame
{
public:
	PerFrame(Shader* shader);
	~PerFrame();

public:
	void Update();
	void Render();

private:
	struct BufferDesc
	{
		D3DXMATRIX View;
		D3DXMATRIX ViewInverse;
		D3DXMATRIX Projection;
		D3DXMATRIX ViewProjection;

		D3DXCOLOR LightColor;
		D3DXVECTOR3 LightDirection;
		float Time;

		D3DXVECTOR3 LightPosition;
		float Padding;
	} bufferDesc;

private:
	Shader* shader;

	ConstantBuffer* buffer;
	ID3DX11EffectConstantBuffer* sBuffer;
};