#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "IRenderer.h"
#include "../Reader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character 
{
	GLuint     TextureID; 
	glm::ivec2 Size;    
	glm::ivec2 Bearing; 
	GLuint     Advance; 
};

class GUIRenderer : public IRenderer
{
public:
	void Render() override;
	void Init() override;
	void Update() override;
	void setCamera(Camera* camera) override;
	void setMousePicker(MousePicker* mp) override; 
	void HandleEvent(SDL_Event* e) override;

private:
	glm::mat4 CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
private:
	std::unique_ptr<BufferObject> mQuad;
	std::unique_ptr<Shader> mProgram;
	std::unique_ptr<GUITexture> mGuis;
	
	std::map<GLchar, Character> mCharacters;
	Shader* fontProgram;
	BufferObject* fontObj;	
	GLuint VAO, VBO;
	
};

#endif // !GUIRENDERER_HEADER
