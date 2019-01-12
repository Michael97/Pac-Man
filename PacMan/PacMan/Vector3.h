#pragma once

template <typename T>

class Vector3
{
public:
	Vector3() {};
	Vector3(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	T x;
	T y;
	T z;
};

