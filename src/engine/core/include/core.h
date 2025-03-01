#pragma once

#include <i_includes.h>
#include <utils.h>
#include <window.h>

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
    FancyUtils::FTimer test_timer_;

};


} // namespace FancyEngine
