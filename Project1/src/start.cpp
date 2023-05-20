#include <string>
#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Exception/Exception.h"
#include "LinearList/Linear.h"
#include "Matrix/Matrix.h"
#include "Stack/Stack.h"
#include "OpenGL/Renderer.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexArray.h"


LinearList<int>* create();
void size(LinearList<int>*);
void insert(LinearList<int>*);
void erase(LinearList<int>*);
void search(LinearList<int>*);
void Ping(); 
bool checkNull(LinearList<int>*);
void list(LinearList<int>*);
void trim(LinearList<int>*);
void capacity(LinearList<int>*);


void PrintMatchedPairs(std::string expr);

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

struct ColorRGBA
{
	float red;
	float green;
	float blue;
	float alpha;
};

static ShaderSource ParseShader(const std::string& filepath)
{
	enum ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int shader_type, const std::string& source)
{
	unsigned int shader_id = glCreateShader(shader_type);
	const char* src = source.c_str();
	glShaderSource(shader_id, 1, &src, nullptr);
	glCompileShader(shader_id);

	int result;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int log_length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
		char* message = (char*) alloca(sizeof(char) * log_length);
		glGetShaderInfoLog(shader_id, log_length, &log_length, message);


		std::cout << "Fail to compile " 
			<< (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " Shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(shader_id);
		return 0;
	}

	return shader_id;
}

static unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexshader = CompileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glValidateProgram(program);

	
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentShader);

	return program;

}

int main() {


#if 0



	Ping();
	LinearList<int>* linearlist = nullptr;
	int choice;
	std::cin >> choice;
	std::cout << " ------------------------- " << std::endl;
	
	while (choice != 0)
	{
		switch (choice) 
		{
		case 1:
			if (!linearlist)
			{
				linearlist = create();
			}
			break;
		case 2:
			if (!checkNull(linearlist))
			{
				size(linearlist);
			}
			break;
		case 3:
			if (!checkNull(linearlist))
			{
				insert(linearlist);
			}
			break;
		case 4:
			if (!checkNull(linearlist))
			{
				erase(linearlist);
			}
			break;
		case 5:
			if (!checkNull(linearlist))
			{
				search(linearlist);
			}
			break;
		case 6:
			if (!checkNull(linearlist))
			{
				list(linearlist);
			}
			break;
		case 7:
			if (!checkNull(linearlist))
			{
				trim(linearlist);
			}
			break;
		case 8:
			if (!checkNull(linearlist))
			{
				capacity(linearlist);
			}
		default:
			break;
		}

		Ping();
		std::cin >> choice;
		std::cout << " ------------------------- " << std::endl;
	}


#endif // 0


#if 0



	SparseMatrix<int> matrix = SparseMatrix<int>(3, 4);
	SparseMatrix<int> matrix2 = SparseMatrix<int>(3, 4);

	std::cout << "Please input the sparse matrix # :" << std::endl;
	std::string element;
	std::cin >> element;

	while (element != "#")
	{
		int row = 0, col = 0, value = 0;
		std::cout << "Please input the row number :" << std::endl;
		std::cin >> row;
		std::cout << "Please input the col number :" << std::endl;
		std::cin >> col;
		std::cout << "Please input the value of element :" << std::endl;
		std::cin >> value;

		try
		{
			matrix.set(row, col, value);
		}
		catch (MatrixIndexOutOgBounds e)
		{
			std::cout << "MatrixIndexOutOgBounds exception thrown" << std::endl;
			e.outputMessage();
			exit(-1);
		}
		catch (illegalParameterValue e)
		{
			std::cout << "illegalParamterValue exception thrown" << std::endl;
			e.outputMessage();
			exit(-1);
		}
		catch (illegalIndex e)
		{
			std::cout << "illegalIndex exception thrown" << std::endl;
			e.outputMessage();
			exit(-1);
		}
		
		std::cout << matrix << std::endl;
		std::cout << "Input $ for more input or # for exit" << std::endl;

		std::cin >> element;
	}

	std::cout << "Please input the sparse matrix # :" << std::endl;
	std::cin >> element;
	while (element != "#")
	{
		int row = 0, col = 0, value = 0;
		std::cout << "Please input the row number :" << std::endl;
		std::cin >> row;
		std::cout << "Please input the col number :" << std::endl;
		std::cin >> col;
		std::cout << "Please input the value of element :" << std::endl;
		std::cin >> value;

		try
		{
			matrix2.set(row, col, value);
		}
		catch (MatrixIndexOutOgBounds e)
		{
			std::cout << "MatrixIndexOutOgBounds exception thrown" << std::endl;
			e.outputMessage();
			exit(-1);
		}
		catch (illegalParameterValue e)
		{
			std::cout << "illegalParamterValue exception thrown" << std::endl;
			e.outputMessage();
			exit(-1);
		}
		catch (illegalIndex e)
		{
			std::cout << "illegalIndex exception thrown" << std::endl;
			e.outputMessage();
			exit(-1);
		}

		std::cout << matrix2 << std::endl;
		std::cout << "Input $ for more input or # for exit" << std::endl;

		std::cin >> element;
	}

	std::cout << "The matrix1 + matrix2 = " << std::endl;
	std::cout << matrix + matrix2 << std::endl;

#endif // 0

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "Maze", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error" << std::endl;
	}

	{
		float positions[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		VertexArray vao;
		VertexBuffer vBuffer(positions, sizeof(float) * 8);
		VertexBufferLayout layout;
		layout.Push<float>(2);

		vao.AddBuffer(vBuffer, layout);
		
		IndexBuffer iBuffer(indices, 6);

		ShaderSource source = ParseShader("res/Shader/Basic.shader");
		unsigned int program = CreateShader(source.vertexSource, source.fragmentSource);
		glUseProgram(program);

		int color_location = glGetUniformLocation(program, "u_Color");
		ColorRGBA color = { 0.5f, 0.4f, 0.2f, 1.0f };

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			glUniform4f(color_location, color.red, color.green, color.blue, color.alpha);

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			color.red += 0.05f;
			color.green += 0.03f;
			color.blue += 0.04f;

			if (color.red > 1.0f) color.red = 0.0f;
			if (color.green > 1.0f) color.green = 0.0f;
			if (color.blue > 1.0f) color.blue = 0.0f;



			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glDeleteProgram(program);
	}

	glfwTerminate();

	std::cout << "Program Ending" << std::endl;

}

