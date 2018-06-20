#include "GUI/Factory.hpp"
#include "GUI/ActorSquare.hpp"

GraphicFactory::GraphicFactory() {
	m_vGraphics = {
		new GraphicActorSquare()
	};
}

GraphicFactory::~GraphicFactory() {
	for (auto graphic : m_vGraphics) {
		delete graphic;
	}
}

GraphicActor* GraphicFactory::getGraphicActor(long unsigned int graphic) {
	return (GraphicActor*) m_vGraphics[graphic];
}
