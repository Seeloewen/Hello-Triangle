#include "InputLayout.h"
#include "Application.h"
#include "Shader.h"

void InputLayout::addInfoElement(const char* semanticName, DXGI_FORMAT format, size_t offset)
{
	//Create a new info element and add it to the list
	D3D11_INPUT_ELEMENT_DESC element = {};
	element.SemanticName = semanticName;
	element.SemanticIndex = 0;
	element.Format = format;
	element.InputSlot = 0;
	element.AlignedByteOffset = (UINT)offset;
	element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	element.InstanceDataStepRate = 0;

	inputLayoutInfo.push_back(element);
}

HRESULT InputLayout::create(Shader* shader)
{
	//Try creating the input layout from the (hopefully) previously supplied info
	if(FAILED(instance->renderer->device->CreateInputLayout(
		inputLayoutInfo.data(),
		2,
		shader->shaderBlob.Get()->GetBufferPointer(),
		shader->shaderBlob.Get()->GetBufferSize(),
		&inputLayout
	)))
	{
		print("Could not create Input Layout: " + HrToString(E_FAIL));
		return E_FAIL;
	}
	print("Created Input Layout");

	return S_OK;
}

ID3D11InputLayout* InputLayout::get()
{
	return inputLayout.Get();
}