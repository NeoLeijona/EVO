#include "Platform/Text.h"
#include "Platform/Viewport.h"
#include <incl/glm/gtc/type_ptr.hpp>
#include <incl/freetype-gl/shader.h>
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

Text::Text(const std::string& fontPath, const float fontSize)
	: m_fontSize(fontSize),
	  fr("string")
{
	m_path = "Assets/Fonts/" + fontPath;
	m_atlas = texture_atlas_new(1024, 1024, 1);
	shader = EVO_NEW Shader("Assets/Shaders/v3f-t2f-c4f.vert",
                         "Assets/Shaders/v3f-t2f-c4f.frag");

	buffer = vertex_buffer_new( "vertex:3f,tex_coord:2f,color:4f" );
	_type = OBJECT_TYPE::TEXT;

#ifdef __ANDROID__
	//std::string data = fr.loadFile(m_path);
	fr.loadFile(m_path);
	const int length = fr.length();
	unsigned char* fontBuffer = new unsigned char[length] /*malloc(length)*/;
	writeLog("fb length %d", length);
	fr.read(fr.length(), fontBuffer);
	font = texture_font_new_from_memory(m_atlas, m_fontSize, fontBuffer, length);
	writeLog("font size: %d", font->memory.size);
	if(font == NULL)
		writeLog("NULL PTR");
#else
	//std::string data = fr.loadFile(m_path);
	font = texture_font_new_from_file(m_atlas, m_fontSize, m_path.c_str());
	//font = texture_font_new_from_memory(m_atlas, m_fontSize, data.c_str(), data.length());
#endif
}

Text::~Text()
{
	texture_font_delete(font);
	texture_atlas_delete(m_atlas);
	delete shader;
}

void Text::addText(const std::wstring& text, const glm::vec4& color)
{
	writeLog("as %d", font->memory.size);
	glm::vec2 pos = m_lastPos;

	texture_font_load_glyphs(font, text.c_str());

    size_t i;
	float r = color.x, g = color.y, b = color.z, a = color.w;
	for( i=0; i<text.size(); ++i )
    {
        texture_glyph_t *glyph = nullptr;
		writeLog("null glyph");
		if (text.at(i) == L'\n')
			writeLog("NewLine");
		else
			writeLog("no NewLine");

		writeLog("fonttiongelma 1/2");
		glyph = texture_font_get_glyph(font, text.at(i));
		writeLog("fonttiongelma 1");


        if( glyph != nullptr )
        {
            int kerning = 0;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text[i-1] );
				writeLog("fonttiongelma 2");
            }
            pos.x += kerning;
            float x0  = ( pos.x + glyph->offset_x );
            float y0  = ( pos.y + glyph->offset_y );
            float x1  = ( x0 + glyph->width );
            float y1  = ( y0 - glyph->height );
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint indices[6] = {0,1,2, 0,2,3};
            vertex_t vertices[4] = { { x0,-y0,-1,  s0,t0,  r,g,b,a },
                                     { x0,-y1,-1,  s0,t1,  r,g,b,a },
                                     { x1,-y1,-1,  s1,t1,  r,g,b,a },
                                     { x1,-y0,-1,  s1,t0,  r,g,b,a } };
            vertex_buffer_push_back( buffer, vertices, 4, indices, 6 );
            pos.x += glyph->advance_x;
        }
    }
	m_lastPos = pos;
}

void Text::draw(glm::mat4 &projectionMatrix)
{
	glm::mat4 model		 =  getMatrix();
	glm::mat4 projection = projectionMatrix;
	glUseProgram(shader->program());

	glBindTexture( GL_TEXTURE_2D, m_atlas->id );

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glUniform1i( glGetUniformLocation( shader->program(), "texture" ),
                     0 );
	glUniformMatrix4fv( glGetUniformLocation( shader->program(), "model" ),
                            1, 0, glm::value_ptr(model));
	//glUniformMatrix4fv( glGetUniformLocation( shader, "view" ),
	//						1, 0, glm::value_ptr(view));
	glUniformMatrix4fv( glGetUniformLocation( shader->program(), "projection" ),
							1, 0, glm::value_ptr(projection));
	vertex_buffer_render( buffer, GL_TRIANGLES );
}

void Text::update(float dt)
{

}