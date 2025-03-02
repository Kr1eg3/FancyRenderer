#pragma once

#include <i_includes.h>
#include <renderer_base.h>

namespace FancyEngine {

class FDirectXRenderer : public IFRenderDevice {

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
	Microsoft::WRL::ComPtr<ID3D11Device>			p_device_;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			p_swap_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		p_context_;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	p_target_;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	p_depth_stencil_view_;
};


} // namespace FancyEngine