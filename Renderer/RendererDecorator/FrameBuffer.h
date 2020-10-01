#pragma once
#ifndef FRAME_BUFFER_HEADER
#define FRAME_BUFFER_HEADER
#include "Buffer.h"

class FrameBuffer final : public RendererDecorator, public Buffer
{
public:
	FrameBuffer(std::unique_ptr<Renderer> renderer);
	void Init() override;
	void Render();
private:
	void Create(const char* fboName) override;
	void Bind(const char* fboName) override;
	void UnBind(const char* fboName) override;
	void Set(const char* fboName, int attachment_id, glm::vec2 scr, int texActiveId = -1, bool blend = 0);
private:
	std::map<std::string, GLuint> mFboID;
	GLuint mTextureID;
	GLuint mRboID;
};

#endif // !FRAMEBUFFER_HEADER
