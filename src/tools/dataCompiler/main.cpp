#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
bool readActorTypeLine(char line[MAX_CHARS_PER_LINE], S_ActorTypeData &data);
bool readLevelLine(char line[MAX_CHARS_PER_LINE], S_LevelData &data);

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

	if (type == "actors") {
		ResourceManager<S_ActorTypeData> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readActorTypeLine);
		if (!res) {
			return 1;
		}
	}
	else if (type == "levels") {
		ResourceManager<S_LevelData> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readLevelLine);
		if (!res) {
			return 1;
		}
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}

	return 0;
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

bool readActorTypeLine(char line[MAX_CHARS_PER_LINE], S_ActorTypeData &data) {
	int graphic, behaviour, red, green, blue;
	int result = sscanf(
		line, "%d %d %d %d %d %d %d %d %d %d %d\n",
		&graphic, &behaviour, &data.health, &data.stamina,
		&data.attack, &data.speed,
		&red, &green, &blue,
		&data.size, &data.hitboxSize
	);
	data.graphic = (char) graphic;
	data.behaviour = (char) behaviour;
	data.red = (unsigned char) (red & 255);
	data.green = (unsigned char) (green & 255);
	data.blue = (unsigned char) (blue & 255);
	if (result != 11) {
		return false;
	}

	return true;
}

bool readLevelLine(char line[MAX_CHARS_PER_LINE], S_LevelData &data) {
	int result = sscanf(
		line, "%d %d %d\n",
		&data.enemyCount, &data.maxSimultaneousEnemies, &data.difficulty
	);
	if (result != 3) {
		return false;
	}

	return true;
}
