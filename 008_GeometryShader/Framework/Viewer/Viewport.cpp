#include "Framework.h"
#include "Viewport.h"

Viewport::Viewport(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	Set(width, height, x, y, minDepth, maxDepth);
}

Viewport::~Viewport()
{
	
}

void Viewport::Set(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	viewport.TopLeftX = this->x = x;
	viewport.TopLeftY = this->y = y;
	viewport.Width = this->width = width;
	viewport.Height = this->height = height;
	viewport.MinDepth = this->minDepth = minDepth;
	viewport.MaxDepth = this->maxDepth = maxDepth;

	RSSetViewport();
}

void Viewport::GetRay(OUT D3DXVECTOR3 * position, OUT D3DXVECTOR3 * direction, D3DXMATRIX & W, D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR3 mouse = Mouse::Get()->GetPosition();

	D3DXVECTOR2 point;
	//Inv Viewport
	{
		point.x = ((2.0f * mouse.x) / width) - 1.0f;
		point.y = (((2.0f * mouse.y) / height) - 1.0f) * -1.0f;
	}

	//Inv Projection
	{
		point.x = point.x / P._11;
		point.y = point.y / P._22;
	}

	D3DXVECTOR3 cameraPosition;
	//Inv View
	{
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &V);

		cameraPosition = D3DXVECTOR3(invView._41, invView._42, invView._43);

		D3DXVec3TransformNormal(direction, &D3DXVECTOR3(point.x, point.y, 1), &invView);
		D3DXVec3Normalize(direction, direction);
	}

	//InvWorld
	{
		D3DXMATRIX invWorld;
		D3DXMatrixInverse(&invWorld, NULL, &W);

		D3DXVec3TransformCoord(position, &cameraPosition, &invWorld);
		D3DXVec3TransformNormal(direction, direction, &invWorld);
		D3DXVec3Normalize(direction, direction);
	}
	
}

void Viewport::Project(OUT D3DXVECTOR3 * position, D3DXVECTOR3 & source, D3DXMATRIX & W, D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXMATRIX matrix = W * V * P;

	D3DXVECTOR3 temp = source;
	D3DXVec3TransformCoord(position, &temp, &matrix);

	position->x = ((position->x + 1.0f) * 0.5f) * width + x;
	position->y = ((-position->y + 1.0f) * 0.5f) * height + y;
	position->z = (position->z * (maxDepth - minDepth)) + minDepth;
}

void Viewport::Unproject(OUT D3DXVECTOR3 * position, D3DXVECTOR3 & source, D3DXMATRIX & W, D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXMATRIX matrix = W * V * P;
	D3DXMatrixInverse(&matrix, NULL, &matrix);

	D3DXVECTOR3 temp = source;
	position->x = ((temp.x - x) / width) * 2.0f - 1.0f;
	position->y = (((temp.y - y) / height) * 2.0f - 1.0f) * -1.0f;
	position->z = (temp.z - minDepth) / (maxDepth - minDepth);

	D3DXVec3TransformCoord(position, position, &matrix);
}

void Viewport::RSSetViewport()
{
	D3D::GetDC()->RSSetViewports(1, &viewport);
}