//
// Created by 22584 on 2023/12/22.
//

#ifndef SANDSIMULATION_OPENGL_RENDERWINDOW_H
#define SANDSIMULATION_OPENGL_RENDERWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class RenderWindow {
public:
    static RenderWindow &getInstance() {
        static RenderWindow instance;
        return instance;
    }

private:
    RenderWindow() : window(nullptr), name("Program"), width(1600), height(900) {};

    GLFWwindow *window;
    std::string name;
    int width;
    int height;
    double cursorX{};
    double cursorY{};

public:
    inline void setSize(int _width, int _height) {
        width = _width;
        height = _height;
    }

    inline GLFWwindow *getWindow() { return window; }

    [[nodiscard]] inline int getWidth() const { return width; }

    [[nodiscard]] inline int getHeight() const { return height; }

    void initialize(const std::string &_name, int _width, int _height) {
        name = _name;
        setSize(_width, _height);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        gladLoadGL();
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        if (!window) {
            std::cout << "Failed to create the GLFW window\n";
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD\n";
            glfwTerminate();
        }
        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *_window, int _width, int _height) {
            glViewport(0, 0, _width, _height);
//        WINDOW_WIDTH = width;
//        WINDOW_HEIGHT = height;
        });
    }

    void cleanUp() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void handleEvent(Simulator &simulator) {
        glfwGetCursorPos(window, &cursorX, &cursorY);
        simulator.genParticleInCircle((int) cursorY / CELL_HEIGHT, (int) cursorX / CELL_WIDTH);
    }

    void showFPS() {
        static double prevTime = 0.0;
        static double curTime = 0.0;
        static double timeDiff = 0.0;
        static unsigned int counter = 0;

        curTime = glfwGetTime();
        timeDiff = curTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string newTitle = "SandSimulation_OpenGL - " + FPS;
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = curTime;
            counter = 0;
        }
    }

    RenderWindow(RenderWindow const &) = delete;

    void operator=(RenderWindow const &) = delete;


};


#endif //SANDSIMULATION_OPENGL_RENDERWINDOW_H
