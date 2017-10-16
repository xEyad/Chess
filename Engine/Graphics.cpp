/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Graphics.h"
#include "DXErr.h"
#include "ChiliException.h"
#include <assert.h>
#include <string>
#include <array>
//#include <GdiPlus.h>
//#pragma comment( lib,"gdiplus.lib" )


// Ignore the intellisense error "cannot open source file" for .shh files.
// They will be created during the build sequence before the preprocessor runs.
namespace FramebufferShaders
{
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

using Microsoft::WRL::ComPtr;

Graphics::Graphics(HWNDKey& key)
	:
	sysBuffer(Graphics::ScreenWidth, Graphics::ScreenHeight)
{
	assert(key.hWnd != nullptr);

	//////////////////////////////////////////////////////
	// create device and swap chain/get render target view
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Graphics::ScreenWidth;
	sd.BufferDesc.Height = Graphics::ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL	featureLevelsRequested = D3D_FEATURE_LEVEL_9_1;
	UINT				numLevelsRequested = 1;
	D3D_FEATURE_LEVEL	featureLevelsSupported;
	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef _DEBUG
#ifdef USE_DIRECT3D_DEBUG_RUNTIME
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif

	// create device and front/back buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		&featureLevelsRequested,
		numLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		&featureLevelsSupported,
		&pImmediateContext)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating device and swap chain");
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Getting back buffer");
	}

	// create a view on backbuffer that we can render to
	if (FAILED(hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating render target view on backbuffer");
	}


	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);


	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float(Graphics::ScreenWidth);
	vp.Height = float(Graphics::ScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1, &vp);


	///////////////////////////////////////
	// create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = Graphics::ScreenWidth;
	sysTexDesc.Height = Graphics::ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;
	// create the texture
	if (FAILED(hr = pDevice->CreateTexture2D(&sysTexDesc, nullptr, &pSysBufferTexture)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sysbuffer texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if (FAILED(hr = pDevice->CreateShaderResourceView(pSysBufferTexture.Get(),
		&srvDesc, &pSysBufferTextureView)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating view on sysBuffer texture");
	}


	////////////////////////////////////////////////
	// create pixel shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating pixel shader");
	}


	/////////////////////////////////////////////////
	// create vertex shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex shader");
	}


	//////////////////////////////////////////////////////////////
	// create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FSQVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(hr = pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex buffer");
	}


	//////////////////////////////////////////
	// create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating input layout");
	}


	////////////////////////////////////////////////////
	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(hr = pDevice->CreateSamplerState(&sampDesc, &pSamplerState)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sampler state");
	}
}

Graphics::~Graphics()
{
	// clear the state of the device context before destruction
	if (pImmediateContext) pImmediateContext->ClearState();
}

void Graphics::EndFrame()
{
	HRESULT hr;

	// lock and map the adapter memory for copying over the sysbuffer
	if (FAILED(hr = pImmediateContext->Map(pSysBufferTexture.Get(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u, &mappedSysBufferTexture)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Mapping sysbuffer");
	}
	// setup parameters for copy operation
	BYTE* pDst = reinterpret_cast<BYTE*>(mappedSysBufferTexture.pData);
	const size_t dstPitch = mappedSysBufferTexture.RowPitch;
	const size_t srcPitch = Graphics::ScreenWidth;
	const size_t rowBytes = srcPitch * sizeof(Color);
	// perform the copy line-by-line
	sysBuffer.Present(dstPitch, pDst);
	// release the adapter memory
	pImmediateContext->Unmap(pSysBufferTexture.Get(), 0u);

	// render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout(pInputLayout.Get());
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(FSQVertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView.GetAddressOf());
	pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
	pImmediateContext->Draw(6u, 0u);

	// flip back/front buffers
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Presenting back buffer");
	}
}

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	sysBuffer.Clear(Colors::Black);
}

void Graphics::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	sysBuffer.PutPixel(x, y, c);
}

void Graphics::PutPixelAlpha(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	sysBuffer.PutPixelAlpha(x, y, c);
}

