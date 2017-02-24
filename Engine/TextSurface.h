#pragma once

#include "Surface.h"
#include <memory>

namespace Gdiplus
{
	class Font;
	class Bitmap;
	class Graphics;
}

class TextSurface : public Surface
{
public:
	enum class Alignment
	{
		Left,
		Right,
		Center
	};
	class Font
	{
		friend TextSurface;
	public:
		Font( const std::wstring& family,float size,bool bold = true );
		~Font();
	private:
		operator const Gdiplus::Font*() const;
	private:
		std::unique_ptr<Gdiplus::Font> pFont;
	};
public:
	TextSurface( unsigned int width,unsigned int height );
	void DrawString( const std::wstring& string,const Vec2& pt,const Font& font,Color c );
	void DrawString( const std::wstring& string,const RectF& rect,const Font& font,
		Color c = Colors::White,Alignment a = Alignment::Center );
	~TextSurface();
	TextSurface( const TextSurface& ) = delete;
	TextSurface( TextSurface&& ) = delete;
	TextSurface& operator=( const TextSurface& ) = delete;
	TextSurface& operator=( TextSurface&& ) = delete;
private:
	std::unique_ptr<Gdiplus::Bitmap>	pBmp;
	std::unique_ptr<Gdiplus::Graphics>	pGfx;
};