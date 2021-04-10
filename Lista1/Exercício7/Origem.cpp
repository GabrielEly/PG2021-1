#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Shader.h"
using namespace std;

#define M_PI 3.14159265358979323846264338327950288

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int *setupGeometry();
void drawCircle(GLint colorLoc, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat numberOfSides);

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exercicio 7", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	unsigned int *VAO = setupGeometry();
	// Compilando e buildando o programa de shader
	Shader shader("../Shaders/vertexSource.vs", "../Shaders/fragmentSource.fs");

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);
	glUseProgram(shader.ID);

	while (!glfwWindowShouldClose(window)) {
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		// Chamada de desenho - drawcall
		// Poligono Preenchido - GL_TRIANGLES
		glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
		glUseProgram(shader.ID);
		glBindVertexArray(VAO[0]);
		// Grama
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Céu
		glUniform4f(colorLoc, 0.0f, 0.2f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(int)));
		// Tronco
		glUniform4f(colorLoc, 0.28f, 0.21f, 0.11f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(int)));
		// Folhas
		glUniform4f(colorLoc, 0.13f, 0.37f, 0.04f, 1.0f);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(18 * sizeof(int)));
		// Cabeça
		glUniform4f(colorLoc, 0.79f, 0.53f, 0.41f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(int)));
		// Corpo
		glUniform4f(colorLoc, 0.0f, 0.6f, 0.66f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(36 * sizeof(int)));
		// Braços
		glUniform4f(colorLoc, 0.79f, 0.53f, 0.41f, 1.0f);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(42 * sizeof(int)));
		// Pernas
		glUniform4f(colorLoc, 0.27f, 0.25f, 0.66f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(int)));

		glLineWidth(5);

		// Contornos
		glBindVertexArray(VAO[1]);
		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINES, 0, 6);			// Grama
		glDrawArrays(GL_LINE_STRIP, 6, 4);		// Tronco
		glDrawArrays(GL_LINE_STRIP, 10, 6);		// Folhas
		glDrawArrays(GL_LINE_STRIP, 16, 4);		// Steve
		glDrawArrays(GL_LINE_LOOP, 20, 4);		// Steve

		// Sol
		glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
		drawCircle(colorLoc, 1.0f, 1.0f, 0.0f, 0.5f, 30);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

unsigned int *setupGeometry() {
	float squareVertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, -0.6f, 0.0f,		// Grama
		 1.0f, -0.6f, 0.0f,
		 1.0f, -1.0f, 0.0f,

		-0.8f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,		// Tronco
		-0.8f,  0.0f, 0.0f,
		-0.5f,  0.0f, 0.0f,

		-1.0f,  0.0f, 0.0f,
		-0.1f,  0.0f, 0.0f,		// Folhas
		-1.0f,  0.4f, 0.0f,
		-0.1f,  0.4f, 0.0f,
		-0.3f,  0.4f, 0.0f,
		-1.0f,  0.4f, 0.0f,
		-0.3f,  0.8f, 0.0f,
		-1.0f,  0.8f, 0.0f,

		-1.0f, -0.6f, 0.0f,
		-1.0f,  1.0f, 0.0f,		// Céu
		 1.0f,  1.0f, 0.0f,
		 1.0f, -0.6f, 0.0f,

		 0.6f, -0.1f, 0.0f,
		 0.8f, -0.1f, 0.0f,		// Cabeça
		 0.6f, -0.3f, 0.0f,
		 0.8f, -0.3f, 0.0f,

		 0.6f, -0.3f, 0.0f,
		 0.8f, -0.3f, 0.0f,		// Corpo
		 0.8f, -0.7f, 0.0f,
		 0.6f, -0.7f, 0.0f,

		 0.6f, -0.3f, 0.0f,
		 0.5f, -0.3f, 0.0f,		// Braços
		 0.6f, -0.7f, 0.0f,
		 0.5f, -0.7f, 0.0f,
		 0.8f, -0.3f, 0.0f,
		 0.9f, -0.3f, 0.0f,
		 0.8f, -0.7f, 0.0f,
		 0.9f, -0.7f, 0.0f,

		 0.6f, -0.7f, 0.0f,
		 0.8f, -0.7f, 0.0f,		// Pernas
		 0.8f, -1.0f, 0.0f,
		 0.6f, -1.0f, 0.0f,
	};

	int indices[] = {
		0, 1, 2,		// Grama
		0, 2, 3,

		16, 17, 18,		// Céu
		16, 18, 19,

		4, 5, 6,		// Tronco
		5, 6, 7,

		8, 9, 10,		// Folhas
		9, 10, 11,
		12, 13, 14,
		13, 14, 15,

		20, 21, 22,		// Cabeça
		21, 22, 23,

		24, 25, 26,		// Corpo
		24, 26, 27,

		28, 29, 30,		// Braços
		29, 30, 31,
		32, 33, 34,
		33, 34, 35,

		36, 37, 38,		// Pernas
		36, 38, 39
	};

	float lineVertices[] = {
		-1.0f, -0.6f, 0.0f,
		-0.8f, -0.6f, 0.0f,		// Grama
		-0.5f, -0.6f, 0.0f,
		 0.5f, -0.6f, 0.0f,
		 0.9f, -0.6f, 0.0f,
		 1.0f, -0.6f, 0.0f,

		-0.8f, -1.0f, 0.0f,
		-0.8f,  0.0f, 0.0f,		// Tronco
		-0.5f,  0.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,

		-1.0f,  0.0f, 0.0f,
		-0.1f,  0.0f, 0.0f,		// Folhas
		-0.1f,  0.4f, 0.0f,
		-0.3f,  0.4f, 0.0f,
		-0.3f,  0.8f, 0.0f,
		-1.0f,  0.8f, 0.0f,

		 0.6f, -1.0f, 0.0f,
		 0.6f, -0.1f, 0.0f,		// Steve
		 0.8f, -0.1f, 0.0f,
		 0.8f, -1.0f, 0.0f,

		 0.5f, -0.3f, 0.0f,
		 0.9f, -0.3f, 0.0f,		// Steve
		 0.9f, -0.7f, 0.0f,
		 0.5f, -0.7f, 0.0f
	};

	static unsigned int VAO[2];
	unsigned int VBO[2], EBO;
	glGenVertexArrays(1, &VAO[0]);
	glGenBuffers(1, &VBO[0]);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO[1]);
	glGenBuffers(1, &VBO[1]);
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

void drawCircle(GLint colorLoc, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat numberOfSides) {
	int numberOfVertices = numberOfSides + 2;

	GLfloat angle = 2.0f * M_PI / numberOfSides;

	GLfloat* allVertices = new GLfloat[(numberOfVertices) * 3];
	allVertices[0] = x;
	allVertices[1] = y;
	allVertices[2] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		allVertices[i * 3] = x + (radius * cos(i * angle));
		allVertices[(i * 3) + 1] = y + (radius * sin(i * angle));
		allVertices[(i * 3) + 2] = z;
	}

	GLuint VBOc, VAOc;
	glGenVertexArrays(1, &VAOc);
	glGenBuffers(1, &VBOc);

	glBindVertexArray(VAOc);
	glBindBuffer(GL_ARRAY_BUFFER, VBOc);
	glBufferData(GL_ARRAY_BUFFER, (numberOfSides + 2) * 3 * sizeof(GLfloat), allVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] allVertices;

	glBindBuffer(GL_ARRAY_BUFFER, VBOc);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOc);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfSides + 2);
	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_LINE_LOOP, 0, numberOfSides + 2);
}
