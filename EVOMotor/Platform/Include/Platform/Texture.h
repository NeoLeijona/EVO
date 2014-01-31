#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Platform/Window.h"
#include "Platform/Shader.h"

struct tgaHeader
{
	GLubyte idLength;
	GLubyte colorMapType;
	GLubyte type;
	GLushort width;
	GLushort height;
	GLubyte depth;
	GLubyte descriptor;
};

class Texture
{
public:
	Texture(GLubyte* data,int width,int height,int depth);
	Texture(GLubyte* data);
	~Texture(void);

	void bind(Shader* shader);
	GLuint getTextureObject() const;

	static Texture* generateRandom(glm::vec2& size);
	static Texture* load(const std::string &fileName);
	static Texture* generateBlank();
	static Texture* blank;

	static GLubyte* loadTGA(const std::string& fileName, tgaHeader &header);
private:

	void init();

	GLubyte* _data;
	GLuint _textureID;

	int _width;
	int _height;
	int _depth;
};

#endif

