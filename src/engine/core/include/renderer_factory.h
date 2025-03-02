#pragma once

#include <i_includes.h>
#include <vk_renderer.h>
#include <dx_renderer.h>

namespace FancyEngine {

class RendererFactory {

public:
    enum RendererType {
        //OPENGL,
        VULKAN,
        DIRECTX,
		RENDERER_TYPE_COUNT
    };

    static std::unique_ptr<IFRenderDevice> CreateRenderer(RendererType type) {
        switch (type) {
            //case OPENGL:
                //return std::make_unique<FOpenGLRenderer>();
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