#include <core.h>

namespace FancyEngine {

Engine::Engine() {
    std::cout << "Engine constructed" << std::endl;
}

Engine::~Engine() {
    std::cout << "Engine destructed" << std::endl;
}

} // namespace FancyEngine
