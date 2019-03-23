#include "Framework.h"
#include "Context.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"
#include "Viewer/Freedom.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SAFE_DELETE(instance);
}

Context::Context()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);
	camera = new Freedom();

	lightColor = D3DXCOLOR(0, 0, 0, 1);
	lightDirection = D3DXVECTOR3(-1, -1, 1);
	lightPosition = D3DXVECTOR3(0, 0, 0);
}

Context::~Context()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(perspective);
	SAFE_DELETE(viewport);
}

void Context::Update()
{
	camera->Update();

	ImGui::SliderFloat3("Light Direction", (float *)&lightDirection, -1, 1);
}

void Context::Render()
{
	viewport->RSSetViewport();
}

D3DXMATRIX Context::View()
{
	D3DXMATRIX view;
	camera->GetMatrix(&view);

	return view;
}

D3DXMATRIX Context::Projection()
{
	D3DXMATRIX projection;
	perspective->GetMatrix(&projection);

	return projection;
}
