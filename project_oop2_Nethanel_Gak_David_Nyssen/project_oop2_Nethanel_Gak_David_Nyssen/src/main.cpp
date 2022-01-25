#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "Controller.h"

int main() try //PROJECT OOP2 NETHANEL GAK AND DAVID NYSSEN
{
	std::srand(unsigned int(std::time(NULL)));


	auto c = Controller();
	c.run();

	return 0;
}

catch (std::ios_base::failure e)
{
	std::cerr << e.what();
	std::cerr << " exception occured." << std::endl;
	return EXIT_FAILURE;
}

catch (std::exception& ex)
{
	std::cerr << "Exception: " << ex.what() << '\n';
	return EXIT_FAILURE;
}

catch (...) {}
