#include "framework.h"
#include "ModelMeshPart.h"
#include "ModelMesh.h"

ModelMeshPart::ModelMeshPart()
	: material(NULL), transform(NULL), perFrame(NULL),pass(0)
{
	boneBuffer = new ConstantBuffer(&boneDesc, sizeof(BoneDesc));
}

ModelMeshPart::~ModelMeshPart()
{
	SAFE_DELETE(boneBuffer);
	SAFE_DELETE(transform);
	SAFE_DELETE(perFrame);
}

void ModelMeshPart::SetShader(Shader * shader)
{
	this->shader = shader;

	SAFE_DELETE(transform);
	transform = new Transform(shader);


	SAFE_DELETE(perFrame);
	perFrame = new PerFrame(shader);

	material->SetShader(shader);

	sBoneBuffer = shader->AsConstantBuffer("CB_Bone");
}

void ModelMeshPart::Transforms(D3DXMATRIX * transforms)
{
	memcpy(boneDesc.Transforms, transforms, sizeof(D3DXMATRIX) * MODEL_MAX_TRANSFORMS);

}

void ModelMeshPart::SetTransform(Transform * transform)
{
	this->transform->Set(transform);
}

void ModelMeshPart::Update()
{
	boneDesc.Index = parent->BoneIndex();

	perFrame->Update();
	transform->Update();
}

void ModelMeshPart::Render()
{
	boneBuffer->Apply();
	sBoneBuffer->SetConstantBuffer(boneBuffer->Buffer());
	
	perFrame->Render();
	transform->Render();
	material->Render();
	shader->DrawIndexed(0, pass, indexCount, startIndex, 0);
}

void ModelMeshPart::Binding(Model* model)
{
	Material* srcMaterial = model->MaterialByName(materialName); // 원본메터리얼
	material = new Material();

	material->Ambient(srcMaterial->Ambient());
	material->Diffuse(srcMaterial->Diffuse());
	material->Specular(srcMaterial->Specular());
	material->Shininess(srcMaterial->Shininess());

	if (srcMaterial->DiffuseMap() != NULL)
	{
		material->DiffuseMap(srcMaterial->DiffuseMap()->GetFile());
	}
	if (srcMaterial->SpecularMap() != NULL)
	{
		material->SpecularMap(srcMaterial->SpecularMap()->GetFile());
	}
	if (srcMaterial->NormalMap() != NULL)
	{
		material->NormalMap(srcMaterial->NormalMap()->GetFile());
	}
}
