#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(InputLayout* inputLayout)
{
	this->inputLayout = inputLayout;
}

ID3D11Buffer* VertexBuffer::get()
{
	return buffer.Get();
}

void VertexBuffer::put(float x, float y, float r, float g, float b)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(0.0f);
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
}

void VertexBuffer::use()
{
	//Create buffer info and vertex buffer
	D3D11_BUFFER_DESC bufferInfo = {};
	bufferInfo.ByteWidth = vertices.size() * sizeof(float);
	bufferInfo.Usage = D3D11_USAGE_DEFAULT;
	bufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//Save the vertices as resource to mem
	D3D11_SUBRESOURCE_DATA resourceData = {};
	std::vector<float> verticesCopy = vertices; //Only set copy as data in memory so actual buffer can be flushed and filled with new data
	resourceData.pSysMem = verticesCopy.data();


	//Create the buffer from info and resourcedata
	instance->renderer->device->CreateBuffer(
		&bufferInfo,
		&resourceData,
		&buffer);

	UINT stride = inputLayout->getSize();
	UINT offset = 0;

	instance->renderer->deviceContext->IASetInputLayout(inputLayout->get()); //Bind input layout
	instance->renderer->deviceContext->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset); //Bind buffer
}

void VertexBuffer::flush()
{
	//Draw the vertices and clear the buffer
	UINT i = getVertAmount();
	instance->renderer->deviceContext->Draw(i, 0);
	vertices.clear();
}

UINT VertexBuffer::getVertAmount()
{
	return vertices.size() * sizeof(float) / inputLayout->getSize();
}