void Graphics::PutPixelAlpha(Vec2I point, Color c)
{
	PutPixelAlpha(point.x, point.y, c);
}

void Graphics::DrawLine(int x1, int y1, int x2, int y2, Color c)
{
	
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dy == 0 && dx == 0)
	{
		PutPixel(x1, y1,c);
	}
	else if (abs(dy) > abs(dx))
	{
		if (dy < 0)
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dx / (float)dy;
		float b = x1 - m*y1;
		for (int y = y1; y <= y2; y = y + 1)
		{
			int x = (int)(m*y + b + 0.5f);
			PutPixel(x, y,c);
		}
	}
	else
	{
		if (dx < 0)
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dy / (float)dx;
		float b = y1 - m*x1;
		for (int x = x1; x <= x2; x = x + 1)
		{
			int y = (int)(m*x + b + 0.5f);
			PutPixel(x, y,c);
		}
	}
}

void Graphics::DrawCircle(int centerX, int centerY, int radius, Color c)
{
	int rSquared = radius*radius;
	int xPivot = (int)(radius * 0.707107f + 0.5f);
	for (int x = 0; x <= xPivot; x++)
	{
		int y = (int)(sqrt((float)(rSquared - x*x)) + 0.5f);
		PutPixel(centerX + x, centerY + y, c);
		PutPixel(centerX - x, centerY + y, c);
		PutPixel(centerX + x, centerY - y, c);
		PutPixel(centerX - x, centerY - y, c);
		PutPixel(centerX + y, centerY + x, c);
		PutPixel(centerX - y, centerY + x, c);
		PutPixel(centerX + y, centerY - x, c);
		PutPixel(centerX - y, centerY - x, c);
	}
}

void Graphics::DrawRect(const RectI rect, Color c) 
{
	DrawLine(rect.left, rect.top, rect.right, rect.top, c);
	DrawLine(rect.right, rect.top, rect.right, rect.bottom, c);
	DrawLine(rect.right, rect.bottom, rect.left, rect.bottom, c);
	DrawLine(rect.left, rect.bottom, rect.left, rect.top,c);
}

void Graphics::DrawColoredRect(const RectI rect, Color c, int shrink, bool fillEdges)
{
	DrawRect(rect, c);
	FillRect(rect, c, shrink, fillEdges);
}

void Graphics::FillRect(const RectI rect, Color c ,int shrink, bool fillEdges)
{
	int top_left = shrink;
	int bot_right = 0;
	if (fillEdges)
	{
		top_left = 0;
		bot_right = shrink;
	}
	for (int x = rect.left + top_left; x < rect.right + bot_right; x++)
	{
		for (int y = rect.top + top_left; y < rect.bottom + bot_right; y++)
		{
			PutPixel(x, y, c);
		}
	}
}

void Graphics::DrawSprite(const Surface * sprite, Vec2I topLeftLocation)
{
	RectI regionToDraw(0, sprite->GetHeight(),0, sprite->GetWidth() );
	DrawSpriteSubregion(sprite, regionToDraw, topLeftLocation);	
}

void Graphics::DrawSpriteSubregion(const Surface * sprite, RectI subRegion, Vec2I drawLocation)
{
	for (int sy = subRegion.top; sy < subRegion.bottom; sy++)
	{
		for (int sx = subRegion.left; sx < subRegion.right; sx++)
		{
			PutPixelAlpha(drawLocation.x+ sx -subRegion.left, drawLocation.y + sy - subRegion.top, sprite->GetPixel(sx, sy));
		}		
	}
}

