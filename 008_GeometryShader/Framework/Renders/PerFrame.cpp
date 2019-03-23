#include "Framework.h"
#include "PerFrame.h"

PerFrame::PerFrame(Shader * shader)
	: shader(shader)
{
	buffer = new ConstantBuffer(&bufferDesc, sizeof(BufferDesc));

	sBuffer = shader->AsConstantBuffer("CB_PerFrame");


	D3DXMatrixIdentity(&bufferDesc.View);
	D3DXMatrixIdentity(&bufferDesc.ViewInverse);
	D3DXMatrixIdentity(&bufferDesc.Projection);
	D3DXMatrixIdentity(&bufferDesc.ViewProjection);
}

PerFrame::~PerFrame()
{
	SAFE_DELETE(buffer);
}

void PerFrame::Update()
{
	bufferDesc.View = Context::Get()->View();
	D3DXMatrixInverse(&bufferDesc.ViewInverse, NULL, &bufferDesc.View);

	bufferDesc.Projection = Context::Get()->Projection();
	bufferDesc.ViewProjection = bufferDesc.View * bufferDesc.Projection;

	bufferDesc.LightColor = Context::Get()->LightColor();
	bufferDesc.LightPosition = Context::Get()->LightPosition();
	bufferDesc.LightDirection = Context::Get()->LightDirection();

	bufferDesc.Time = Time::Get()->Running();
}

void PerFrame::Render()
{
	buffer->Apply();

	sBuffer->SetConstantBuffer(buffer->Buffer());
}
