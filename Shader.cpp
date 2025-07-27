#include <d3dcompiler.h>
#include <iostream>

#include "Util.h"
#include "Shader.h"
#include "Application.h"

Shader::Shader(const std::wstring fileName)
{
	this->fileName = fileName;
}

ComPtr<ID3DBlob> Shader::compile(const std::wstring fileName, const std::string profile)
{
	//Check if the device is initialized before starting any compilations
	if (instance->device == nullptr)
	{
		print("Could not begin shader compilation. Please make sure the shader engine was initialized with a D3D11Device.");
		return nullptr;
	}

	unsigned int compileFlags = D3DCOMPILE_ENABLE_STRICTNESS; //More strict compiling, not allowing legacy syntax
	ComPtr<ID3DBlob> shaderBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

	//Try compiling the shader from file
	if (FAILED(D3DCompileFromFile(
		fileName.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //Specifies how to handle includes in the shader
		"Main",
		profile.c_str(),
		compileFlags,
		0,
		&shaderBlob,
		&errorBlob)))
	{
		print("Could not compile shader from file");
		if (errorBlob != nullptr)
		{
			std::cout << static_cast<const char*>(errorBlob->GetBufferPointer()); //Read error message from shader error blob
		}
		return nullptr;
	}

	print("Compiled shader from file " + WStringToString(fileName));

	this->shaderBlob = shaderBlob; //blob blob blob
	return shaderBlob;
}