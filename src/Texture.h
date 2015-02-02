#ifdef __APPLE__
# include <OPENGL/OpenGL.h>
# include <GLUT/Glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <GL/glew.h>
#endif

class Texture
{
public:
	Texture(void);
	~Texture(void);
	void init(GLenum tempFormat, GLint width, GLint height);
	void init(GLenum tempFormat, GLint width, GLint height, GLubyte *data);
	void init(GLenum tempFormat, GLint width, GLint height, GLint depth, GLubyte *data);
	GLuint inline getID()
	{
		return textureID;
	}
private:
	bool isActive;
	GLenum format;
	GLuint textureID;

};