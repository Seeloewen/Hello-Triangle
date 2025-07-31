#include "VertexBuffer.h"
#include "PrimitiveRenderer.h"

VertexBuffer::VertexBuffer(InputLayout* inputLayout)
{
	this->inputLayout = inputLayout;

	//Create buffer info and vertex buffer
	D3D11_BUFFER_DESC bufferInfo = {};
	bufferInfo.ByteWidth = 1024;
	bufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	bufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//Create the buffer from info and resourcedata
	instance->renderer->device->CreateBuffer(
		&bufferInfo,
		nullptr,
		&buffer);
}

ID3D11Buffer* VertexBuffer::get()
{
	return buffer.Get();
}

void VertexBuffer::put(float x, float y, float r, float g, float b, float a)
{
	//If the buffer is not big enough, render
	if (1024 - (vertices.size() * sizeof(float)) < inputLayout->getSize())
	{
		instance->renderer->primitiveRenderer->render();
	}

	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(0.0f);
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
}

void VertexBuffer::use()
{
	//Create a new subresource for storing the vertex data and map it to the GPU
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	instance->renderer->deviceContext->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, vertices.data(), vertices.size() * sizeof(float));
	instance->renderer->deviceContext->Unmap(buffer.Get(), 0);

	//Set the input layout and buffer
	UINT stride = inputLayout->getSize();
	UINT offset = 0;
	instance->renderer->deviceContext->IASetInputLayout(inputLayout->get()); //Bind input layout
	instance->renderer->deviceContext->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset); //Bind buffer
}

void VertexBuffer::flush()
{
	//Draw the vertices and clear the buffer - make sure to bind buffer and shaders first
	UINT i = getVertAmount();
	instance->renderer->deviceContext->Draw(i, 0);
	vertices.clear();
}

UINT VertexBuffer::getVertAmount()
{
	return vertices.size() * sizeof(float) / inputLayout->getSize();
}