void Graphics::DrawSpriteClipped(const Surface * sprite, Vec2I topLeftLocation, RectI clipRect)
{
	RectI sprREC(topLeftLocation.y, topLeftLocation.y + sprite->GetHeight(), topLeftLocation.x, topLeftLocation.x + sprite->GetWidth());
	int startX = topLeftLocation.x;
	int shiftY = 0;
	int shiftX = 0;
	int sprStartX = 0;
	int sprStartY = 0;
	int sprEndX = sprite->GetWidth();
	int sprEndY = sprite->GetHeight();
	if (sprREC.top < clipRect.top)
	{
		shiftY = clipRect.top - sprREC.top;
		sprStartY = shiftY;
	}

	if (sprREC.bottom > clipRect.bottom)
		sprEndY = sprite->GetHeight() - (sprREC.bottom - clipRect.bottom);


	if (sprREC.left < clipRect.left)
	{
		shiftX = clipRect.left - sprREC.left;
		sprStartX = shiftX;
	}

	if (sprREC.right > clipRect.right)
		sprEndX = sprite->GetWidth() - (sprREC.right - clipRect.right);
	//its shifted from the right, meaning we will end drawing earlier by this much (shift), but won't start drawing shifted!


	for (int sy = sprStartY; sy < sprEndY; sy++)
	{
		for (int sx = sprStartX; sx < sprEndX; sx++)
		{
			PutPixelAlpha(topLeftLocation.x++ + shiftX, topLeftLocation.y + shiftY, sprite->GetPixel(sx, sy));
		}
		topLeftLocation.x = startX;
		topLeftLocation.y++;
	}
}

void Graphics::DrawSpriteClipped(const Surface * sprite, Vec2I topLeftLocation)
{
	RectI clipRect(0, ScreenHeight, 0, ScreenWidth);
	DrawSpriteClipped(sprite, topLeftLocation, clipRect);
}

void Graphics::DrawSpriteSubRegionClipped(const Surface * sprite, RectI subRegion, Vec2I topLeftLocation, RectI clipRect)
{
	int subRegionWidth = subRegion.right - subRegion.left;
	int subRegionHeight = subRegion.bottom - subRegion.top;
	RectI sprREC(topLeftLocation.y, topLeftLocation.y + subRegionHeight, topLeftLocation.x, topLeftLocation.x + subRegionWidth);
	int startX = topLeftLocation.x;
	int shiftY = 0;
	int shiftX = 0;
	int sprStartX = subRegion.left;
	int sprStartY = subRegion.top;
	int sprEndX = subRegion.right;
	int sprEndY = subRegion.bottom;
	if (sprREC.top < clipRect.top)
	{
		shiftY = clipRect.top - sprREC.top;
		sprStartY = subRegion.top + shiftY;
	}

	if (sprREC.bottom > clipRect.bottom)
	{
		sprEndY = subRegion.bottom - (sprREC.bottom - clipRect.bottom);
	}


	if (sprREC.left < clipRect.left)
	{
		shiftX = clipRect.left - sprREC.left;
		sprStartX = subRegion.left + shiftX;
	}

	if (sprREC.right > clipRect.right)
	{
		sprEndX = subRegion.right - (sprREC.right - clipRect.right);
		//its shifted from the right, meaning we will end drawing earlier by this much (shift), but won't start drawing shifted!
	}


	for (int sy = sprStartY; sy < sprEndY; sy++)
	{
		for (int sx = sprStartX; sx < sprEndX; sx++)
		{
			PutPixelAlpha(topLeftLocation.x++ + shiftX, topLeftLocation.y + shiftY, sprite->GetPixel(sx, sy));
		}
		topLeftLocation.x = startX;
		topLeftLocation.y++;
	}
}

void Graphics::DrawSpriteSubRegionClipped(const Surface * sprite, RectI subRegion, Vec2I topLeftLocation)
{
	RectI clipRect(0, ScreenHeight, 0, ScreenWidth);
	DrawSpriteSubRegionClipped(sprite, subRegion, topLeftLocation, clipRect);
}
Graphics::Exception::Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line )
	:
	ChiliException( file,line,note ),
	hr( hr )
{}

std::wstring Graphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring( L"Error: " ) + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring( L"Description: " ) + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring( L"Note: " ) + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring( L"Location: " ) + location
			: empty);
}

std::wstring Graphics::Exception::GetErrorName() const
{
	return DXGetErrorString( hr );
}

std::wstring Graphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t,512> wideDescription;
	DXGetErrorDescription( hr,wideDescription.data(),wideDescription.size() );
	return wideDescription.data();
}

std::wstring Graphics::Exception::GetExceptionType() const
{
	return L"Chili Graphics Exception";
}