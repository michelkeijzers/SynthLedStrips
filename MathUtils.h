// Mathtils.h

#pragma once

class MathUtils
{
public:
	static int Min(int a, int b) 
	{ 
		return a < b ? a : b; 
	}
	
	
	static int Min(int a, int b, int c) 
	{
		return Min(Min(a, b), c);
	}
	
	
	static int Max(int a, int b) 
	{
		return a > b ? a : b; 
	}
	
	
	static int Max(int a, int b, int c)
	{
		return Max(Max(a, b), c);
	}


private:
	MathUtils();
	~MathUtils();
};
