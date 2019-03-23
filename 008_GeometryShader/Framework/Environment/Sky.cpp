#include "Framework.h"
#include "Sky.h"

Sky::Sky()
{
	shader = new Shader(L"022_Sky.fx");
	sData = shader->Variable("Data");
	
	sphere = new MeshSphere(shader, 0.5f);
}

Sky::~Sky()
{
	SAFE_DELETE(shader);
	SAFE_DELETE(sphere);
}

void Sky::Update()
{
	D3DXVECTOR3 position;
	Context::Get()->GetCamera()->Position(&position);

	sphere->GetTransform()->Position(position);
	sphere->Update();
}

void Sky::Render()
{
	sData->SetRawValue(&dataDesc, 0, sizeof(DataDesc));

	sphere->Render();
}
