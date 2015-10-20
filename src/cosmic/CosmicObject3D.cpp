/*
 * CosmicObject3D.cpp
 *
 *  Created on: 17 janv. 2014
 *      Author: bmathieu
 */

#include "CosmicObject3D.h"
#include "CosmicObject.hpp"

using namespace std;
using namespace brain;
using namespace brain::cosmic;

void brain::cosmic::timedtevent(ISystem& s, shared_ptr<IEvent> e)
{
	Logger<TimeDtEvent>::trace("Premier evenement cosmic");
}

CosmicObject3D::CosmicObject3D() :
		CosmicObject<Vector3D>()
{
}

CosmicObject3D::CosmicObject3D(const CosmicObject3D& other) :
		CosmicObject<Vector3D>(other)
{
}

CosmicObject3D::~CosmicObject3D()
{
}

CosmicObject3D& CosmicObject3D::operator =(const CosmicObject3D& other)
{
	if (this != &other)
	{
		this->CosmicObject<Vector3D>::operator =(other);
	}

	return (*this);
}
