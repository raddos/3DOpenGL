#pragma once

#include "Renderer.h"

class Texture 
{
private:
	unsigned int rendererID;
	std::string filepath;
	unsigned char* localBuffer;
	int width;
	int height;
	int bitsPerPixel;
public:
	Texture(const std::string& filepath);
	~Texture();

	void BindTextureSlot()const;
	
	void Unbind()const; 


	inline int GetWidth()const { return width; };
	inline int GetHeight()const { return height; };

	inline void SetWidth(int width) { this->width=width; };
	inline void SetHidth(int hidth) { this->height = height; };
};