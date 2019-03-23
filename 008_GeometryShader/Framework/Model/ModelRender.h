#pragma once

class ModelRender
{
public:
	ModelRender(Shader* shader, Model* model);
	~ModelRender();

	void Update();
	void Render();

	Transform* GetTransform() { return transform; }

private:
	Model* model;
	Transform* transform;

	D3DXMATRIX renderTransforms[MODEL_MAX_TRANSFORMS];
};