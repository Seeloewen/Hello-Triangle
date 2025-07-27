#include "PixelShader.h"
#include "Util.h"
#include "d3d11.h"
#include "Shader.h"
#include "Application.h"

HRESULT PixelShader::create()
{
	//Try compiling the shader code
	ComPtr<ID3DBlob> shaderBlob = compile(fileName, "ps_5_0");
	if (shaderBlob == nullptr) return E_POINTER;

	//Try creating the vertex shader from the previously compiled shader code
	ComPtr<ID3D11PixelShader> shader;
	if (FAILED(instance->device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&shader)))
	{
		return E_FAIL;
	}

	this->shader = shader;
	return S_OK;
}

ComPtr<ID3D11PixelShader> PixelShader::get()
{
	//Convert back to specific shader type
	ComPtr<ID3D11PixelShader> convShader;
	shader.As(&convShader);

	return convShader;
}