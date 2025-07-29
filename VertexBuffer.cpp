#include "VertexBuffer.h"

PrimitiveVertexBuffer::PrimitiveVertexBuffer(InputLayout* inputLayout)
{
	this->inputLayout = inputLayout;
}

ID3D11Buffer* PrimitiveVertexBuffer::get()
{
	return buffer.Get();
}

void PrimitiveVertexBuffer::put(float x, float y, float r, float g, float b)
{
	vertices.push_back({ DirectX::XMFLOAT3{x, y, 0.0f}, DirectX::XMFLOAT3{r,g,b} });
}

void PrimitiveVertexBuffer::use()
{
	//Create buffer info and vertex buffer
	D3D11_BUFFER_DESC bufferInfo = {};
	bufferInfo.ByteWidth = vertices.size() * sizeof(PrimitiveVertexLayout);
	bufferInfo.Usage = D3D11_USAGE_DEFAULT;
	bufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//Save the vertices as resource to mem
	D3D11_SUBRESOURCE_DATA resourceData = {};
	//std::vector<PrimitiveVertexLayout> verticesCopy = vertices; //Only set copy as data in memory so actual buffer can be flushed and filled with new data
	resourceData.pSysMem = vertices.data();


	//Create the buffer from info and resourcedata
	instance->renderer->device->CreateBuffer(
		&bufferInfo,
		&resourceData,
		&buffer);

	UINT stride = sizeof(PrimitiveVertexLayout);
	UINT offset = 0;

	instance->renderer->deviceContext->IASetInputLayout(inputLayout->get()); //Bind input layout
	instance->renderer->deviceContext->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset); //Bind buffer

	//flush();
}

void PrimitiveVertexBuffer::flush()
{
	vertices.clear();
}