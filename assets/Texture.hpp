#pragma once

#include <string>
#include <stb_image.h>
#include "Asset.hpp"

enum class ClampType {
	REPEAT = GL_REPEAT,
	MIRROR_REPEAT = GL_MIRRORED_REPEAT,
	EDGE = GL_CLAMP_TO_EDGE,
	BORDER = GL_CLAMP_TO_BORDER,
};

enum class TexInterpolation {
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
};


class Texture : public Asset
{
public:
    Texture() = default;
    Texture(Texture &&) = default;
    Texture(const Texture &) = default;
    Texture &operator=(Texture &&) = default;
    Texture &operator=(const Texture &) = default;
	~Texture() {
		
		glDeleteTextures(1, &id);
	}
    
	unsigned int id;
    int width;
    int height;
	int nChannels;
	ClampType clamp = ClampType::REPEAT;
	TexInterpolation texInterpolation = TexInterpolation::LINEAR;
	
	float borderColor[4] = {1,1,1,1};
	unsigned int LoadTexture(const std::string path) {

		this->path = path;

		// Creates the texture on GPU
		glGenTextures(1, &id);
		// Loads the texture
		// Flips the texture when loads it because in opengl the texture coordinates are flipped
		stbi_set_flip_vertically_on_load(true);
		// Loads the texture file data
		unsigned char *data = stbi_load(path.data(), &width, &height, &nChannels, 0);
		if (data)
		{
			// Gets the texture channel format
			GLenum format;
			switch (nChannels)
			{
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			}

			// Binds the texture
			glBindTexture(GL_TEXTURE_2D, id);
			// Creates the texture
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			// Creates the texture mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);

			// Set the filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(clamp));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(clamp));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(texInterpolation));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(texInterpolation));

		}
		else
		{
			std::cout << "ERROR:: Unable to load texture " << path << std::endl;
			glDeleteTextures(1, &id);
		}
		// We dont need the data texture anymore because is loaded on the GPU
		stbi_image_free(data);
		std::cout << "texture loaded "<< path << std::endl;
		return id;
	}
private:

};
