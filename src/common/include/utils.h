#include <chrono>

namespace  FancyUtils {


class FTimer {

public:
    FTimer() : is_running_(false) {}
    ~FTimer() = default;

    void start() {
        start_time_ = std::chrono::steady_clock::now();
        is_running_ = true;
    }

    float reset() {
        if (!is_running_) return 0.0f;

        auto elapsed = tick();
        start_time_ = std::chrono::steady_clock::now();
        return elapsed;
    }

    float tick() {
        if (!is_running_) return 0.0f;

        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<float>(now - start_time_).count();
    }

private:
    std::chrono::steady_clock::time_point start_time_;
    bool is_running_;
};



} // namespace FUtils
