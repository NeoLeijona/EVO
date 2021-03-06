#include "Platform/VertexData.h"
#include "Platform/debug.h"

VertexData::VertexData(std::vector<GLfloat> &data)
	: _data(data)
{
	init();
}

//VertexData::VertexData(std::vector<glm::vec3> &data)
//	: _data(data)
//{
//	for(int i = 0; i < data.size(); i++)
//	{
//		_data.push_back(data[i].x);
//		_data.push_back(data[i].y);
//		_data.push_back(data[i].z);
//	}
//	init();
//}
//
//VertexData::VertexData(std::vector<glm::vec2> &data)
//	: _data(data)
//{
//	for(int i = 0; i < data.size(); i++)
//	{
//		_data.push_back(data[i].x);
//		_data.push_back(data[i].y);
//	}
//
//	init();
//}

VertexData::~VertexData()
{

}

void VertexData::bindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	checkGLError("BindBuffer");
}

void VertexData::setAttribute(int location, int components, int stride, int offset)
{
	bindBuffers();

	glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	checkGLError("glVertexAttribPointer");

	glEnableVertexAttribArray(location);
	checkGLError("glEnableVertexAttribArray");

}

void VertexData::setData(int target,unsigned int offset, unsigned int size, void* data)
{
	bindBuffers();

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	checkGLError("glBufferSubData");

	glBindBuffer(GL_ARRAY_BUFFER,0);
	checkGLError("UnBindBuffer");
}

std::vector<GLfloat>& VertexData::getData()
{
	return _data;
}

void VertexData::init()
{
	glGenBuffers(1, &_vertexBufferObject);
	checkGLError("glGenerateBuffers");

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	checkGLError("glBindBuffer VBO");

	glBufferData(GL_ARRAY_BUFFER, _data.size()*sizeof(GLfloat),&_data[0], GL_DYNAMIC_DRAW);
	checkGLError("glBufferData");
}