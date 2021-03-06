#include "Engine.hpp"
#include "globals.hpp"
#include "HUD.hpp"
#include "GUI.hpp"
#include "Map/Renderer.hpp"
#include "Actor.hpp"
#include <iostream>
#include <iterator>
#include "SDL2_framework/Game.h"

Engine::Engine() :
	m_hero(nullptr),
	m_graphicFactory(GraphicFactory()),
	m_actorFactory(ActorFactory(m_graphicFactory)),
	m_map(Map()),
	m_level(Level(m_actorFactory)),
	m_mapRenderer(MapRenderer(m_map, m_graphicFactory)),
	m_camera()
{
}

void Engine::initialise() {
	m_camera = {
		0, 0,
		Game::Instance()->getScreenWidth(), Game::Instance()->getScreenHeight()
	};

	m_mapRenderer.setCamera(m_camera);
	m_map.setDimensions(m_camera.w, m_camera.h);
}

Engine::~Engine() {}

Map &Engine::getMap() {
	return m_map;
}

std::shared_ptr<Actor> Engine::getHero() {
	return m_hero;
}

bool Engine::loadTaxonomy(std::string filePath) {
	bool ret = true;
	if (m_actorFactory.parseTaxonomy(filePath.c_str())) {
		std::cout << "Taxonomy parsed\n";
	}
	else {
		std::cout << "error parsing taxonomy" << std::endl;
		ret = false;
	}

	return ret;
}

bool Engine::loadLevels(std::string filePath) {
	bool ret = true;
	if (m_level.parseLevels(filePath.c_str())) {
		std::cout << "Levels parsed\n";
	}
	else {
		std::cout << "error parsing levels" << std::endl;
		ret = false;
	}

	return ret;
}

bool Engine::isLevelFinished() {
	return m_level.isFinished() && m_map.getActors().size() == 1;
}

bool Engine::reloadLevel() {
	return _loadLevel(0);
}

bool Engine::loadNextLevel() {
	return _loadLevel(+1);
}

bool Engine::_loadLevel(int index) {
	if (m_level.load(index)) {
		initialiseHeroData();
		return true;
	}
	return false;
}

void Engine::initialiseHero() {
	m_hero = m_actorFactory.createHero();
	initialiseHeroData();
	m_map.addActor(m_hero);
}

void Engine::initialiseHeroData() {
	m_hero->setX((double) m_map.getWidth() / 2);
	m_hero->setY((double) m_map.getHeight() / 2);
	m_hero->setHealth(m_hero->getMaxHealth());
}

void Engine::update() {
	m_hero->update(this);
	for (auto actor : m_map.getActors()) {
		if (actor != m_hero) {
			actor->update(this);
		}
	}

	if (!m_hero->isDead()) {
		m_map.clearDeadActors();
		m_level.update(m_map);
	}
	else if (m_iLifes > 0) {
		--m_iLifes;
		m_map.clearActors();
		initialiseHero();
		reloadLevel();
	}
}

void Engine::render() {
	m_mapRenderer.render();
	// render HUD
	HUD::render(Game::Instance(), m_hero);
}
