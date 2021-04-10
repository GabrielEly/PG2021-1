#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../dependencies/Shader.h"

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Prot�tipos das fun��es
int setupGeometry();

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercicio 1", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Compilando e buildando o programa de shader
	Shader shader("../Shaders/transformations.vs", "../Shaders/transformations.fs");

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	GLuint VAO = setupGeometry();

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a vari�veis do tipo uniform em GLSL para armazenar esse tipo de info
	// que n�o est� nos buffers
	GLint colorLoc = glGetUniformLocation(shader.ID, "contourColor");
	assert(colorLoc > -1);
	glUseProgram(shader.ID);
	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f); //para cor de contorno

	// Para enviar o identificador de modo de desenho
	GLint rasterCodeLoc = glGetUniformLocation(shader.ID, "rasterCode");
	GLint modelCodeLoc = glGetUniformLocation(shader.ID, "modelCode");

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		//aqui recupera o tamanho atual da janela, para corre��o do aspect ratio mais tarde
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// 3 different model trasformations
		glm::mat4 model1 = glm::mat4(1);
		glm::mat4 model2 = glm::mat4(1);
		glm::mat4 model3 = glm::mat4(1);

		// Create transformations -- a first "camera" -- Orthographic Camera
		glm::mat4 ortho = glm::mat4(1);;

		// Matriz ortogr�fica - C�mera 2D
		ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

		// Passa suas informa��es efetivamente para o shader
		GLint modelLoc;
		GLint projLoc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));

		glLineWidth(5);
		glPointSize(10);

		glUniform1i(modelCodeLoc, 1);

		model1 = glm::translate(model1, glm::vec3(glfwGetTime() / 8, 0.0f, 0.0f));

		// Obtem seus identificadores de localiza��o no shader
		modelLoc = glGetUniformLocation(shader.ID, "model1");
		// Passa suas informa��es efetivamente para o shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));

		// Quadrante - top middle
		glViewport(width / 4, height / 2, width / 2, height / 2);
		// Chamada de desenho - drawcall
		// Poligono Preenchido - GL_TRIANGLES
		glUniform1i(rasterCodeLoc, 0); //zero � preenchido
		glUseProgram(shader.ID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Chamada de desenho - drawcall
		// Contorno do pol�gono - GL_LINE_LOOP
		glUniform1i(rasterCodeLoc, 1); //1 � contornado
		glDrawArrays(GL_LINE_LOOP, 0, 6);
		glBindVertexArray(0);

		glUniform1i(modelCodeLoc, 2);
		model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
		model2 = glm::rotate(model2, (GLfloat)-glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		// Obtem seus identificadores de localiza��o no shader
		modelLoc = glGetUniformLocation(shader.ID, "model2");
		// Passa suas informa��es efetivamente para o shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		// Quadrante - bottom right
		glViewport(width / 2, 0, width / 2, height / 2);
		glUniform1i(rasterCodeLoc, 0); //zero � preenchido
		glUseProgram(shader.ID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUniform1i(rasterCodeLoc, 1); //1 � contornado
		glDrawArrays(GL_LINE_LOOP, 0, 6);
		glBindVertexArray(0);

		glUniform1i(modelCodeLoc, 3);
		model3 = glm::scale(model3, glm::vec3(1.5f, 1.5f, 1.5f));
		model3 = glm::rotate(model3, (GLfloat)glfwGetTime(), glm::vec3(0.5f, 0.5f, 0.5f));
		// Obtem seus identificadores de localiza��o no shader
		modelLoc = glGetUniformLocation(shader.ID, "model3");
		// Passa suas informa��es efetivamente para o shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));

		// Quadrante - bottom left
		glViewport(0, 0, width / 2, height / 2);
		glUniform1i(rasterCodeLoc, 0); //zero � preenchido
		glUseProgram(shader.ID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUniform1i(rasterCodeLoc, 1); //1 � contornado
		glDrawArrays(GL_LINE_LOOP, 0, 6);
		glBindVertexArray(0);

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
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

int setupGeometry()
{
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f, 1.0, 0.0, 0.0, //Superior esquerdo
		0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, //Inferior esquerdo
	   -0.5f,  0.5f, 0.0f, 0.0, 0.0, 1.0, //Superior esquerdo


		0.5f, -0.5f, 0.0f, 1.0, 1.0, 0.0,
	   -0.5f, -0.5f, 0.0, 1.0, 0.0, 1.0,  //Inferior esquerdo
	   -0.5f,  0.5f, 0.0f, 0.0, 1.0, 1.0
	};

	GLuint VBO, VAO;

	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), ((GLvoid*)(3 * sizeof(GLfloat))));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}