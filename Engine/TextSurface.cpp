#define FULL_WINTARD
#include "ChiliWin.h"
#include "TextSurface.h"
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <gdiplus.h>


TextSurface::TextSurface( unsigned int width,unsigned int height )
	:
	Surface( width,height ),
	pBmp( std::make_unique<Gdiplus::Bitmap>( width,height,INT( pitch * sizeof( Color ) ),
		PixelFormat32bppRGB,reinterpret_cast<byte*>( pBuffer.get() ) ) ),
	pGfx( std::make_unique<Gdiplus::Graphics>( pBmp.get() ) )
{
	pGfx->SetTextRenderingHint( Gdiplus::TextRenderingHintAntiAlias );
}

void TextSurface::DrawString( const std::wstring & string,const Vec2& pt,const Font & font,Color c )
{
	Gdiplus::Color textColor( c.GetR(),c.GetG(),c.GetB() );
	Gdiplus::SolidBrush textBrush( textColor );
	pGfx->DrawString( string.c_str(),-1,font,
		Gdiplus::PointF( pt.x,pt.y ),&textBrush );
}

void TextSurface::DrawString( const std::wstring & string,const RectF & rect,const Font & font,Color c,Alignment a )
{
	Gdiplus::StringFormat format;
	switch( a )
	{
	case Alignment::Left:
		format.SetAlignment( Gdiplus::StringAlignmentNear );
		break;
	case Alignment::Right:
		format.SetAlignment( Gdiplus::StringAlignmentFar );
		break;
	case Alignment::Center:
	default:
		format.SetAlignment( Gdiplus::StringAlignmentCenter );
		break;
	}
	Gdiplus::Color textColor( c.GetR(),c.GetG(),c.GetB() );
	Gdiplus::SolidBrush textBrush( textColor );
	pGfx->DrawString( string.c_str(),-1,font,
		Gdiplus::RectF( rect.left,rect.top,rect.GetWidth(),rect.GetHeight() ),
		&format,
		&textBrush );
}

TextSurface::~TextSurface()
{}

TextSurface::Font::Font( const std::wstring & family,float size,bool bold )
	:
	pFont( std::make_unique<Gdiplus::Font>( family.c_str(),size,
		bold ? Gdiplus::FontStyleBold : Gdiplus::FontStyleRegular ) )
{}

TextSurface::Font::operator const Gdiplus::Font*() const
{
	return pFont.get();
}

TextSurface::Font::~Font()
{}