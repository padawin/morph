#ifndef __RRPG__
#define __RRPG__

#include "ActorFactory.hpp"
#include "GUI/Factory.hpp"
#include "Map/Renderer.hpp"
#include "Map.hpp"
#include "Level.hpp"
#include <string>
#include <memory>
#include <SDL2/SDL.h>

class Actor;

class Engine {
	private:
	std::shared_ptr<Actor> m_hero;
	GraphicFactory m_graphicFactory;
	ActorFactory m_actorFactory;
	Map m_map;
	Level m_level;
	MapRenderer m_mapRenderer;
	bool m_bIsBlocked = false;
	std::string m_sTilesFile = "";
	std::string m_sObjectsFile = "";
	SDL_Rect m_camera;

	public:
	Engine();
	~Engine();
	Map &getMap();
	std::shared_ptr<Actor> getHero();
	bool loadTaxonomy(std::string filePath);
	bool loadLevels(std::string filePath);
	void initialiseHero();
	void update();
	void render();
};

#endif
