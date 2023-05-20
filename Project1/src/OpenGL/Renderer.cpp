#include <iostream>
#include "Renderer.h"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* functionName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "):"
			<< functionName << " at " << fileName << ": line "
			<< line << std::endl;
		return false;
	}
	return true;
}