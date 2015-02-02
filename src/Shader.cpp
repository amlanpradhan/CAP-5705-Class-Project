#include "Shader.h"
#include <iostream>
Shader::Shader(void)
{

}

Shader::~Shader(void)
{

}

char *Shader::shaderFileRead(const char *fn)
{
	if(fn==NULL)
		return NULL;

	FILE *file;
	file = fopen(fn, "rt");
	if(file == NULL)
	{
		fclose(file);
		return NULL;
	}

	char *fileContent = NULL;

	int charCount = 0;

	fseek(file, 0, SEEK_END);
	charCount = ftell(file);
	rewind(file);

	if(charCount>0)
	{
		fileContent = new char[charCount + 1];
		charCount = fread(fileContent, sizeof(char), charCount, file);
		fileContent[charCount] = '\0';
	}
	return fileContent;
}

void Shader::setShader(const char *vertexFile, const char *fragmentFile)
{
	char *vs, *fs;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	char tempVertFile[100]={0};
	char tempFragFile[100]={0};
	sprintf(tempVertFile, "%s.vert", vertexFile);
	sprintf(tempFragFile, "%s.frag", fragmentFile);

	vs = shaderFileRead(tempVertFile);
	fs = shaderFileRead(tempFragFile);

	const char *vv = vs;
	const char *ff = fs;
   
	glShaderSource(vertShader, 1, &vv, NULL);
	glShaderSource(fragShader, 1, &ff, NULL);
 
	delete vs; delete fs;

	glCompileShader(vertShader); glCompileShader(fragShader); 

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
}

void Shader::enable()
{
	glUseProgram(shaderProgram);
}

void Shader::disable()
{
	glUseProgram(0);
}

void Shader::setUniform(const GLchar *uniformName, GLint uniformVal)
{
	GLint location = glGetUniformLocation(shaderProgram, uniformName);
	glUniform1i(location, uniformVal);
}

void Shader::setUniform(const GLchar *uniformName, GLint uniformVal, GLfloat *x)
{
	GLint location = glGetUniformLocation(shaderProgram, uniformName);
	glUniform2fv(location, uniformVal, x);
}

void Shader::setAttribute(const GLchar *uniformName, GLfloat x, GLfloat y, GLfloat z)
{
	GLint location = glGetUniformLocation(shaderProgram, uniformName);
	glVertexAttrib3f(location, x, y, z);
}