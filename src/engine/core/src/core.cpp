#include "window.h"
#include <core.h>

namespace FancyEngine {

FEngine::FEngine()
    : window_(800, 600, "Fancy Engine"), renderer_type_(RendererFactory::VULKAN) {
    std::cout << "Engine constructed" << std::endl;
}

FEngine::~FEngine() {
    std::cout << "Engine destructed" << std::endl;
}

void FEngine::Initialize() {
    window_.Initialize();
    renderer_ = RendererFactory::createRenderer(renderer_type_);
}

} // namespace FancyEngine
