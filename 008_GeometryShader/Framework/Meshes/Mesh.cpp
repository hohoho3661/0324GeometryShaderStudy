#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Shader * shader)
	: Renderer(shader), color(0, 0, 0, 1)
{
	sColor = shader->AsVector("Color");
}

Mesh::~Mesh()
{
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE_ARRAY(indices);
}

void Mesh::Render()
{
	if (vertexBuffer == NULL && indexBuffer == NULL)
	{
		Create();

		vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(MeshVertex));
		indexBuffer = new IndexBuffer(indices, indexCount);
	}

	Renderer::Render();
	sColor->SetFloatVector(color);

	shader->DrawIndexed(0, Pass(), indexCount);
}

void Mesh::Color(D3DXCOLOR & val)
{
	color = val;
}

void Mesh::Color(float r, float g, float b)
{
	Color(D3DXCOLOR(r, g, b, 1));
}