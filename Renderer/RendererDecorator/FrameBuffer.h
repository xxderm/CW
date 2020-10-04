#pragma once
#ifndef FRAME_BUFFER_HEADER
#define FRAME_BUFFER_HEADER
#include "Buffer.h"

struct FrameBufferFormat
{
	std::string Name;
	int AttachmentId;
	glm::vec2 Scr;
	int TexActiveId = -1;
	bool Blend = 0;
};

class FrameBuffer : public Buffer
{
public:
	FrameBuffer();
	void Init() override;
	void setFbos(std::vector<FrameBufferFormat> Fbos);
	void Bind(const char* fboName) override;
	void UnBind(const char* fboName) override;
	void Set(const char* fboName, int attachment_id, glm::vec2 scr, int texActiveId = -1, bool blend = 0);
private:
	std::map<std::string, GLuint> mFboID;
	std::vector<FrameBufferFormat> mFbos;
	GLuint mTextureID;
	GLuint mRboID;
};

#endif // !FRAMEBUFFER_HEADER
