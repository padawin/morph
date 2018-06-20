#ifndef __GRAPHIC__FACTORY__
#define __GRAPHIC__FACTORY__

#include <vector>
#include <memory>

#define GRAPHIC_ACTOR_SQUARE 0

class Graphic;
class GraphicActor;

class GraphicFactory {
	private:
	std::vector<Graphic*> m_vGraphics = {};

	public:
	GraphicFactory();
	~GraphicFactory();
	GraphicActor* getGraphicActor(long unsigned int graphic);

};

#endif
