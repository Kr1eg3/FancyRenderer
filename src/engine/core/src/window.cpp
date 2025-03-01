#include <window.h>
#include <iostream>

namespace  FancyEngine {

FWindow::FWindow(int width, int height, const char* title)
    : width_(width), height_(height), p_title_(title), p_window_(nullptr) {
}

FWindow::~FWindow() {
    glfwTerminate();
    std::cout << "Window destryoed" << std::endl;
}

void FWindow::Initialize() {
    if (is_initialized_) {
        std::cerr << "Window already initialized" << std::endl;
        return;
    }

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    if (IsPlatformMacOS()) {
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_TRUE);
    }

    GLFWwindow* raw_window = glfwCreateWindow(width_, height_, p_title_, nullptr, nullptr);
    if (!raw_window) {
        glfwTerminate();
        std::cerr << "Failed to create window" << std::endl;
        return;
    }

    p_window_.reset(raw_window);
    is_initialized_ = true;
    std::cout << "Window initialized" << std::endl;
}

} // namespace FancyEngine
