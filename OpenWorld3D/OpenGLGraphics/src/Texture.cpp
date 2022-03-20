#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath):filepath(filepath),localBuffer(nullptr),width(0),height(0),bitsPerPixel(0)
{
	stbi_set_flip_vertically_on_load(true);
	localBuffer = stbi_load(filepath.c_str(),&width,&height,&bitsPerPixel,4);

	GLCall(glGenTextures(1, &rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // min filter to be resampled down
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // if we render texture area larger then texture pix size
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)); // horizontal wrap clamp to not extend to area
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)); // vertical wrap clamp to not extend to area

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer)); // check everything ( levels , format, data )

	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer) 
		stbi_image_free(localBuffer);
	
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &rendererID));
}

void Texture::Bind()const 
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void Texture::Unbind()const
{

}