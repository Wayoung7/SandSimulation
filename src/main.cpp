#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stb_image.h>
#include <iostream>

#include "Shader.h"
#include "shape.h"
#include "Simulator.h"
#include "RenderWindow.h"

int main(int argc, char **argv) {
    RenderWindow::getInstance().initialize("SandSimulation_OpenGL", 1920, 1080);
    GLFWwindow *window = RenderWindow::getInstance().getWindow();
    int windowWidth = RenderWindow::getInstance().getWidth();
    int windowHeight = RenderWindow::getInstance().getHeight();

    Shader instancingShader("../Shaders/instancing.vert", "../Shaders/instancing.frag");

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    io.Fonts->AddFontFromFileTTF("../res/fonts/OpenSans-VariableFont_wdth,wght.ttf", 30);

    Simulator simulator;
    simulator.initialize();
    simulator.renderSetup();
    const char *particleTypes[] = {"Empty", "Wall", "Sand", "water"};

    while (!glfwWindowShouldClose(window)) {
        RenderWindow::getInstance().showFPS();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            RenderWindow::getInstance().handleEvent(simulator);
        }

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::ortho(0.0f, (float) windowWidth, (float) windowHeight, 0.0f, -1.0f, 1.0f);
        instancingShader.Activate();
        instancingShader.setMat4("projection", projection);

        simulator.update();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        simulator.renderWithInstances(instancingShader);

        ImGui::Begin("gui");
        for (int i = 0; i < EnumCount; i++) {
            if (ImGui::RadioButton(particleTypes[i], simulator.getSelectedParticleType() == i)) {
                simulator.setSelectedParticleType((ParticleType) i);
            }
        }
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    simulator.cleanUpBuffers();
    instancingShader.Delete();
    RenderWindow::getInstance().cleanUp();
    return 0;
}