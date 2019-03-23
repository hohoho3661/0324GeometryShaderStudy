#pragma once

class Material
{
public:
	Material();
	Material(Shader* shader);
	~Material();

	Shader* GetShader() { return shader; }
	void SetShader(Shader* shader);


	void Name(wstring val) { name = val; }
	wstring Name() { return name; }

	D3DXCOLOR Ambient() { return colorDesc.Ambient; }
	void Ambient(D3DXCOLOR& color);
	void Ambient(float r, float g, float b, float a = 1.0f);

	D3DXCOLOR Diffuse() { return colorDesc.Diffuse; }
	void Diffuse(D3DXCOLOR& color);
	void Diffuse(float r, float g, float b, float a = 1.0f);

	D3DXCOLOR Specular() { return colorDesc.Specular; }
	void Specular(D3DXCOLOR& color);
	void Specular(float r, float g, float b, float a = 1.0f);

	float Shininess() { return colorDesc.Shininess; }
	void Shininess(float val);


	Texture* DiffuseMap() { return diffuseMap; }
	void DiffuseMap(string file);
	void DiffuseMap(wstring file);

	Texture* SpecularMap() { return specularMap; }
	void SpecularMap(string file);
	void SpecularMap(wstring file);

	Texture* NormalMap() { return normalMap; }
	void NormalMap(string file);
	void NormalMap(wstring file);

	void Render();


private:
	void Initialize();

private:
	struct ColorDesc
	{
		D3DXCOLOR Ambient = D3DXCOLOR(0, 0, 0, 1);
		D3DXCOLOR Diffuse = D3DXCOLOR(1, 1, 1, 1);
		D3DXCOLOR Specular = D3DXCOLOR(0, 0, 0, 1);

		float Shininess = 0;
		float Padding[3];
	} colorDesc;

private:
	Shader* shader;

	wstring name;

	Texture* diffuseMap;
	Texture* specularMap;
	Texture* normalMap;

	ConstantBuffer* buffer;

	ID3DX11EffectConstantBuffer* sBuffer;
	ID3DX11EffectShaderResourceVariable* sDiffuseMap;
	ID3DX11EffectShaderResourceVariable* sSpecularMap;
	ID3DX11EffectShaderResourceVariable* sNormalMap;
};