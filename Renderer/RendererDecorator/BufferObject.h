#pragma once
#ifndef BUFFER_OBJECT_HEADER
#define BUFFER_OBJECT_HEADER
#include "Buffer.h"

struct BufferObjectFormat
{
	unsigned int VboID[3];
	unsigned int VaoID;
};

class BufferObject : public Buffer
{
public:
	BufferObject();
	void Init() override;
	void Bind(const char* fboName) override;
	void UnBind(const char* fboName) override;
	void setMesh(std::vector<Mesh>* mesh);
	void Set(
		const char* fboName,
		void* vertices,
		void* texCoord,
		void* indices,
		GLuint draw_type,
		GLuint vert_size,
		GLuint texCoordSize,
		GLuint ind_size,
		int d = 3);
	void Draw(const char* fboName, GLuint type, GLsizei count);
	const unsigned getVaoID(const char* fboName);
	~BufferObject();
private:
	std::map<std::string, BufferObjectFormat> mBufferObj;
	std::vector<Mesh>* mMesh = nullptr;
};

#endif // !BUFFEROBJECT_HEADER
