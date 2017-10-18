/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"
#include "Bitmap.h"
#include "TextSurface.h"
#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )



class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel(Vec2I point, int r, int g, int b)
	{
		PutPixel(point.x, point.y, { unsigned char(r),unsigned char(g),unsigned char(b) });
	}
	void PutPixel(int x, int y, Color c);
	void PutPixel(Vec2I point, Color c)
	{
		PutPixel(point.x, point.y, c);
	void PutPixel(int x, int y, Color c);
	}
	void PutPixelAlpha(int x, int y, Color c);
	void PutPixelAlpha(Vec2I point, Color c);
	void PutPixelClipped(int x, int y, Color c, RectI clipRect)
	{
		if (y > clipRect.top &&
			y < clipRect.bottom &&
			x > clipRect.left &&
			x < clipRect.right)
			PutPixel(x, y, c);
	}
	void PutPixelClipped(Vec2I point, Color c,  RectI clipRect)
	{
		PutPixelClipped(point.x, point.y, c, clipRect);
	}
	void PutPixelAlphaClipped(int x, int y, Color c, RectI clipRect)
	{
		if (y > clipRect.top &&
			y < clipRect.bottom &&
			x > clipRect.left &&
			x < clipRect.right)
			PutPixelAlpha(x, y, c);
	}
	void PutPixelAlphaClipped(Vec2I point, Color c, RectI clipRect)
	{
		PutPixelAlphaClipped(point.x, point.y, c, clipRect);
	}

	//another functions
	void DrawLine(int x1, int y1, int x2, int y2, Color c);
	void DrawCircle(int cx, int cy, int radius, Color c);
	void DrawRect(const RectI rect, Color c);
	void DrawColoredRect(const RectI rect, Color c, int shrink = 1, bool fillEdges = false);
	void FillRect(const RectI rect, Color c, int shrink = 1, bool fillEdges = false);
	void DrawText(const std::wstring& string, const Vec2& pt, const TextSurface::Font& font, Color c)
	{
		sysBuffer.DrawString(string, pt, font, c);
	}
	void DrawText(const Text txt)
	{
		DrawText(txt.content, txt.pos,*(txt.font), txt.clr);
	}
	void DrawSprite(const Surface* sprite, Vec2I topLeftLocation);
	void DrawSpriteSubregion(const Surface* sprite, RectI regionToDraw, Vec2I drawLocation);
	//void DrawSpriteSubregionClipped(const Surface* sprite, RectI regionToDraw, Vec2I drawLocation, RectI clipRect);

	void DrawSpriteClipped(const Surface* sprite, Vec2I topLeftLocation, RectI clipRect);
	void DrawSpriteClipped(const Surface * sprite, Vec2I topLeftLocation);
	void DrawSpriteSubRegionClipped(const Surface * sprite, RectI subRegion, Vec2I topLeftLocation, RectI clipRect);
	void DrawSpriteSubRegionClipped(const Surface * sprite, RectI subRegion, Vec2I topLeftLocation);
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
	TextSurface                                         sysBuffer;
public:
	static constexpr unsigned int ScreenWidth = 680u;
	static constexpr unsigned int ScreenHeight = 680u - 4u;
};