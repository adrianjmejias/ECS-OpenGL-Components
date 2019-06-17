#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"

#include <cstdio>



int main(int argc, char **argv)
{
    // .. setup the context
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()) {
        printf("Something went wrong!\n");
        return (-1);
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // .. render here ..

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}