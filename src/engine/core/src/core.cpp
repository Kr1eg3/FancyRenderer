#include <core.h>

namespace FancyEngine {

FEngine::FEngine()
    : window_(800, 600, "Fancy Engine")
    , renderer_type_(RendererFactory::DIRECTX) {
    std::cout << "Engine constructed" << std::endl;
}

FEngine::~FEngine() {
    std::cout << "Engine destructed" << std::endl;
}

void FEngine::Initialize() {
	// --------------------------------------------------------
	// Inititialize GLFW window
    window_.Initialize();
	// --------------------------------------------------------

	// --------------------------------------------------------
	// Initialize renderer via renderer factory
    renderer_ = RendererFactory::CreateRenderer(renderer_type_);
	renderer_->Initialize(window_.GetRawWindow());
	// --------------------------------------------------------



}

void FEngine::Run() {
	while (!glfwWindowShouldClose(window_.GetRawWindow())) {
		glfwPollEvents();


		DoFrame();
	}
}

void FEngine::DoFrame() {
	// --------------------------------------------------------
	// Begin frame
	renderer_->BeginFrame();
	// --------------------------------------------------------






	// --------------------------------------------------------
	// End frame
	renderer_->EndFrame();
	// --------------------------------------------------------
}

} // namespace FancyEngine
