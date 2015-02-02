#ifdef __APPLE__
# include <OPENGL/OpenGL.h>
# include <GLUT/Glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <GL/glew.h>
#endif

class Shader
{
public:
	Shader(void);
	~Shader(void);
	void setShader(const char *, const char *);
	void enable();
	void disable();
	void setUniform(const GLchar *uniformName, GLint uniformVal);
	void setUniform(const GLchar *uniformName, GLint uniformVal, GLfloat *x);
	void setAttribute(const GLchar *uniformName, GLfloat x, GLfloat y, GLfloat z);
	GLuint shaderProgram;

private:
	char *shaderFileRead(const char *fRead);
	GLuint vertShader;
	GLuint fragShader;
};
