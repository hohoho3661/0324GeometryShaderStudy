#include "stdafx.h"
#include "Test.h"
#include "Environment/Sky.h"
#include "Environment/Terrain.h"
#include "Environment/BillBoard.h"

void Test::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(12, 0);
	Context::Get()->GetCamera()->Position(102, 23, -2);

	//Sky
	{
		sky = new Sky();
	}

	//Terrain
	{
		shader = new Shader(L"008_TerrainBrush.fx");
		terrain = new Terrain(shader, L"HeightMaps/Gray256.png");
		terrain->BaseMap(L"Terrain/Dirt.png");
		terrain->LayerMap(L"Terrain/Grass (Lawn).jpg", L"HeightMaps/Gray256.png");
	}
	
	//
	type = 0;
	color = D3DXCOLOR(0, 1, 0, 1);
	range = 10;
	speed = 5.0f;
	wantHeight = 0.0f;

	treeNumber = 0;
}

void Test::Ready()
{

}

void Test::Destroy()
{
	
}

void Test::Update()
{
	sky->Update();

	//브러쉬 옵션
	D3DXVECTOR3 picked = terrain->GetPickedHeight();
	ImGui::LabelText("Picking", "%.2f, %.2f, %.2f", picked.x, picked.y, picked.z);
	
	// TestBrush
	ImGui::SliderInt("Type", (int *)&type, 0, 3);
	ImGui::ColorEdit3("Color", (float *)&color);
	ImGui::SliderInt("Range", (int *)&range, 1, 50);
	ImGui::SliderFloat("Speed", (float *)&speed, 1.0f, 70.0f);
	ImGui::SliderInt("Height", (int *)&wantHeight, 0, 50);

	terrain->BrushLocation(picked);
	terrain->BrushColor(color);
	terrain->BrushRange(range);
	terrain->BrushType(type);

	// 터레인(빌보드 저장,불러오기, 세팅 여기안에 있슴)
	terrain->Update();


	// 텍스쳐(나무) 선택 버튼 만들기
	if (ImGui::Button("T1") == true)
	{
		treeNumber = 0;
	}
	if (ImGui::Button("T2") == true)
	{
		treeNumber = 1;
	}
	if (ImGui::Button("T3") == true)
	{
		treeNumber = 2;
	}
	if (ImGui::Button("T4") == true)
	{
		treeNumber = 3;
	}
	if (ImGui::Button("T5") == true)
	{
		treeNumber = 4;
	}

	//
	if (Mouse::Get()->Down(0) && type == 3)
	{
		terrain->InsertBillBoard(picked, type, range, treeNumber);
	}
	//if (Mouse::Get()->Press(0))
	//{
	//	terrain->RaiseHeight(picked, type, range, speed, wantHeight);
	//}




}

void Test::PreRender()
{

}

void Test::Render()
{
	sky->Render();
	terrain->Render();
	
	//billBoard->Render();
}

void Test::PostRender()
{

}

void Test::ResizeScreen()
{

}