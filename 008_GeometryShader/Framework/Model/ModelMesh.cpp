#include "Framework.h"
#include "ModelMesh.h"
#include "ModelMeshPart.h"

ModelBone::ModelBone()
{

}

ModelBone::~ModelBone()
{

}



///////////////////////////////////////////////////////////////////////////////

ModelMesh::ModelMesh()
{
}

ModelMesh::~ModelMesh()
{
	SAFE_DELETE(vertexBuffer);
	SAFE_DELETE(indexBuffer);

	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE_ARRAY(indices);

	for (ModelMeshPart* part : meshParts)
		SAFE_DELETE(part);
}

void ModelMesh::Pass(UINT pass)
{
}

void ModelMesh::SetShader(Shader * shader)
{
	for (ModelMeshPart* part : meshParts)
		part->SetShader(shader);
}

void ModelMesh::Update()
{
	for (ModelMeshPart* part : meshParts)
		part->Update();
}

void ModelMesh::Render()
{
	vertexBuffer->Render();
	indexBuffer->Render();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (ModelMeshPart* part : meshParts)
		part->Render();
}

void ModelMesh::Transforms(D3DXMATRIX * transforms)
{
	for (ModelMeshPart* part : meshParts)
		part->Transforms(transforms);
}

void ModelMesh::SetTransform(Transform * transform)
{
	for (ModelMeshPart* part : meshParts)
		part->SetTransform(transform);
}

void ModelMesh::Binding(Model* model)
{
	vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(Model::ModelVertex));
	indexBuffer = new IndexBuffer(indices, indexCount);

	for (ModelMeshPart* part : meshParts)
		part->Binding(model);
}
