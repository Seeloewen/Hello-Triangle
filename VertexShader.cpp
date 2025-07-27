#include "VertexShader.h"
#include "Util.h"
#include "d3d11.h"
#include "Shader.h"
#include "Application.h"

HRESULT VertexShader::create()
{
	//Try compiling the shader code
	ComPtr<ID3DBlob> shaderBlob = compile(fileName, "vs_5_0");
	if (shaderBlob == nullptr) return E_POINTER;

	//Try creating the vertex shader from the previously compiled shader code
	ComPtr<ID3D11VertexShader> vertexShader;
	if (FAILED(instance->device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&vertexShader)))
	{
		return E_FAIL;
	}

	this->shader = shader;
	return S_OK;
}

ComPtr<ID3D11VertexShader> VertexShader::get()
{
	//Convert back to specific shader type
	ComPtr<ID3D11VertexShader> vertexShader;
	shader.As(&vertexShader);

	return vertexShader;
}