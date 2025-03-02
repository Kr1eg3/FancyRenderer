#include <vk_renderer.h>

namespace FancyEngine {

bool FVulkanRenderer::Initialize(GLFWwindow* window) {
	std::cout << "Vulkan renderer initialized" << std::endl;
	return true;
}

void FVulkanRenderer::Shutdown() {
	std::cout << "Vulkan renderer shutdown" << std::endl;
}

void FVulkanRenderer::BeginFrame() {
	std::cout << "Vulkan renderer begin frame" << std::endl;
}

void FVulkanRenderer::EndFrame() {
	std::cout << "Vulkan renderer end frame" << std::endl;
}

void FVulkanRenderer::ResizeViewport(uint32_t width, uint32_t height) {
	std::cout << "Vulkan renderer resize viewport" << std::endl;
}

uint32_t FVulkanRenderer::CreateVertexBuffer(const void* data, size_t size) {
	std::cout << "Vulkan renderer create vertex buffer" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateIndexBuffer(const void* data, size_t size) {
	std::cout << "Vulkan renderer create index buffer" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateTexture(const void* data, uint32_t width, uint32_t height) {
	std::cout << "Vulkan renderer create texture" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
	std::cout << "Vulkan renderer create shader" << std::endl;
	return 0;
}

void FVulkanRenderer::BindShader(uint32_t shaderId) {
	std::cout << "Vulkan renderer bind shader" << std::endl;
}

void FVulkanRenderer::BindVertexBuffer(uint32_t bufferId) {
	std::cout << "Vulkan renderer bind vertex buffer" << std::endl;
}

void FVulkanRenderer::BindIndexBuffer(uint32_t bufferId) {
	std::cout << "Vulkan renderer bind index buffer" << std::endl;
}

void FVulkanRenderer::BindTexture(uint32_t textureId, uint32_t slot) {
	std::cout << "Vulkan renderer bind texture" << std::endl;
}

void FVulkanRenderer::DrawIndexed(uint32_t indexCount) {
	std::cout << "Vulkan renderer draw indexed" << std::endl;
}


} // namespace FancyEngine