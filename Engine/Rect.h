/******************************************************************************************
*	Chili DirectX Framework Version 14.03.22											  *
*	Rect.h																				  *
*	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
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

#include "Vec2.h"

template < typename T >
class Rect
{
public:
	inline	Rect() {}
	inline	Rect( _Vec2< T > p0 , _Vec2< T > p1 )
	{
		top = std::min( p0.y, p1.y );
		bottom = std::max( p0.y, p1.y );
		right = std::max( p0.x, p1.x );
		left = std::min( p0.x, p1.x );
	}
	inline	Rect( T top,T bottom,T left,T right )
		:
	top( top ),
	bottom( bottom ),
	left( left ),
	right( right )
	{}
	inline	Rect( const Rect& rect )
		:
	top( rect.top ),
	bottom( rect.bottom ),
	left( rect.left ),
	right( rect.right )
	{}
	
	inline	void Translate( _Vec2< T > d )
	{
		Translate( d.x,d.y );
	}
	inline	void Translate( T dx,T dy )
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	
	inline	void ClipTo( const Rect& rect )
	{
		top = std::max( top,rect.top );
		bottom = std::min( bottom,rect.bottom );
		left = std::max( left,rect.left );
		right = std::min( right,rect.right );
	}
	inline T GetHeight() const
	{
		return bottom - top;
	}
	inline T GetWidth() const
	{
		return right - left;
	}
	inline bool Overlaps( const Rect& rect ) const
	{
				
		return(
			top		< rect.bottom&&
			bottom	> rect.top		&&
			left		< rect.right	&&
			right		> rect.left
			);
	}
	inline bool Contains( const _Vec2< T >& p )
	{
		return (
			p.y >= top &&
			p.y <= bottom &&
			p.x >= left &&
			p.x <= right
			);
	}

	template < typename T2 >
	inline	operator Rect< T2 >() const
	{
		return{ (T2)top,(T2)bottom,(T2)left,(T2)right };
	}
public:
	T top;
	T bottom;
	T left;
	T right;
};

typedef Rect< int > RectI;
typedef Rect< float > RectF;