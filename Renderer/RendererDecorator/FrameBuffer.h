#pragma once
#ifndef FRAME_BUFFER_HEADER
#define FRAME_BUFFER_HEADER
#include "Buffer.h"

class FrameBuffer final : public RendererDecorator, public Buffer
{
public:
	FrameBuffer(Renderer* renderer);
	void Create() override;
	void Bind() override;
	void UnBind() override;
	void Set(int attachment_id, glm::vec2 scr, int texActiveId = -1, bool blend = 0);
private:
	GLuint mFboID;
	GLuint mTextureID;
	GLuint mRboID;
};

#endif // !FRAMEBUFFER_HEADER
