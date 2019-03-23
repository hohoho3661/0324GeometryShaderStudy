#include "stdafx.h"
#include "Export.h"
#include "Assimp/Loader.h"

void Export::Initialize()
{
	Loader* loader = NULL;

	////Tower
	//loader = new Loader();
	//loader->ReadFile(L"Tower/Tower.fbx");
	//loader->ExportMaterial(L"Tower/Tower");
	//loader->ExportMesh(L"Tower/Tower");

	tower = new Model();
	tower->ReadMaterial(L"Tower/Tower");
	tower->ReadMesh(L"Tower/Tower");

	towerShader = new Shader(L"020_Model.fx");
	towerRender = new ModelRender(towerShader, tower);
	towerRender->GetTransform()->Scale(0.01f, 0.01f, 0.01f);


	////Tank
	//loader = new Loader();
	//loader->ReadFile(L"Tank/Tank.fbx");
	//loader->ExportMaterial(L"Tank/Tank", false);
	//loader->ExportMesh(L"Tank/Tank");

	tank = new Model();
	tank->ReadMaterial(L"Tank/Tank");
	tank->ReadMesh(L"Tank/Tank");

	tankShader = new Shader(L"020_Model.fx");
	for (UINT i = 0; i < 5; i++)
	{
		ModelRender* tankRender = new ModelRender(tankShader, tank);		
		tankRender->GetTransform()->Position(i * 10, 0, 0);

		tankRenders.push_back(tankRender);
	}	
}

void Export::Ready()
{

}

void Export::Destroy()
{
	SAFE_DELETE(tower);
	SAFE_DELETE(towerShader);
	SAFE_DELETE(towerRender);

	SAFE_DELETE(tank);
	SAFE_DELETE(tankShader);

	for(ModelRender* tankRender : tankRenders)
		SAFE_DELETE(tankRender);
}

void Export::Update()
{
	towerRender->Update();

	static UINT count = 0;
	ImGui::SliderInt("Number", (int *)&count, 0, 4);

	float speed = 5.0f;
	D3DXVECTOR3 position;
	tankRenders[count]->GetTransform()->Position(&position);

	if (Keyboard::Get()->Press(VK_UP))
		position.z += speed * Time::Delta();
	else if (Keyboard::Get()->Press(VK_DOWN))
		position.z -= speed * Time::Delta();

	if (Keyboard::Get()->Press(VK_RIGHT))
		position.x += speed * Time::Delta();
	else if (Keyboard::Get()->Press(VK_LEFT))
		position.x -= speed * Time::Delta();

	tankRenders[count]->GetTransform()->Position(position);

	
	for (ModelRender* tankRender : tankRenders)
		tankRender->Update();
}

void Export::PreRender()
{

}

void Export::Render()
{
	towerRender->Render();
	
	for (ModelRender* tankRender : tankRenders)
		tankRender->Render();
}

void Export::PostRender()
{

}

void Export::ResizeScreen()
{

}