#pragma once

#include <i_includes.h>
#include <utils.h>
#include <window.h>
#include <renderer.h>

namespace FancyEngine {


class FEngine {

public:
    FEngine();
    FEngine(FEngine &&) noexcept = default;
    FEngine &operator=(FEngine &&) noexcept = default;
    ~FEngine();

    FEngine(const FEngine &) = delete;
    FEngine &operator=(const FEngine &) = delete;

    void Initialize();


private:
    FWindow window_;
    std::unique_ptr<FRenderer> renderer_;
    FancyUtils::FTimer test_timer_;
    RendererFactory::RendererType renderer_type_;

};


} // namespace FancyEngine
