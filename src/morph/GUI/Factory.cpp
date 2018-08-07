#include "GUI/Factory.hpp"
#include "GUI/ActorSquare.hpp"
#include "GUI/ActorTriangle.hpp"
#include "GUI/ActorDisc.hpp"
#include "GUI/ActorStar.hpp"

GraphicFactory::GraphicFactory() {
	m_vGraphics = {
		new GraphicActorSquare(),
		new GraphicActorTriangle(),
		new GraphicActorDisc(),
		new GraphicActorStar()
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
