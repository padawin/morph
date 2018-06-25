#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
void writeActorType(std::ofstream &fileOutStream, S_ActorTypeData actorType);
void writeLevel(std::ofstream &fileOutStream, S_LevelData level);
template <typename T>
bool decompileFile(
	ResourceManager<T> *resourceManager,
	void (callback)(std::ofstream&, T),
	std::string fileIn,
	std::string fileOut
);

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

	bool ret;
	if (type == "actors") {
		ret = decompileFile(new ResourceManager<S_ActorTypeData>(), writeActorType, fileIn, fileOut);
	}
	else if (type == "levels") {
		ret = decompileFile(new ResourceManager<S_LevelData>(), writeLevel, fileIn, fileOut);
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}

	return ret ? 0 : 1;
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

void writeActorType(std::ofstream &fileOutStream, S_ActorTypeData actorType) {
	fileOutStream <<
		actorType.graphic << " "
		<< actorType.behaviour << " "
		<< actorType.health << " "
		<< actorType.attack << " "
		<< actorType.speed << " "
		<< actorType.red << " "
		<< actorType.green << " "
		<< actorType.blue << " "
		<< actorType.width << " "
		<< actorType.height << " "
		<< actorType.hitboxWidth << " "
		<< actorType.hitboxHeight << "\n";
}


void writeLevel(std::ofstream &fileOutStream, S_LevelData level) {
	fileOutStream <<
		level.enemyCount << " "
		<< level.maxSimultaneousEnemies << " "
		<< level.difficulty << "\n";
}


template <typename T>
bool decompileFile(
	ResourceManager<T> *resourceManager,
	void (callback)(std::ofstream&, T),
	std::string fileIn,
	std::string fileOut
) {
	resourceManager->setResourceFile(fileIn);
	resourceManager->parseBinaryFile();
	bool ret = resourceManager->saveReadableFile(fileOut, callback);
	delete resourceManager;
	return ret;
}
