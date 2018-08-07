#include "SDL2_framework/Game.h"
#include "../Actor.hpp"
#include "ActorPolygon.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;

double GraphicActorPolygon::_getRenderRatio() {
	return 1;
}

std::pair<std::vector<Sint16>, std::vector<Sint16>> GraphicActorPolygon::_getCorners(
	Actor *actor, E_ActorAttack orientation, double distanceFromCenter, double initialAngle
) {
	distanceFromCenter += actor->getSize();
	double c, s, xOrig, yOrig, x, y;
	double angle = _getAngleCorners();
	xOrig = 0;
	yOrig = -distanceFromCenter / 2;
	if (orientation == ATTACK_RIGHT) {
		xOrig = distanceFromCenter / 2;
		yOrig = 0;
	}
	else if (orientation == ATTACK_DOWN) {
		xOrig = 0;
		yOrig = distanceFromCenter / 2;
	}
	else if (orientation == ATTACK_LEFT) {
		xOrig = -distanceFromCenter / 2;
		yOrig = 0;
	}
	xOrig *= _getRenderRatio();
	yOrig *= _getRenderRatio();
	std::pair<std::vector<Sint16>, std::vector<Sint16>> corners;
	for (long unsigned i = 0; i < _getCountCorners() ; ++i) {
		s = sin(initialAngle + angle * (int) i);
		c = cos(initialAngle + angle * (int) i);
		x = xOrig * c - yOrig * s;
		y = xOrig * s + yOrig * c;
		corners.first.push_back((Sint16) (actor->getX() + x));
		corners.second.push_back((Sint16) (actor->getY() + y));
	}
	return corners;
}

void GraphicActorPolygon::render(int displayShiftX, int displayShiftY, Actor *actor) {
	_renderPolygon(displayShiftX, displayShiftY, actor, _getCorners(actor, m_lastAttack, 0), actor->isHollow());
	_renderAttacks(displayShiftX, displayShiftY, actor);
}

void GraphicActorPolygon::_renderPolygon(int displayShiftX, int displayShiftY, Actor* actor, std::pair<std::vector<Sint16>, std::vector<Sint16>> corners, bool hollow) {
	Game* game = Game::Instance();
	long unsigned nbCorners = _getCountCorners();

	if (hollow) {
		for (unsigned int i = 0; i < nbCorners; ++i) {
			thickLineRGBA(
				game->getRenderer(),
				(Sint16) (displayShiftX + corners.first[i]),
				(Sint16) (displayShiftY + corners.second[i]),
				(Sint16) (displayShiftX + corners.first[(i + 1) % nbCorners]),
				(Sint16) (displayShiftY + corners.second[(i + 1) % nbCorners]),
				ACTOR_RIM_THICKNESS,
				actor->getRed(), actor->getGreen(), actor->getBlue(), 255
			);
		}
	}
	else {
		filledPolygonRGBA(
			game->getRenderer(),
			&corners.first[0], &corners.second[0], (int) nbCorners,
			actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}
}
