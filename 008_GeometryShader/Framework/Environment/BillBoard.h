#pragma once

class BillBoard : public Renderer
{
public:
	BillBoard(Shader* shader, vector<wstring>& textureNames);
	~BillBoard();

	void FixedY(bool val) { fixedY = val; }

	void Add(D3DXVECTOR3& position, D3DXVECTOR2& scale, UINT textureNumber);
//	void Add(D3DXVECTOR3& position, float& scaleX, float& scaleY);
	
	void Clear();

public:
	void CreateBuffer();
		
	void Update();
	void Render();

private:
	struct VertexScale
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Scale;
		UINT textureNumber;
	};

public:
	size_t GetSize() { return vertices.size(); }
	vector<VertexScale> GetVertices() { return vertices; }

private:
	bool fixedY;

	vector<VertexScale> vertices;

	TextureArray* textures;
};