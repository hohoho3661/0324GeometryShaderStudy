#pragma once

class ModelMeshPart
{
public:
	friend class Model;
	friend class ModelMesh;

private:
	ModelMeshPart();
	~ModelMeshPart();

public:
	void SetShader(Shader* shader);
	void Pass(UINT val) { pass = val; }

private:
	void Transforms(D3DXMATRIX* transforms);
	void SetTransform(Transform* transform);

	void Update();
	void Render();

	void Binding(Model* model);

private:
	struct BoneDesc
	{
		D3DXMATRIX Transforms[MODEL_MAX_TRANSFORMS];

		UINT Index;
		float Padding[3];
	} boneDesc;

private:
	wstring name;

	Shader* shader;
	UINT pass;

	PerFrame* perFrame;
	Transform* transform;

	class ModelMesh* parent;

	Material* material;
	wstring materialName;

	UINT startVertex;
	UINT vertexCount;

	UINT startIndex;
	UINT indexCount;

	ConstantBuffer* boneBuffer;
	ID3DX11EffectConstantBuffer* sBoneBuffer;
};