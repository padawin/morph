#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "GUI/Factory.hpp"
#include <SDL2/SDL.h>

class Map;

class MapRenderer {
	private:
	SDL_Rect m_camera;
	Map &m_map;
	GraphicFactory &m_graphicFactory;

	public:
	MapRenderer(Map &map, GraphicFactory &graphicFactory);
	void render();
	void setCamera(SDL_Rect camera);
};

#endif
