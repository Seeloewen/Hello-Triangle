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
	ComPtr<ID3D11VertexShader> shader;
	HRESULT hr = instance->renderer->device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &shader);
	this->shader = shader;

	if (FAILED(hr)) return E_FAIL;
}

void VertexShader::use()
{
	//Cast the shader to the correct type and bind it
	instance->renderer->deviceContext->VSSetShader(static_cast<ID3D11VertexShader*>(get()), nullptr, 0);
}