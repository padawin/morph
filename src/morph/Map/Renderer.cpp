#include "Map/Renderer.hpp"
#include "Map.hpp"
#include "Actor.hpp"

MapRenderer::MapRenderer(Map &map, GraphicFactory &graphicFactory) :
	m_camera(),
	m_map(map),
	m_graphicFactory(graphicFactory)
{
}

void MapRenderer::setCamera(SDL_Rect camera) {
	m_camera = camera;
}

void MapRenderer::render() {
	for (auto actor : m_map.getActors()) {
		actor->render(m_camera.x, m_camera.y);
	}
}
