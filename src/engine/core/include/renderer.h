#pragma once

#include <i_includes.h>

namespace FancyEngine {

class FRenderer {
public:
	virtual ~FRenderer() = default;
	virtual void initialize() = 0;
	virtual void render() = 0;
	virtual void shutdown() = 0;
};

class FOpenGLRenderer : public FRenderer {
public:
	void initialize() override {
		std::cout << "OpenGL renderer initialized" << std::endl;
	}

	void render() override {
		std::cout << "Rendering with OpenGL" << std::endl;
	}

	void shutdown() override {
		std::cout << "OpenGL renderer shutdown" << std::endl;
	}
};

class FVulkanRenderer : public FRenderer {
public:
	void initialize() override {
		std::cout << "Vulkan renderer initialized" << std::endl;
	}

	void render() override {
		std::cout << "Rendering with Vulkan" << std::endl;
	}

	void shutdown() override {
		std::cout << "Vulkan renderer shutdown" << std::endl;
	}
};

class FDirectXRenderer : public FRenderer {
public:
	void initialize() override {
		std::cout << "DirectX renderer initialized" << std::endl;
	}

	void render() override {
		std::cout << "Rendering with DirectX" << std::endl;
	}

	void shutdown() override {
		std::cout << "DirectX renderer shutdown" << std::endl;
	}
};

class RendererFactory {
public:
    enum RendererType {
        OPENGL,
        VULKAN,
        DIRECTX
    };

    static std::unique_ptr<FRenderer> createRenderer(RendererType type) {
        switch (type) {
            case OPENGL:
                return std::make_unique<FOpenGLRenderer>();
            case VULKAN:
                return std::make_unique<FVulkanRenderer>();
            case DIRECTX:
                return std::make_unique<FDirectXRenderer>();
            default:
                return std::make_unique<FVulkanRenderer>();
        }
    }
};

} // namespace FancyEngine