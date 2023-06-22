//
// Created by robcholz on 6/15/23.
//

#ifndef RUNCRAFT_ENTITYACCESS_HPP
#define RUNCRAFT_ENTITYACCESS_HPP

#include "world/poi/Coordinate.hpp"
#include "world/poi/Position.hpp"

class EntityAccess {
public:
	virtual coordinate::Velocity& getVelocity() = 0;

	virtual entity::EntityPosition& getEntityPosition() = 0;

	virtual coordinate::EntityPositionT getHeight() = 0;

	virtual coordinate::EntityPositionT getWidth() = 0;

	virtual float getHealth() = 0;

	virtual float getMaxHealth() = 0;

	virtual bool onGround() = 0;

	virtual bool isDamaged() = 0;
};

#endif //RUNCRAFT_ENTITYACCESS_HPP
