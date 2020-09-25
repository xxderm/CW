#pragma once
#ifndef BUFFER_OBJECT_HEADER
#define BUFFER_OBJECT_HEADER
#include "Buffer.h"
#include "RendererDecorator.h"

class BufferObject final : public RendererDecorator, public Buffer
{
public:
	BufferObject(Renderer* renderer);
	void Create() override;
	void Bind() override;
	void UnBind() override;
	void Set(
		void* vertices,
		void* texCoord,
		void* indices,
		GLuint draw_type,
		GLuint vert_size,
		GLuint texCoordSize,
		GLuint ind_size,
		int d = 3);
	void updateBuffer(GLuint id, GLuint offset, void* data, GLuint size);
	void Draw(GLuint type, GLsizei count);
	const unsigned getVaoID();
	~BufferObject();
private:
	unsigned mVboID[3];
	unsigned mVaoID;
};

#endif // !BUFFEROBJECT_HEADER
