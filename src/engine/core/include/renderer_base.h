#pragma once

#include <i_includes.h>

namespace FancyEngine {

class IFRenderDevice {
public:
    virtual ~IFRenderDevice() = default;

    virtual bool Initialize(GLFWwindow* window) = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void ResizeViewport(uint32_t width, uint32_t height) = 0;

    virtual uint32_t CreateVertexBuffer(const void* data, size_t size) = 0;
    virtual uint32_t CreateIndexBuffer(const void* data, size_t size) = 0;
    virtual uint32_t CreateTexture(const void* data, uint32_t width, uint32_t height) = 0;
    virtual uint32_t CreateShader(const std::string& vertexSource, const std::string& fragmentSource) = 0;

    virtual void BindShader(uint32_t shaderId) = 0;
    virtual void BindVertexBuffer(uint32_t bufferId) = 0;
    virtual void BindIndexBuffer(uint32_t bufferId) = 0;
    virtual void BindTexture(uint32_t textureId, uint32_t slot) = 0;
    virtual void DrawIndexed(uint32_t indexCount) = 0;
};


} // namespace FancyEngine