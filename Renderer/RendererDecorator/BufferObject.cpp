#include "BufferObject.h"

BufferObject::BufferObject()
{
}

void BufferObject::Init()
{
	mBufferObj = std::map<std::string, BufferObjectFormat>();
	if(mMesh)
		for (auto& mesh : *mMesh)
		{
			mBufferObj.try_emplace(mesh.Name);
			glGenVertexArrays(1, &mBufferObj.at(mesh.Name).VaoID);
			Bind(mesh.Name.c_str());
			Set(mesh.Name.c_str(), mesh.Vertices.data(), mesh.TexCoord.data(), mesh.Indices.data(), mesh.DrawType, sizeof(glm::vec3) * mesh.Vertices.size(), sizeof(glm::vec2) * mesh.TexCoord.size(), sizeof(GLuint) * mesh.Indices.size());
		}
}

void BufferObject::Bind(const char* fboName)
{
	if(mBufferObj.count(fboName) > 0)
		glBindVertexArray(mBufferObj.at(fboName).VaoID);
}

void BufferObject::UnBind(const char* fboName)
{
	glBindVertexArray(0);
}

void BufferObject::setMesh(std::vector<Mesh>* mesh)
{
	mMesh = nullptr;
	mMesh = mesh;
}

void BufferObject::Set(const char* fboName, void* vertices, void* texCoord, void* indices, GLuint draw_type, GLuint vert_size, GLuint texCoordSize, GLuint ind_size, int d)
{
	glGenBuffers(3, mBufferObj.at(fboName).VboID);

	glBindBuffer(GL_ARRAY_BUFFER, mBufferObj.at(fboName).VboID[0]);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, draw_type);
	{
		glVertexAttribPointer(0, d, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mBufferObj.at(fboName).VboID[1]);
	glBufferData(GL_ARRAY_BUFFER, texCoordSize, texCoord, draw_type);
	{
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferObj.at(fboName).VboID[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, draw_type);
}

void BufferObject::Draw(const char* fboName, GLuint type, GLsizei count)
{
	Bind(fboName);
	//glDrawArrays(type, 0, count);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferObj.at(fboName).VboID[2]);
	glDrawElements(type, count, GL_UNSIGNED_INT, (void*)0);
	UnBind(fboName);
}

const unsigned BufferObject::getVaoID(const char* fboName)
{
	return mBufferObj.at(fboName).VaoID;
}

BufferObject::~BufferObject()
{
	for (auto& i : mBufferObj)
	{
		glDeleteBuffers(3, i.second.VboID);
		glDeleteVertexArrays(1, &i.second.VaoID);
	}
}
