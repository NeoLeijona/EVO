#ifndef INDEXDATA_H_
#define INDEXDATA_H_

#include <vector>

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <stdlib.h>
#include "Platform/Shader.h"




class IndexData

{
public:
	IndexData(std::vector<GLushort> &data);
	~IndexData();

	void bindBuffers();
	std::vector<GLushort>& getData();

private:

	IndexData(IndexData&);
	void init();
	
	GLuint _indexBuffer;
	std::vector<GLushort> _data;

	};


#endif