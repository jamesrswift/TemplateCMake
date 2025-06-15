
#include <iostream>
#include <filesystem>

#include <MyProject/Version.h>

int main(int argc, char* argv[]) {
	// Initialize the application
	// ...
	// Run the main event loop
	// ...

	std::cout << "MyApplication Version: " << MY_VERSION << std::endl;
	std::cout << std::filesystem::exists("./assets/.gitkeep") << std::endl;
	return 0;
}
