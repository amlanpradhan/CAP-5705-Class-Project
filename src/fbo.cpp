#include "fbo.h"
#include <iostream>

FBO::FBO(GLenum tempAttachment, GLenum tempKind, GLuint textureID)
{
	activeRBO = false;
	attachment = tempAttachment;
	kind = tempKind;

	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, kind, textureID, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::updateFBO(GLenum tempAttachment, GLuint textureID)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, tempAttachment, kind, textureID, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::updateRBO(GLint width, GLint height)
{
	glGenRenderbuffers(1, &renderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_RENDERBUFFER, renderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	activeRBO = true;
}

void FBO::bindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}

void FBO::unbindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::bindRBO()
{
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
}

void FBO::unbindRBO()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}




