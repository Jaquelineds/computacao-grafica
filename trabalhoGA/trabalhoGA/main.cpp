#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "SOIL2.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Shader.h"
#include "AssetManager.h"
#include "Time.h"
#include "OBJReader.h"
#include "Renderer.h"
#include "Time.h"

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed no init GLEW." << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_BLEND);	// Enables blending ( glBlendFunc )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Shader coreShader = Shader("Shaders/Core/core.vs", "Shaders/Core/core.fs");

	coreShader.Use();

	Mesh* testMesh = OBJReader::Read("mesa/mesa01.obj");
	testMesh->Bind();

	Renderer *render = new Renderer();
	render->AssociateMesh(testMesh, "Test");

	glm::mat4 model(1.0f);
	int modelLoc = coreShader.Uniform("model");
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view(1.0f);
	int viewLoc = coreShader.Uniform("view");
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

	glm::mat4 projection(1.0f);
	int projLoc = coreShader.Uniform("projection");
	projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

	float angle = 0.0f;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		if (glfwGetKey(window, 'A') == GLFW_PRESS) {
			view = glm::translate(view, glm::vec3(0.06f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, 'D') == GLFW_PRESS) {
			view = glm::translate(view, glm::vec3(-0.06f, 0.0f, 0.0f));
		}

		if (glfwGetKey(window, 'W') == GLFW_PRESS) {
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.06f));
		}
		if (glfwGetKey(window, 'S') == GLFW_PRESS) {
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.06f));
		}

		if (glfwGetKey(window, 'X') == GLFW_PRESS) {
			view = glm::translate(view, glm::vec3(0.0f, 0.06f, 0.0f));
		}
		if (glfwGetKey(window, 'Z') == GLFW_PRESS) {
			view = glm::translate(view, glm::vec3(0.0f, -0.06f, 0.0f));
		}

		if (glfwGetKey(window, 'Q') == GLFW_PRESS) {
			angle += 1.0f;
			view = glm::rotate(view, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (glfwGetKey(window, 'E') == GLFW_PRESS) {
			angle -= 1.0f;
			view = glm::rotate(view, glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coreShader.Use();

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		render->Render();

		glfwSwapBuffers(window);
	}

	coreShader.Delete();

	glfwTerminate();

	return 0;
}