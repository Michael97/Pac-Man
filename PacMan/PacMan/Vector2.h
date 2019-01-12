#ifndef __VECTOR2_H__
#define __VECTOR2_H__//\===========================================================================================================================================
//\ Filename: Vector2.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A custom Vector2 class.
//\===========================================================================================================================================
template <typename T>

class Vector2
{
public:
	Vector2() {};
	Vector2(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	T x;
	T y;

	//Operator overload to compare 2 Vector2's
	bool Vector2::operator!=(const Vector2& v) const 
	{ 
		return x != v.x || y != v.y; 
	}

	//Operator overload to compare 2 Vector2's
	bool Vector2::operator==(const Vector2& v) const 
	{ 
		return (*this != v) == false; 
	}

	//Operator overload to subtract a vector2 from another
	Vector2 Vector2::operator-(const Vector2& v) const 
	{ 
		return Vector2(x - v.x, y - v.y); 
	}
};

#endif // __VECTOR2_H__