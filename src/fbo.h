#pragma once
#ifdef __APPLE__
# include <OPENGL/OpenGL.h>
# include <GLUT/Glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <GL/glew.h>
#endif

class FBO
{
public:
	FBO(GLenum, GLenum, GLuint);
	void updateFBO(GLenum, GLuint);
	void updateRBO(GLint, GLint);
	void bindFBO();
	void unbindFBO();
	void bindRBO();
	void unbindRBO();
	bool inline isActive()
	{
		return active;
	}

private:
	bool activeRBO;
	bool active;
	GLuint frameBufferID;
	GLuint renderBufferID;
	GLenum attachment;
	GLenum kind;
};