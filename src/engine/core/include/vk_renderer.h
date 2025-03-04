#pragma once

#include <renderer_base.h>

namespace FancyEngine {

class FVulkanRenderer : public IFRenderDevice {

public:
    bool Initialize(GLFWwindow* window) override;
    virtual void Shutdown() override;
    virtual void BeginFrame() override;
    virtual void EndFrame() override;
    virtual void ResizeViewport(uint32_t width, uint32_t height) override;

    virtual uint32_t CreateVertexBuffer(const void* data, size_t size) override;
    virtual uint32_t CreateIndexBuffer(const void* data, size_t size) override;
    virtual uint32_t CreateTexture(const void* data, uint32_t width, uint32_t height) override;
    virtual uint32_t CreateShader(const std::string& vertexSource, const std::string& fragmentSource) override;

    virtual void BindShader(uint32_t shaderId) override;
    virtual void BindVertexBuffer(uint32_t bufferId) override;
    virtual void BindIndexBuffer(uint32_t bufferId) override;
    virtual void BindTexture(uint32_t textureId, uint32_t slot) override;
    virtual void DrawIndexed(uint32_t indexCount) override;

private:

    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    
    std::vector<VkPhysicalDevice> GPUs;
    uint32_t GPUsCount = 0;
    VkPhysicalDevice physical = VK_NULL_HANDLE;
    VkDevice logical = VK_NULL_HANDLE;
    
    VkQueue graphicsQueue = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    std::vector<VkImage> swapchainImages;
    uint32_t swapchainImagesCount;
    std::vector<VkImageView> swapchainImagesViews;

    VkRenderPass renderpass = VK_NULL_HANDLE;

    std::vector<VkSemaphore> semaphores;
    VkFence fence = VK_NULL_HANDLE;

    VkCommandPool graphicsPool = VK_NULL_HANDLE;
    VkCommandBuffer graphicsCommand = VK_NULL_HANDLE;

    std::vector<VkFramebuffer> framebuffers;
    uint32_t imageIndex = 0;
    
};


} // namespace FancyEngine