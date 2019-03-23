#pragma once
#include "Mesh.h"

class MeshGrid : public Mesh
{
public:
	MeshGrid(Shader* shader);
	~MeshGrid();

protected:
	void Create() override;

private:

};