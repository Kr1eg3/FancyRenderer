#include <dx_renderer.h>

namespace FancyEngine {

bool FDirectXRenderer::Initialize(GLFWwindow* window) {
	std::cout << "DirectX renderer initialized" << std::endl;
	return true;
}

void FDirectXRenderer::Shutdown() {
	std::cout << "DirectX renderer shutdown" << std::endl;
}

void FDirectXRenderer::BeginFrame() {
	std::cout << "DirectX renderer begin frame" << std::endl;
}

void FDirectXRenderer::EndFrame() {
	std::cout << "DirectX renderer end frame" << std::endl;
}

void FDirectXRenderer::ResizeViewport(uint32_t width, uint32_t height) {
	std::cout << "DirectX renderer resize viewport" << std::endl;
}

uint32_t FDirectXRenderer::CreateVertexBuffer(const void* data, size_t size) {
	std::cout << "DirectX renderer create vertex buffer" << std::endl;
	return 0;
}

uint32_t FDirectXRenderer::CreateIndexBuffer(const void* data, size_t size) {
	std::cout << "DirectX renderer create index buffer" << std::endl;
	return 0;
}

uint32_t FDirectXRenderer::CreateTexture(const void* data, uint32_t width, uint32_t height) {
	std::cout << "DirectX renderer create texture" << std::endl;
	return 0;
}

uint32_t FDirectXRenderer::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
	std::cout << "DirectX renderer create shader" << std::endl;
	return 0;
}

void FDirectXRenderer::BindShader(uint32_t shaderId) {
	std::cout << "DirectX renderer bind shader" << std::endl;
}

void FDirectXRenderer::BindVertexBuffer(uint32_t bufferId) {
	std::cout << "DirectX renderer bind vertex buffer" << std::endl;
}

void FDirectXRenderer::BindIndexBuffer(uint32_t bufferId) {
	std::cout << "DirectX renderer bind index buffer" << std::endl;
}

void FDirectXRenderer::BindTexture(uint32_t textureId, uint32_t slot) {
	std::cout << "DirectX renderer bind texture" << std::endl;
}

void FDirectXRenderer::DrawIndexed(uint32_t indexCount) {
	std::cout << "DirectX renderer draw indexed" << std::endl;
}


} // namespace FancyEngine