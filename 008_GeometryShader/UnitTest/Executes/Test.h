#pragma once
#include "Systems/IExecute.h"

class Test : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ResizeScreen() override;
	
private:
	class Sky* sky;

	Shader* shader;
	class Terrain* terrain;
	
private:
	UINT type;
	D3DXCOLOR color;
	UINT range;

	float speed;
	float wantHeight;

	UINT treeNumber;
};