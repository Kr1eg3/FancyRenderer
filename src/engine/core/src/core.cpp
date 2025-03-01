#include "window.h"
#include <core.h>

namespace FancyEngine {

FEngine::FEngine()
    : window_(800, 600, "Fancy Engine") {
    std::cout << "Engine constructed" << std::endl;
}

FEngine::~FEngine() {
    std::cout << "Engine destructed" << std::endl;
}

void FEngine::Initialize() {
    window_.Initialize();
}

} // namespace FancyEngine
