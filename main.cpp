#include <core.h>


auto main(int argc, char *argv[]) -> int {

    FancyUtils::FTimer t;
    t.reset(); t.start();

    FancyEngine::FEngine e;
	e.Initialize();
    e.Run();
    float f = t.tick();
    std::cout << "Time elapsed: " << f << " seconds" << std::endl;

    return 0;
}
