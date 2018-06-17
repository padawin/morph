#include "GUI/Factory.hpp"
#include "GUI/Actor.hpp"
#include "GUI/Player.hpp"

GraphicFactory::GraphicFactory() {
	m_vGraphics = {
		new GraphicActor(),
		new GraphicPlayer()
	};
}

GraphicActor* GraphicFactory::getGraphicActor() {
	return (GraphicActor*) m_vGraphics[0];
}

GraphicPlayer* GraphicFactory::getGraphicPlayer() {
	return (GraphicPlayer*) m_vGraphics[1];
}
