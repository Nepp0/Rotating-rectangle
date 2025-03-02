#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <cmath>

const uint SCR_WIDTH = 1280;
const uint SCR_HEIGHT = 960;

/*
void framebuffer_size_callback(GLFWwindow* window,int width, int height)
{
  glViewport(0,0,width, height);
}
*/
float mixVal = 0.2;
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window,true);
  }

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
  {
    mixVal += 0.005f;
    if (mixVal >= 1.0f)
      mixVal = 1.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    mixVal -= 0.005f;
    if (mixVal <= 0.0f)
      mixVal = 0.0f;
  }
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL", NULL, NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create window/n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD/n";
      return -1;
  }

Shader Shade("vertexSH.vs" , "fragSH.fs");

float vertices[] = {
   0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
  -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
  -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f 
};
unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

uint VBO, VAO, EBO;

//The VAO is a container that stores the configuration of vertex attributes and their associated buffer objects (VBOs).
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);

glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);

glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

//this copies the defined data into the bounded buffer
//first argument: type of buffer to copy data into. second:the size of the data to pass to buffer
//third: the data we want to send. fourth: how we want the graphics card to manage the given data
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//glVertexAttribPointer configures how vertex data is read from the buffer.
//3 = The attribute has 3 components (e.g., x, y, z for position).
//GL_FLOAT = Each component is a float.
//GL_FALSE = The data is not normalized.
//6 * = byte offset between consecutive vertices (each vertex is 24 bytes apart),
//3 * = The attribute starts after the first 3 floats (12 bytes) in each vertex.

//Position
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Color
glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

//Texture
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

uint texture1, texture2;
glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set the texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// load image, create texture and generate mipmaps
int width, height, nrChannels;
unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
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
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set the texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// load image, create texture and generate mipmaps
stbi_set_flip_vertically_on_load(true);
data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
  {
    std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

Shade.use();
glUniform1i(glGetUniformLocation(Shade.ID, "uniTexture1"),0);
Shade.setInt("uniTexture2",1);
  while (!glfwWindowShouldClose(window))
  {
    //input
    processInput(window);

    //clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //color changing
    double timeValue = glfwGetTime() * 2;
    float redValue = static_cast<float>(sin(timeValue) / 3.0);
    float greenValue = static_cast<float>(sin(timeValue + 2) / 3.0);
    float blueValue = static_cast<float>(sin(timeValue + 4) / 3.0);
    int vertexColorLocation = glGetUniformLocation(Shade.ID, "uniColor");
    glUniform4f(vertexColorLocation, redValue / 3, greenValue / 3, blueValue / 3, 1.0f);

    //position changing
    double posTime = glfwGetTime();
    float xPos = sin(posTime);
    int vertexPosLocation = glGetUniformLocation(Shade.ID, "uniPos");
    glUniform4f(vertexPosLocation, xPos / 2, 0.0f, 0.0f, 1.0);

    //opacity changing
    Shade.setFloat("opacity", mixVal);

    // Rotation
    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, glm::vec3(0.0f, 0.0f, 0.0f));
    translate = glm::rotate(translate, (float)glfwGetTime(), glm::vec3(0.0f, 0.9f, 1.0f));
    Shade.use();

    uint transformLoc = glGetUniformLocation(Shade.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translate));
    // container
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // smiley
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
 }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();
  return 0;
}
