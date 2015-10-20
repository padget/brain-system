/*
 * CosmicObject3D.h
 *
 *  Created on: 17 janv. 2014
 *      Author: bmathieu
 */

#ifndef COSMICOBJECT3D_H_
#define COSMICOBJECT3D_H_

#include "CosmicObject.hpp"
#include "math/Vector.hpp"
namespace brain
{
	namespace cosmic
	{
		/*!
		 * CosmicObject3D représente un CosmicObject dans un espace euclidien à 3 dimensions spatiales.
		 */
		class CosmicObject3D: public CosmicObject<Vector3D>
		{
			public:
				CosmicObject3D();
				CosmicObject3D(const CosmicObject3D& other);

				virtual ~CosmicObject3D();

				virtual CosmicObject3D& operator=(const CosmicObject3D& other);
		};
	}
}
#endif /* COSMICOBJECT3D_H_ */
