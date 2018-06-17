#ifndef __GRAPHIC__FACTORY__
#define __GRAPHIC__FACTORY__

#include <vector>
#include <memory>

class Graphic;
class GraphicTerrain;
class GraphicObject;
class GraphicActor;
class GraphicPlayer;

class GraphicFactory {
	private:
	std::vector<Graphic*> m_vGraphics = {};

	public:
	GraphicFactory();
	GraphicActor* getGraphicActor();
	GraphicPlayer* getGraphicPlayer();

};

#endif
