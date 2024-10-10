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

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"



const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
    
Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;


static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";



void CreateObject() {
    unsigned int indices[] = {
      0, 3, 1,
      1, 3, 2,
      2, 3, 0,
      0, 1, 2
    };
    GLfloat vertices[] = {
    //   x      y     z        u     v
        -1.0f, -1.0f, 0.0f,    0.0f, 0.0f,
         0.0f, -1.0f, 1.0f,    0.5f, 0.0f,
         1.0f, -1.0f, 0.0f,    1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,    0.5f, 1.0f
    };

    Mesh* obji = new Mesh();
    obji->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obji);

    Mesh* obji2 = new Mesh();
    obji2->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obji2);

     Mesh* obji3 = new Mesh();
    obji3->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obji3);

    Mesh* obji4 = new Mesh();
    obji4->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obji4);

    Mesh* obji5 = new Mesh();
    obji5->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obji5);

    Mesh* obji6 = new Mesh();
    obji6->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obji6);


    
}

void CreateShaders() {
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

}

int main() {

    mainWindow = Window(1920, 1200);
    mainWindow.Initialize();

    CreateObject();
    CreateShaders();

    camera = Camera(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f), -90.0f, 0.0f, 5.0f, 0.4f);

    brickTexture = Texture((char*)"Textures/brick.png");
    brickTexture.LoadTexture();
    dirtTexture = Texture((char*)"Textures/dirt.png");
    dirtTexture.LoadTexture();

    mainLight = Light(1.0f,1.0f,1.0f,1.0f);
    

    GLuint uniformModel = 0, uniformProjection = 0, unifornModel = 0,uniformView = 0, uniformAmbientIntensity =  0, uniformAmbientColour = 0;
    glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.GetBuferrHeight(), 0.1f, 100.0f);

    while (!mainWindow.getShouldClose()) {
		GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();

        camera.keyControl(mainWindow.getKesy(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModeLocation();
        uniformProjection = shaderList[0].GerProJectionlocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
        uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();

        mainLight.UseLight(uniformAmbientIntensity,uniformAmbientColour);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        dirtTexture.UseTexture();
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[1]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        
        meshList[2]->RenderMesh();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        brickTexture.UseTexture();
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[1]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[2]->RenderMesh();

        mainWindow.swapBuffers();
    }

    glfwTerminate();
    return 0;
}