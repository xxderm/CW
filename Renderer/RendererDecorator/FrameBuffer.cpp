#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
}

void FrameBuffer::Init()
{
    for (auto& fbo : mFbos)
    {
        mFboID.try_emplace(fbo.Name);
	    glGenFramebuffers(1, &mFboID.at(fbo.Name));
        this->Bind(fbo.Name.c_str());
        this->Set(fbo.Name.c_str(), fbo.AttachmentId, fbo.Scr, fbo.TexActiveId, fbo.Blend);
    }
}

void FrameBuffer::setFbos(std::vector<FrameBufferFormat> Fbos)
{
    mFbos = Fbos;
}

void FrameBuffer::Bind(const char* fboName)
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFboID.at(fboName));
}

void FrameBuffer::UnBind(const char* fboName)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Set(const char* fboName, int attachment_id, glm::vec2 scr, int texActiveId, bool blend)
{
    this->Bind(fboName);
    if (texActiveId != -1)
        glActiveTexture(texActiveId);
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, scr.x, scr.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_WRAP_S), GL_CLAMP_TO_EDGE);
    glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_WRAP_T), GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glGenRenderbuffers(1, &mRboID);
    glBindRenderbuffer(GL_RENDERBUFFER, mRboID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, scr.x, scr.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRboID);
    glFramebufferTexture(GL_FRAMEBUFFER, attachment_id, mTextureID, 0);
    GLenum DrawBuffers[1] = { attachment_id };
    glDrawBuffers(1, DrawBuffers);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOG(ERROR) << "Frame buffer status not complete";
    this->UnBind(fboName);
}
