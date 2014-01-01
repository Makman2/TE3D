#pragma once




// Describes a 3 Dimensional Vector
struct TE3D_Vector3f{
	float x;
	float y;
	float z;
};

struct TE3D_Pixel{
	int r;
	int g;
	int b;

};




// Describes a color with red, green and blue components.
struct TE3D_Color
{
	// The red portion of the color.
	char R;
	// The green portion of the color.
	char G;
	// The blue portion of the color.
	char B;
}

// Describes a colorized char.
struct TE3D_ColorChar
{
	// The char.
	char Char;
	// The color of the char.
	TE3D_Color Color;
}

// Describes a surface of colorized chars.
struct TE3D_Surface
{
	// The colorized chars of the surface.
	TE3D_Color Pixels[];
	// The width and height of the surface.
	int Width;
	int Height;
	// The stride of the surface.
	int Stride;
}