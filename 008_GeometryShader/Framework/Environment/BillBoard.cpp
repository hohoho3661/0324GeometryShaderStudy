#include "Framework.h"
#include "BillBoard.h"

BillBoard::BillBoard(Shader * shader, vector<wstring>& textureNames)
	: Renderer(shader), fixedY(true)
{
	Topology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	textures = new TextureArray(textureNames, 256, 256);
	shader->AsSRV("Map")->SetResource(textures->SRV());
	
}

BillBoard::~BillBoard()
{
	SAFE_DELETE(textures);
}

void BillBoard::Add(D3DXVECTOR3 & position, D3DXVECTOR2 & scale, UINT textureNumber)
{
	VertexScale vertex;
	vertex.Position = position;
	vertex.Scale = scale;
	vertex.textureNumber = textureNumber;
	
	vertices.push_back(vertex);
}

void BillBoard::Clear()
{
	vertices.clear();
}


//void BillBoard::Add(D3DXVECTOR3 & position, float & scaleX, float & scaleY)
//{
//	D3DXVECTOR2 scale;
//	scale.x = scaleX;
//	scale.y = scaleY;
//
//	VertexScale vertex;
//	vertex.Position = position;
//	vertex.Scale = scale;
//
//	vertices.push_back(vertex);
//}

void BillBoard::CreateBuffer()
{
	SAFE_DELETE(vertexBuffer); // ������ �����
	assert(vertexBuffer == NULL); // ��������   // �������
	vertexBuffer = new VertexBuffer(&vertices[0], vertices.size(), sizeof(VertexScale));
}


void BillBoard::Update()
{
	Renderer::Update();

	////================= ������ ========================
	////decompose ���
	//D3DXMATRIX V = Context::Get()->View();
	//D3DXMatrixInverse(&V, NULL, &V);
	//
	//float x = 0.0f;
	//if (fixedY == false)
	//	x = asin(-V._32);

	//float z = atan2(V._12, V._22);
	//float y = atan2(V._31, V._33);
	//
	////TODO:: transform->rotation,, �κ�(textures)���� �ȵ��ư��� billBoard��ü�� ���ư�
	////transform->Rotation(x, y, z);
	////transform->Update();
}

void BillBoard::Render()
{
	Renderer::Render();

	shader->Draw(0, Pass(), vertices.size());
}
