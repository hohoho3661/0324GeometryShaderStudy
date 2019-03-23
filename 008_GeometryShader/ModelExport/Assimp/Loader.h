#pragma once

class Loader
{
public:
	Loader();
	~Loader();

	void ReadFile(wstring file);

public:
	void ExportMaterial(wstring savePath, bool bOverwrite = true);

private:
	void ReadMaterial();
	void WriteMaterial(wstring savePath, bool bOverwrite);
	string WriteTexture(string file, string saveFolder);

public:
	void ExportMesh(wstring savePath, bool bOverwrite = true);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int bone);
	void WriteMeshData(wstring savePath, bool bOverwrite);

private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct AsMaterial *> materials;
	vector<struct AsBone *> bones;
	vector<struct AsMesh *> meshes;
};