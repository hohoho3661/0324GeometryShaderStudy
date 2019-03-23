#pragma once

class Terrain : public Renderer
{
public:
	typedef VertexTextureNormal TerrainVertex;

public:
	Terrain(Shader* shader, wstring heightMap);
	~Terrain();

	void Update() override;
	void Render() override;

	void BrushType(UINT val) { brushDesc.Type = val; }
	void BrushLocation(D3DXVECTOR3& vec) { brushDesc.Location = vec; }
	void BrushRange(UINT val) { brushDesc.Range = val; }
	void BrushColor(D3DXCOLOR& color) { brushDesc.Color = color; }

public:
	float GetHeight(D3DXVECTOR3& position);
	float GetPickedHeight(D3DXVECTOR3& position);
	D3DXVECTOR3 GetPickedHeight();

	void RaiseHeight(D3DXVECTOR3& position, UINT type, UINT range
		, float speed, float wantHeight); // 높이조정

	void InsertBillBoard(D3DXVECTOR3& position, UINT type, UINT range, UINT textureNumber);

	void BaseMap(wstring file);
	void LayerMap(wstring file, wstring alpha);

public:
	void Save(wstring savePath);
	void Load(wstring savePath);

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();

private:
	struct BrushDesc
	{
		D3DXCOLOR Color = D3DXCOLOR(0, 1, 0, 1);
		D3DXVECTOR3 Location = D3DXVECTOR3(-1, -1, -1);
		int Type = 0;
		int Range = 1;

		float Padding[3];
	} brushDesc;

	struct GridLineDesc
	{
		D3DXCOLOR Color = D3DXCOLOR(1, 1, 1, 1);

		int Visible = 1;
		float Thickness = 0.1f;
		float Size = 25.5f;

		float Padding;
	} gridLineDesc;

private:
	Texture* heightMap;

	UINT width, height;

	TerrainVertex* vertices;
	UINT* indices;


	ConstantBuffer* brushBuffer;
	ID3DX11EffectConstantBuffer* sBrushBuffer;

	ConstantBuffer* gridLineBuffer;
	ID3DX11EffectConstantBuffer* sGridLineBuffer;

	Texture* baseMap;
	ID3DX11EffectShaderResourceVariable* sBaseMap;

	Texture* layerMap;
	ID3DX11EffectShaderResourceVariable* sLayerMap;

	Texture* alphaMap;
	ID3DX11EffectShaderResourceVariable* sAlphaMap;

private:
	//빌보드
	Shader* billShader;

	class BillBoard* billBoard;

	vector<wstring> textureName;

};