void Ping() 
{
	std::cout << "Which function is your need : " << std::endl;
	std::cout << "1. Create an linearlist." << std::endl;
	std::cout << "2. Show size of the linearlist." << std::endl;
	std::cout << "3. Insert an element to the linearlist." << std::endl;
	std::cout << "4. Erase an element from the linearlist." << std::endl;
	std::cout << "5. Search the linearlist." << std::endl;
	std::cout << "6. List the linearlist." << std::endl;
	std::cout << "7. Trim the linearlist." << std::endl;
	std::cout << "8. Show capacity of the linearlist." << std::endl;
	std::cout << "End this program with code 0" << std::endl;
}

bool checkNull(LinearList<int>* list) {
	if (!list)
	{
		std::cout << "The ArrayList is Null " << std::endl;
	}
	return list == nullptr;
}

LinearList<int>* create()
{
	std::cout << "Choose mode of linearlist :" << std::endl;
	std::cout << "1. ArrayList(Array)" << std::endl;
	std::cout << "2. LinkedList(Chain)" << std::endl;
	int choice;
	std::cin >> choice;

	std::cout << "Please input the list ended with # :" << std::endl;
	std::string element;
	std::cin >> element;


	LinearList<int>* list = nullptr;
	switch (choice)
	{
	case 1:
		list = new ArrayList<int>();
		break;
	case 2:
		list = new Chain<int>();
		break;
	default:
		std::cout << "For more linearlist type " << std::endl;
		break;
	}
	int index = 0;
	while (element != "#")
	{
		if (list == nullptr)
		{
			exit(-1);
		}
		try
		{
			list->insert(index, std::atoi(element.c_str()));
		}
		catch (illegalParameterValue e)
		{
			std::cout << "illegalParamterValue exception thrown" << std::endl;
			e.outputMessage();
			exit(1);
		}
		catch (illegalIndex e)
		{
			std::cout << "illegalIndex exception thrown" << std::endl;
			e.outputMessage();
			exit(1);
		}

		++index;
		std::cin >> element;
	}

	std::cout << *list << std::endl;
	std::cout << " ------------------------- " << std::endl;
	return list;
}

void size(LinearList<int>* list)
{
	std::cout << "The current number of elements : " << list->size() << std::endl;
}

void capacity(LinearList<int>* list)
{
	std::cout << "The current capacity of arraylist : " << list->capacity() << std::endl;
}

void insert(LinearList<int>* list)
{
	std::cout << "Please input the index to insert : " << std::endl;
	int index;
	std::cin >> index;
	std::cout << " ------------------------- " << std::endl;

	std::cout << "Please input the element to insert : " << std::endl;
	int element;
	std::cin >> element;
	std::cout << " ------------------------- " << std::endl;

	list->insert(index, element);
	std::cout << *list << std::endl;
	std::cout << " ------------------------- " << std::endl;

}

void erase(LinearList<int>* list)
{
	std::cout << "Please input the index to erase : " << std::endl;
	int index;
	std::cin >> index;
	std::cout << " ------------------------- " << std::endl;

	list->erase(index);
	std::cout << *list << std::endl;
	std::cout << " ------------------------- " << std::endl;
}

void search(LinearList<int>* list)
{
	std::cout << "Which mode is your need : " << std::endl;
	std::cout << "1. Find the element by index." << std::endl;
	std::cout << "2. Find the first index by element value." << std::endl;
	int choice;
	std::cin >> choice;
	std::cout << " ------------------------- " << std::endl;
	
	std::string s;
	s.append("Please input the ").append(choice == 1 ? "index : " : "value : ");
	std::cout << s << std::endl;
	int input;
	std::cin >> input;
	std::cout << " ------------------------- " << std::endl;

	try
	{
		switch (choice)
		{
		case 1:
			std::cout << "The value of the index " << input << " is " << list->get(input) << std::endl;
			break;
		case 2:
			std::cout << "The first index of element value " << input << " is " << list->indexOf(input) << std::endl;
			break;
		default:
			throw undefinedSearchMethod();
			break;
		}
		std::cout << " ------------------------- " << std::endl;
	}
	catch (undefinedSearchMethod e)
	{
		std::cout << "Undefined Search Method Exception Thrown" << std::endl;
		e.outputMessage();
		exit(1);
	}
}

void trim(LinearList<int>* list)
{
	list->trimToSize();
	std::cout << "Current Capacity : " << list->capacity() << std::endl;
	std::cout << "Current Size : " << list->size() << std::endl;
	std::cout << " ------------------------- " << std::endl;
}

void list(LinearList<int>* list)
{
	std::cout << *list << std::endl;
	std::cout << " ------------------------- " << std::endl;
}