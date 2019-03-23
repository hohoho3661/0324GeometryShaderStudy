#include "Framework.h"
#include "ModelRender.h"
#include "ModelMesh.h"

ModelRender::ModelRender(Shader * shader, Model * model)
	: model(model)
{
	transform = new Transform();

	for (ModelMesh* mesh : model->Meshes())
		mesh->SetShader(shader);
	

	D3DXMATRIX boneTransforms[MODEL_MAX_TRANSFORMS];
	for (UINT i = 0; i < model->BoneCount(); i++)
	{
		ModelBone* bone = model->BoneByIndex(i);

		D3DXMATRIX parentTransform;

		int parentIndex = bone->ParentIndex();
		if (parentIndex < 0)
			D3DXMatrixIdentity(&parentTransform);
		else
			parentTransform = boneTransforms[parentIndex];

		
		D3DXMATRIX matrix = bone->Transform();

		boneTransforms[i] = parentTransform;
		renderTransforms[i] = matrix * boneTransforms[i];
	}

	for (ModelMesh* mesh : model->Meshes())
	{
		mesh->Transforms(renderTransforms);
	}
}

ModelRender::~ModelRender()
{
	SAFE_DELETE(transform);
}

void ModelRender::Update()
{
	for (ModelMesh* mesh : model->Meshes())
	{
		mesh->Update();
	}
}

void ModelRender::Render()
{
	for (ModelMesh* mesh : model->Meshes())
	{
		mesh->SetTransform(transform);
		mesh->Render();
	}
}