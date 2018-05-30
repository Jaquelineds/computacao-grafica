#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

unsigned char* Texture::LoadImage(char* path) {
	int width, height;
	unsigned char *image;

	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return nullptr;
}


void Texture::Load(char* path, char* textureUniformName, GLuint shaderProgram, GLint textureNum)
{
	this->textureNum = textureNum;

	glGenTextures(1, &textureID);

	int width, height;
	unsigned char *image;

	textureLocation = glGetUniformLocation(shaderProgram, textureUniformName);

	glActiveTexture(GL_TEXTURE0 + this->textureNum);
	glBindTexture(GL_TEXTURE_2D, textureID);

	LoadImage(path);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //test GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUniform1i(textureLocation, this->textureNum);

	glBindTexture(GL_TEXTURE_2D, 0);

}
