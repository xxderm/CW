#include "BufferObject.h"

BufferObject::BufferObject()
{
	glGenVertexArrays(1, &VaoID);
	Bind();
}

void BufferObject::Bind()
{
	glBindVertexArray(VaoID);
}

void BufferObject::UnBind()
{
	glBindVertexArray(0);
}

void BufferObject::Set(void* vertices, void* texCoord, void* indices, GLuint draw_type, GLuint vert_size, GLuint texCoordSize, GLuint ind_size, int d, int ap)
{
	glGenBuffers(3, VboID);

	glBindBuffer(GL_ARRAY_BUFFER, VboID[0]);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, draw_type);
	{
		glVertexAttribPointer(0, d, GL_FLOAT, GL_FALSE, ap, (void*)0);
		glEnableVertexAttribArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VboID[1]);
	glBufferData(GL_ARRAY_BUFFER, texCoordSize, texCoord, draw_type);
	{
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, draw_type);
}

void BufferObject::Set(GLuint size, GLuint stride)
{
	glGenBuffers(1, &VboID[0]);
	glBindVertexArray(VaoID);
	glBindBuffer(GL_ARRAY_BUFFER, VboID[0]);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BufferObject::Update(void* vertices, GLuint size)
{
	glBindBuffer(GL_ARRAY_BUFFER, VboID[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::Draw(GLuint type, GLsizei count)
{
	Bind();
	//glDrawArrays(type, 0, count);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID[2]);	
	glDrawElements(type, count, GL_UNSIGNED_INT, (void*)0);
	UnBind();
	/*glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(0, 10, 0);
	glEnd();*/
}

const unsigned BufferObject::getVaoID()
{
	return VaoID;
}

BufferObject::~BufferObject()
{
	glDeleteBuffers(3, VboID);
	glDeleteVertexArrays(1, &VaoID);	
}
