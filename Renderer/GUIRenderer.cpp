#include "GUIRenderer.h"

void GUIRenderer::Render()
{		
	mProgram->Bind();
	for (auto& gui : mGuis->getGui())
	{
		if (gui->Visible)
		{
			mProgram->setMat4("transformationMatrix",
				CreateTransformationMatrix(gui->Position, gui->Scale));
			mProgram->setInt("guiTexture", gui->TextureId);
			mProgram->setVec4("guiColor", gui->Color);
			if (gui->TextureId == -1)
				mProgram->setBool("TextureMode", 0);
			else
				mProgram->setBool("TextureMode", 1);
			mQuad->Draw(GL_TRIANGLE_STRIP, 8);
		}
	}
	mProgram->UnBind();	


	static float r = 1, g = 0 , b = 0;
	fontProgram->Bind();
	fontProgram->setVec3("textColor", glm::vec3(r, g, b));
	glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(1280), 0.0f, static_cast<GLfloat>(720));
	fontProgram->setMat4("projection", proj);
	glActiveTexture(GL_TEXTURE18);
	fontProgram->setInt("text", 18);
	glBindVertexArray(VAO);	
	

	std::string text = 
		"123123123123123123123123123123123123123123\n"
		"hjkl\n"
		;
	register std::string::const_iterator c;
	int x = 200, y = 300;
	int scale = 1;
	int tmp = 0;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = mCharacters[*c];
		if (*c == '\n')
		{
			x -= tmp;
			y -= ((ch.Advance >> 6) + 15) * scale;
			tmp = 0;
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
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindTexture(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		auto next = (ch.Advance >> 6) * scale;
		x += next;		
		tmp += next;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	fontProgram->UnBind();
}

void GUIRenderer::Init()
{
	mProgram = std::make_unique<Shader>("Shaders/GUIVertex.glsl", "Shaders/GUIFragment.glsl");
	mProgram->Bind();
	mQuad = std::make_unique<BufferObject>();
	float Vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };
	int Indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	mQuad->Set(Vertices, nullptr, Indices, GL_STATIC_DRAW, 4 * 8, 0, 4 * 8, 2);
	mQuad->UnBind();
	mProgram->UnBind();

	mGuis = std::make_unique<GUITexture>();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	FT_Library ft;
	FT_Face face;
	if (FT_Init_FreeType(&ft))
		LOG(ERROR) << "ERROR::FREETYPE: Could not init FreeType Library";
	if (FT_New_Face(ft, "Resources/font/17541.ttf", 0, &face))
		LOG(ERROR) << "ERROR::FREETYPE: Failed to load font";
	FT_Set_Pixel_Sizes(face, 0, 24);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 255; c++)
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
	fontProgram = new Shader("Shaders/FontVertex.glsl", "Shaders/FontFragment.glsl");
	fontProgram->Bind();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	fontProgram->UnBind();
}

void GUIRenderer::Update()
{
	Reader::getInstance()->getUI(mGuis.get(), "Resources/UI/Main.ui");
}

void GUIRenderer::setCamera(Camera* camera)
{
}

void GUIRenderer::setMousePicker(MousePicker* mp)
{
}

void GUIRenderer::HandleEvent(SDL_Event* e)
{
}

glm::mat4 GUIRenderer::CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix =
		glm::identity<glm::mat4>();
	matrix *= glm::translate(glm::vec3(translation.x, translation.y, 0));
	matrix *= glm::scale(glm::vec3(scale.x, scale.y, 1.f));
	return matrix;
}
