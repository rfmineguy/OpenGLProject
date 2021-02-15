#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "handlers/InputHandler.h"
#include "handlers/ResizeHandler.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include <tests/MainTest.h>
#include <tests/QuadTest.h>
#include <tests/CameraTest.h>
#include <tests/CubeTest.h>

struct InputHandler Input;
struct ResizeHandler Resize;

bool firstMouse = true;

const char* GLSL_VERSION = "#version 450";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == 0) {
        Input.keys[key] = false;
    } else if (action == 1) {
        Input.keys[key] = true;
    }

    if (Input.keys[32]) {
        firstMouse = true;
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        Input.lastX = xpos;
        Input.lastY = ypos;
        firstMouse = false;
    }

    double xOffset = xpos - Input.lastX;
    double yOffset = Input.lastY - ypos; //reversed on purpose
    xOffset *= Input.sensitivity;
    yOffset *= Input.sensitivity;
    Input.lastX = xpos;
    Input.lastY = ypos;
    Input.yaw += xOffset;
    Input.pitch += yOffset;
    if (Input.pitch > 89.f)
        Input.pitch = 89.f;
    if (Input.pitch < -89.f)
        Input.pitch = -89.f;
}
void resize_callback(GLFWwindow* window, int width, int height) {
    glfwGetFramebufferSize(window, &Resize.lastWindowWidth, &Resize.lastWindowHeight);

    Resize.windowWidth = width;
    Resize.windowHeight = height;

    printf("%d  %d", Resize.lastWindowHeight, Resize.windowHeight);
    glViewport(0, 0, width, height);
}

//sets up various settings required for the rest of the program
GLFWwindow* CreateWindow() {
    GLFWwindow* window;
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // =======
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // Sets OpenGL version 3.3 <MAJOR.MINOR>
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW_OPENGL_CORE_PROFILE or GLFW_OPENGL_COMPAT_PROFILE

    window = glfwCreateWindow(960, 540, "OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return nullptr;
    }

    //callback above this function
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    glfwMakeContextCurrent(window);

    std::cout << "Created Window" << std::endl;
    return window;
}
void GLSetup() {
    std::cout << "Glad setup -> ";
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED" << std::endl;
        glfwTerminate();
    }
    std::cout << "SUCCESS :: Version -> " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void ImGuiSetup(GLFWwindow* window) {
    std::cout << "ImGui Setup";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    std::cout << " -> SUCCESS" << std::endl;
}
GLFWwindow* FullSetup() {
    printf("-------------------SETUP PROCESS-------------------\n");
    GLFWwindow* window = CreateWindow();
    GLSetup();
    ImGuiSetup(window);
    std::cout << "Full Setup -> SUCCESS" << std::endl;
    printf("-------------------SETUP PROCESS-------------------\n");
    printf("--------------------APPLICATION--------------------\n");
    return window;
}

//main src
void InputHandling(GLFWwindow* window) {
    if(Input.keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(window, true);
    }
}
int main() {
    GLFWwindow* window = FullSetup();

    {
        test::Test *currentTest = nullptr;
        auto testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::QuadTest>("QuadTest");
        testMenu->RegisterTest<test::MainTest>("MainTest");
        testMenu->RegisterTest<test::CameraTest>("CamTest");
        testMenu->RegisterTest<test::CubeTest>("CubeTest");

        double deltaTime = 0.0f;    // Time between current frame and last frame
        double lastFrame = 0.0f; // Time of last frame
        while (!glfwWindowShouldClose(window)) {
            //calc delta time
            {
                deltaTime = glfwGetTime() - lastFrame;
                lastFrame = glfwGetTime();
            }
            InputHandling(window);

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(.5f, .5f, .5f, 1.f);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest != nullptr) {
                currentTest->OnUpdate(deltaTime);
                currentTest->OnRender();
                if (Resize.shouldResize) {
                    currentTest->OnResize(Resize.windowWidth, Resize.windowHeight);
                    Resize.shouldResize = false;
                }

                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();

                if (currentTest == testMenu) ImGui::Text("Application Controls");
                if (currentTest == testMenu && ImGui::Button("Exit")) {
                    break;
                }
                ImGui::NewLine();
                ImGui::Text("Delta Time %.3f", deltaTime);

                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        if (currentTest != testMenu) {
            delete(testMenu);
        }
        delete(currentTest);
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}