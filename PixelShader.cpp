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
	if (FAILED(instance->renderer->device->CreatePixelShader(
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

void PixelShader::use()
{
	//Cast the shader to the correct type and bind it
	instance->renderer->deviceContext->PSSetShader(static_cast<ID3D11PixelShader*>(get()), nullptr, 0);
}