#pragma once
#include "Systems/IExecute.h"

class Export : public IExecute
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
	Model* tower;
	Shader* towerShader;
	ModelRender* towerRender;

	Model* tank;
	Shader* tankShader;
	vector<ModelRender *> tankRenders;
};