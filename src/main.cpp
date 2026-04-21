#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <core/Engine.h>
#include <renderer/Shader.h>
#include <core/stb_image.h>

using namespace std;

string vertexPath = string(SHADER_PATH) + "vertexShader.glsl";
string fragPath = string(SHADER_PATH) + "fragmentShader.glsl";
string fragPath2 = string(SHADER_PATH) + "fragmentShader2.glsl";

string containerTexturePath = string(TEXTURE_PATH) + "containerTexture.jpg";
string containerTexturePath2 = string(TEXTURE_PATH) + "awesomeface.png";

int main()
{
	stbi_set_flip_vertically_on_load(true);
	bool drawTriangle = false;
	float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};

	Engine engine("OpenGL", 800, 600);

	Shader shader(vertexPath.c_str(), fragPath.c_str());
	Shader shader2(vertexPath.c_str(), fragPath2.c_str());

	glewExperimental = GL_TRUE; // Indispensable pour le Core Profile
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Erreur lors de l'initialisation de GLEW" << std::endl;
		return -1;
	}

	// Make a VAO (Vertex Array Object)
	/*
	Le VAO agit comme un conteneur qui stocke la configuration des VBO, spécifiant comment interpréter ces données
	*/
	GLuint VAOs[1];
	glGenVertexArrays(1, VAOs);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAOs[0]);

	/////Rectangle using EBO

	GLfloat verticesForRectangle[] = {
		// Vertices			//Color				//Texture coord
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3	 // second triangle
	};

	/////Triangle

	GLfloat dataTriangle1[] = {
		// Vertices			//Color
		-0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

	GLfloat dataTriangle2[] = {
		0.1f, -0.5f, 0.f, 1.0f, 0.0f, 0.0f,
		0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.f, 0.0f, 0.0f, 1.0f};

	// Texture
	float texCoords[] = {
		0.0f, 0.0f, // lower-left corner
		1.0f, 0.0f, // lower-right corner
		0.5f, 1.0f	// top-center corner
	};

	GLuint texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Type de wrapping qu'on veut utiliser
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Type de Filtre qu'on veut utiliser pour les textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Type de paramètres de mipmap qu'on veut utiliser
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(containerTexturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Type de wrapping qu'on veut utiliser
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Type de Filtre qu'on veut utiliser pour les textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Type de paramètres de mipmap qu'on veut utiliser
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(containerTexturePath2.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	// Le VBO contient les données brutes (positions, couleurs, textures)
	GLuint VBOs[2];
	GLuint EBO;

	glGenBuffers(2, VBOs); // Copy the vertices to a buffer for the GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	if (drawTriangle)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(dataTriangle1), dataTriangle1, GL_STATIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesForRectangle), verticesForRectangle, GL_STATIC_DRAW);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	// Set the vertex attribute pointer so that the GPU knows what data it is
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	if (drawTriangle)
	{
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(dataTriangle2), dataTriangle2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	sf::Clock clock;
	sf::Clock clock2;
	float greenValue = (sin(clock2.getElapsedTime().asSeconds()) / 2.0f) + 0.5f;
	float smileyValue = 0.5f;
	unsigned int vertexColorLocation = glGetUniformLocation(shader2.GetID(), "multiplicator");

	// Use our shader
	shader.Use();
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);
	shader.SetFloat("smileyValue", smileyValue);

	while (engine.IsRunning())
	{
		sf::Time dt = clock.restart();
		greenValue = (sin(clock2.getElapsedTime().asSeconds() * 4.0f) / 2.0f) + 0.5f;
		smileyValue = (sin(clock2.getElapsedTime().asSeconds()) / 2.0f) + 0.5f;
		engine.ProcessEvents();

		engine.Clear(0.2f, 0.2f, 0.2f, 1.0f);

		glBindVertexArray(VAOs[0]);

		if (drawTriangle)
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);

			shader2.Use();
			glUniform4f(vertexColorLocation, greenValue, greenValue, greenValue, 1.0f);

			glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else
		{
			shader.Use();
			shader.SetFloat("smileyValue", smileyValue);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		// glBindVertexArray(0);

		engine.Display();
	}
}