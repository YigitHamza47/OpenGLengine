#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Window.h"
#include "Mesh.h"
#include "shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture PlainTexture;

Material shinyMaterial;
Material dullMaterial;
Material abazaparlak;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vShader = "Shaders/shader.vert";

static const char* fShader = "Shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
		   -1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};


	unsigned int floorIndices[] = {
		0,2,1,
		1,2,3
	};
	
	GLfloat floorVertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
		   -10.0f, 0.0f, -10.0f,      0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
			10.0f,	0.0f, -10.f,      10.f, 0.0f,	 0.0f, -1.0f, 0.0f,
		   -10.0f, 0.0f,   10.0f,     0.0f, 10.0f,   0.0f, -1.0f, 0.0f,
			10.0f, 0.0f,   10.0f,     10.0f, 10.0f,  0.0f, -1.0f, 0.0f,
	};


	unsigned int cubeIndices[] = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4,
	8, 9, 10, 10, 11, 8,
	12, 13, 14, 14, 15, 12,
	16, 17, 18, 18, 19, 16,
	20, 21, 22, 22, 23, 20
	};

	GLfloat cubeVertices[] = {
		// x      y      z      u     v     nx    ny    nz
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f
	};





	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj6);

	Mesh* objF = new Mesh();
	objF->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(objF);

	Mesh* objC = new Mesh();
	objC->CreateMesh(cubeVertices, cubeIndices, 192, 36);
	meshList.push_back(objC);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1920, 1200);
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture((char*)"Textures/brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture((char*)"Textures/dirt.png");
	dirtTexture.LoadTexture();
	PlainTexture = Texture((char*)"Textures/plain.png");
	PlainTexture.LoadTexture();

	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 4);
	abazaparlak = Material(12.0f,269);

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
								0.0f, 0.3f,
								0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
								0.0f, 1.0f,
								-2.0f, 0.0f, 0.0f,
								0.3f, 0.3f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(1.0f, 0.0f, 0.0f,
								0.0f, 1.0f,
								4.0f, 0.0f, 1.0f,
								0.3f, 0.1f, 0.1f);
	pointLightCount++;

	
	
	pointLights[2] = PointLight(0.1f, 0.8f, 1.0f,
								0.0f, 1.0f,
								-4.0f, 0.0f,-6.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;

	



	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, unifosrmEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.GetBuferrHeight(), 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;


		glfwPollEvents();

		camera.keyControl(mainWindow.getKesy(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		unifosrmEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);


		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(unifosrmEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0f);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 2.5f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.0f, 2.5f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, -2.5f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PlainTexture.UseTexture();
		abazaparlak.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PlainTexture.UseTexture();
		abazaparlak.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[7]->RenderMesh();
		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}