#include <vk_renderer.h>

namespace FancyEngine {

bool FVulkanRenderer::Initialize(GLFWwindow* window) {
	std::cout << "DirectX renderer initialized" << std::endl;
	return true;
}

void FVulkanRenderer::Shutdown() {
	std::cout << "DirectX renderer shutdown" << std::endl;
}

void FVulkanRenderer::BeginFrame() {
	std::cout << "DirectX renderer begin frame" << std::endl;
}

void FVulkanRenderer::EndFrame() {
	std::cout << "DirectX renderer end frame" << std::endl;
}

void FVulkanRenderer::ResizeViewport(uint32_t width, uint32_t height) {
	std::cout << "DirectX renderer resize viewport" << std::endl;
}

uint32_t FVulkanRenderer::CreateVertexBuffer(const void* data, size_t size) {
	std::cout << "DirectX renderer create vertex buffer" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateIndexBuffer(const void* data, size_t size) {
	std::cout << "DirectX renderer create index buffer" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateTexture(const void* data, uint32_t width, uint32_t height) {
	std::cout << "DirectX renderer create texture" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
	std::cout << "DirectX renderer create shader" << std::endl;
	return 0;
}

void FVulkanRenderer::BindShader(uint32_t shaderId) {
	std::cout << "DirectX renderer bind shader" << std::endl;
}

void FVulkanRenderer::BindVertexBuffer(uint32_t bufferId) {
	std::cout << "DirectX renderer bind vertex buffer" << std::endl;
}

void FVulkanRenderer::BindIndexBuffer(uint32_t bufferId) {
	std::cout << "DirectX renderer bind index buffer" << std::endl;
}

void FVulkanRenderer::BindTexture(uint32_t textureId, uint32_t slot) {
	std::cout << "DirectX renderer bind texture" << std::endl;
}

void FVulkanRenderer::DrawIndexed(uint32_t indexCount) {
	std::cout << "DirectX renderer draw indexed" << std::endl;
}


} // namespace FancyEngine