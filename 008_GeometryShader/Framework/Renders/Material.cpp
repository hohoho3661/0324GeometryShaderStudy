#include "Framework.h"
#include "Material.h"

Material::Material()
{
	Initialize();
}

Material::Material(Shader * shader)
{
	Initialize();

	SetShader(shader);
}

void Material::Initialize()
{
	name = L"";

	diffuseMap = NULL;
	specularMap = NULL;
	normalMap = NULL;

	buffer = new ConstantBuffer(&colorDesc, sizeof(ColorDesc));
}

Material::~Material()
{
	SAFE_DELETE(diffuseMap);
	SAFE_DELETE(specularMap);
	SAFE_DELETE(normalMap);

	SAFE_DELETE(buffer);
}

void Material::SetShader(Shader * shader)
{
	this->shader = shader;

	sBuffer = shader->AsConstantBuffer("CB_Material");

	sDiffuseMap = shader->AsSRV("DiffuseMap");
	sSpecularMap = shader->AsSRV("SpecularMap");
	sNormalMap = shader->AsSRV("NormalMap");
}

void Material::Ambient(D3DXCOLOR & color)
{
	colorDesc.Ambient = color;
}

void Material::Ambient(float r, float g, float b, float a)
{
	Ambient(D3DXCOLOR(r, g, b, a));
}

void Material::Diffuse(D3DXCOLOR & color)
{
	colorDesc.Diffuse = color;
}

void Material::Diffuse(float r, float g, float b, float a)
{
	Diffuse(D3DXCOLOR(r, g, b, a));
}

void Material::Specular(D3DXCOLOR & color)
{
	colorDesc.Specular = color;
}

void Material::Specular(float r, float g, float b, float a)
{
	Specular(D3DXCOLOR(r, g, b, a));
}

void Material::Shininess(float val)
{
	colorDesc.Shininess = val;
}

void Material::DiffuseMap(string file)
{
	DiffuseMap(String::ToWString(file));
}

void Material::DiffuseMap(wstring file)
{
	SAFE_DELETE(diffuseMap);

	diffuseMap = new Texture(file);
}

void Material::SpecularMap(string file)
{
	SpecularMap(String::ToWString(file));
}

void Material::SpecularMap(wstring file)
{
	SAFE_DELETE(specularMap);

	specularMap = new Texture(file);
}

void Material::NormalMap(string file)
{
	NormalMap(String::ToWString(file));
}

void Material::NormalMap(wstring file)
{
	SAFE_DELETE(normalMap);

	normalMap = new Texture(file);
}

void Material::Render()
{
	sBuffer->SetConstantBuffer(buffer->Buffer());

	if (diffuseMap != NULL)
		sDiffuseMap->SetResource(diffuseMap->SRV());

	if (specularMap != NULL)
		sSpecularMap->SetResource(specularMap->SRV());

	if (normalMap != NULL)
		sNormalMap->SetResource(normalMap->SRV());

}


//깊은복사
//복사생성자
//gof디자인패턴
//게임프로그래밍 패턴