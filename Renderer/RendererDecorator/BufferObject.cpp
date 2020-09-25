#include "BufferObject.h"

BufferObject::BufferObject(Renderer* renderer)
	: RendererDecorator(renderer)
{
}

void BufferObject::Create()
{
	glGenVertexArrays(1, &mVaoID);
	Bind();
}

void BufferObject::Bind()
{
	glBindVertexArray(mVaoID);
}

void BufferObject::UnBind()
{
	glBindVertexArray(0);
}

void BufferObject::Set(void* vertices, void* texCoord, void* indices, GLuint draw_type, GLuint vert_size, GLuint texCoordSize, GLuint ind_size, int d)
{
	glGenBuffers(3, mVboID);

	glBindBuffer(GL_ARRAY_BUFFER, mVboID[0]);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, draw_type);
	{
		glVertexAttribPointer(0, d, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mVboID[1]);
	glBufferData(GL_ARRAY_BUFFER, texCoordSize, texCoord, draw_type);
	{
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboID[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, draw_type);
}

void BufferObject::updateBuffer(GLuint id, GLuint offset, void* data, GLuint size)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVboID[id]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void BufferObject::Draw(GLuint type, GLsizei count)
{
	Bind();
	//glDrawArrays(type, 0, count);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboID[2]);
	glDrawElements(type, count, GL_UNSIGNED_INT, (void*)0);
	UnBind();
}

const unsigned BufferObject::getVaoID()
{
	return mVaoID;
}

BufferObject::~BufferObject()
{
	glDeleteBuffers(3, mVboID);
	glDeleteVertexArrays(1, &mVaoID);
}
