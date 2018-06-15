#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);

int main(int argc, char* argv[]) {
	// expects the following arguments:
	// dataType (tiles),
	// dataFileIn (path to the humanly readable file),
	// dataFileOut (path to the compiled file)

	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " dataType dataFileIn dataFileOut\n";
		return 1;
	}

	std::string type = argv[1],
		fileIn = cleanFileInPath(argv[2]),
		fileOut = argv[3];

	std::cerr << "Invalid type: " << type << "\n";
	return 2;
}

std::string cleanFileInPath(std::string path) {
	if (path[0] == '/') {
		return path;
	}
	else {
		char cwd[1024];
		char* res = getcwd(cwd, sizeof(cwd));
		if (!res) {
			return "./" + path;
		}

		return std::string(cwd) + "/" + path;
	}
}
