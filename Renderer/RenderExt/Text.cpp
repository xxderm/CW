#include "Text.h"

void Text::Init(const char* font, glm::vec2 scrSize, GLuint fontSize)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	FT_Library ft;
	FT_Face face;
	if (FT_Init_FreeType(&ft))
		LOG(ERROR) << "ERROR::FREETYPE: Could not init FreeType Library";
	if (FT_New_Face(ft, font, 0, &face))
		LOG(ERROR) << "ERROR::FREETYPE: Failed to load font";
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (FT_ULong c = 0; c < 256; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			LOG(ERROR) << "ERROR::FREETYPE: Failed to load Glyph";
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		mCharacters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	mProgram = std::make_unique<Shader>("Shaders/FontVertex.glsl", "Shaders/FontFragment.glsl");
	mProgram->Bind();
	mObject = std::make_unique<BufferObject>();
	mObject->Set(sizeof(GLfloat) * 6 * 4, 4 * sizeof(GLfloat));
	mProgram->UnBind();
	proj = glm::ortho(0.0f, static_cast<GLfloat>(scrSize.x), 0.0f, static_cast<GLfloat>(scrSize.y));
}

void Text::RenderText(std::string text, int x, int y, float scale, glm::vec4 color)
{
	mProgram->Bind();
	mProgram->setVec4("textColor", color);
	mProgram->setMat4("transform", proj);
	glActiveTexture(GL_TEXTURE31);
	mProgram->setInt("text", 31);
	glBindVertexArray(mObject->VaoID);
	int stride = 0;
	register std::string::const_iterator c;
	int start = x;

	for (c = text.begin(); c != text.end(); ++c)
	{
		Character ch = mCharacters[*c];
		if (*c == '`')
		{
			x = start;
			y -= ((ch.Advance >> 6) + 15) * scale;
			stride = 0;
			continue;
		}
		
		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, mObject->VboID[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindTexture(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		float next = (ch.Advance >> 6) * scale;
		x += next;
		stride += next;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	mProgram->UnBind();
}

void Text::Resize(glm::vec2 scrSize)
{
	proj = glm::ortho(0.0f, static_cast<GLfloat>(scrSize.x), 0.0f, static_cast<GLfloat>(scrSize.y));
}
