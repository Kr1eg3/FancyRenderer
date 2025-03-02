#include <dx_renderer.h>

namespace FancyEngine {

bool FDirectXRenderer::Initialize(GLFWwindow* window) {
	HWND hWnd = static_cast<HWND>(glfwGetWin32Window(window));

	// A DXGI_MODE_DESC structure that describes the backbuffer display mode. (BufferDesc)
	DXGI_SWAP_CHAIN_DESC sd = {};

	// Width and height of the back buffer in pixels. If you specify 0 for Width and Height, DXGI
	// will use the width and height of the client area of the target window.
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;

	// A member of the DXGI_FORMAT enumerated type that describes the display format.
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

	// A DXGI_RATIONAL structure that describes the refresh rate in hertz of the back buffer.
	// If you specify 0 for the numerator and the denominator, DXGI will use the default refresh rate.
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;

	// A member of the DXGI_MODE_SCANLINE_ORDER enumerated type that describes the scanline drawing mode.
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// A member of the DXGI_MODE_SCANLINE_ORDER enumerated type that describes the scanline drawing mode.
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// A member of the DXGI_SAMPLE_DESC structure that describes multi-sampling parameters.
	// If you do not want to use multi-sampling, set Count to 1 and Quality to 0. (anti-aliasing)
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	// A member of the DXGI_USAGE enumerated type that describes the surface usage and CPU access options for the back buffer.
	// The back buffer can be used for shader input or render-target output.
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// A value that describes the number of buffers in the swap chain. When you call IDXGIFactory::CreateSwapChain
	// to create a full-screen swap chain, you typically include the front buffer in this value.
	// Set it to 1 for double buffering, or 2 for triple buffering.
	sd.BufferCount = 1;

	// An HWND handle to the output window. This member must not be NULL.
	sd.OutputWindow = hWnd;

	// A Boolean value that specifies whether the output is in windowed mode. TRUE if the output is in windowed mode;
	// otherwise, FALSE.
	// We recommend that you create a windowed swap chain and allow the end user to change the swap chain
	// to full screen through IDXGISwapChain::SetFullscreenState; that is, do not set this member to FALSE
	// to force the swap chain to be full screen. However, if you create the swap chain as full screen,
	// also provide the end user with a list of supported display modes through the BufferDesc member because
	// a swap chain that is created with an unsupported display mode might cause the display to go black and
	// prevent the end user from seeing anything.
	sd.Windowed = TRUE;

	// A member of the DXGI_SWAP_EFFECT enumerated type that describes options
	// for handling the contents of the presentation buffer after presenting a surface.
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// A member of the DXGI_SWAP_CHAIN_FLAG enumerated type that describes options for swap-chain behavior.
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create device and front/back buffers, and swap chain and rendering context
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&p_swap_,
		&p_device_,
		nullptr,
		&p_context_
	);

    if (FAILED(hr))
		return false;

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	hr = p_swap_->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	if (FAILED(hr))
		return false;

	hr = p_device_->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &p_target_);
	if (FAILED(hr))
		return false;

	// create depth stencil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	hr = p_device_->CreateDepthStencilState(&dsDesc, &pDSState);
	if (FAILED(hr))
		return false;

	// bind depth state
	p_context_->OMSetDepthStencilState(pDSState.Get(), 1u);

	// create depth stancil texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 800u;
	descDepth.Height = 600u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hr = p_device_->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
	if (FAILED(hr))
		return false;

	// create view of depth stencil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	hr = p_device_->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &p_depth_stencil_view_);
	if (FAILED(hr))
		return false;

	// bind depth stencil view to OM
	p_context_->OMSetRenderTargets(1u, p_target_.GetAddressOf(), p_depth_stencil_view_.Get());

	// configure viewport
	D3D11_VIEWPORT vp = {};
	vp.Width = 800.0f;
	vp.Height = 600.0f;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	p_context_->RSSetViewports(1u, &vp);

	// init imgui d3d impl
	//ImGui_ImplDX11_Init(p_device_.Get(), p_context_.Get());

	std::cout << "DirectX renderer initialized" << std::endl;
	return true;
}

void FDirectXRenderer::Shutdown() {
	std::cout << "DirectX renderer shutdown" << std::endl;
}

void FDirectXRenderer::BeginFrame() {
	//std::cout << "DirectX renderer begin frame" << std::endl;

	const float red = 0.0f;
	const float green = 1.0f;
	const float blue = 0.0f;
	const float color[] = { red, green, blue, 1.0f };
	p_context_->ClearRenderTargetView(p_target_.Get(), color);
	p_context_->ClearDepthStencilView(p_depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void FDirectXRenderer::EndFrame() {
	HRESULT hr;
#ifndef NDEBUG
	infoManager.Set();
#endif
	hr = p_swap_->Present(1u, 0u);
	//if (FAILED(hr))
	//if (FAILED(hr = p_swap_->Present(1u, 0u))) {
	//	if (hr == DXGI_ERROR_DEVICE_REMOVED) {
	//		throw GFX_DEVICE_REMOVED_EXCEPT(p_device_->GetDeviceRemovedReason());
	//	} else {
	//		throw GFX_EXCEPT(hr);
	//	}
	//}
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