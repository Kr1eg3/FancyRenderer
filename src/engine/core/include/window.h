#pragma once

#include <i_includes.h>


namespace  FancyEngine  {

class FWindow {

    struct GLFWwindowDeleter {
        void operator()(GLFWwindow* window) {
            if (window) {
                glfwDestroyWindow(window);
                std::cout << "Raw window destroyed" << std::endl;
            }
        }
    };

    using GLFWwindowPtr = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;

public:
    FWindow(int width, int height, const char* title);
    FWindow(FWindow &&) noexcept = default;
    FWindow &operator=(FWindow &&) noexcept = default;
    ~FWindow();

    FWindow(const FWindow &) = delete;
    FWindow &operator=(const FWindow &) = delete;

    void Initialize();


    inline GLFWwindow* GetRawWindow() const { return p_window_.get(); }
    inline void* getNativeHandle() {
#ifdef __APPLE__
            return static_cast<void*>(glfwGetCocoaWindow(p_window_.get()));
#elif _WIN32
            return static_cast<void*>(glfwGetWin32Window(p_window_.get()));
#else
            return nullptr;
#endif
    }
    inline bool IsWindowInitialized() const { return is_initialized_; }

private:
    GLFWwindowPtr p_window_;
    int width_;
    int height_;
    const char* p_title_;
    bool is_initialized_;
};



} // namespace FancyEngine
