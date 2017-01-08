#pragma once
#include <float.h>
class BiDirection
{
public:
	BiDirection(BiDirection& d) 
	{
		dir = d.dir;
	}
	BiDirection()
	{
		dir = Invalid;
	}
	static BiDirection MakeRight()
	{
		BiDirection d;
		d.SetRight();
		return d;
	}	  
	//can be used without makin instance of the class
	static BiDirection MakeLeft()
	{
		BiDirection d;
		d.SetLeft();
		return d;
	}

	bool IsRight() const
	{
		return dir == Right;
	}
	bool IsLeft() const
	{
		return dir == Left;
	}
	bool IsInValid() const
	{
		return dir == Invalid;
	}
	bool operator == (const BiDirection& rhs) const
	{
		return dir == rhs.dir;
	}
	bool operator != (const BiDirection& rhs) 
	{
		return dir != rhs.dir;
	}
	BiDirection& operator =(const BiDirection& rhs)
	{
		dir = rhs.dir;
		return *this;
	}
	void SetRight()
	{
		dir = Right;
	}
	void SetLeft()
	{
		dir = Left;
	}
	
	BiDirection GetOpposite() const
	{
		BiDirection o;
		if (IsRight())
		{
			o.SetLeft();
		}
		else if (IsLeft())
		{
			o.SetRight();
		}
		return o;
	}
	void Reverse()
	{
		if (IsRight())
		{
			SetLeft();
		}
		if (IsLeft())
		{
			SetRight();
		}
	}
	float Transform(float val) const
	{
		if (dir == Left)
		{
			return val * -1.0f;
		}
		else if (dir == Right)
		{
			return val;
		}
		else
		{
			return _FPCLASS_SNAN;
		}
	}
private:
	enum BiDir
	{
		Right,
		Left,
		Invalid
	}dir;
};