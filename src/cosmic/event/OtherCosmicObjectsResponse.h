/*
 * OtherCosmicObjectsResponse.h
 *
 *  Created on: 15 janv. 2014
 *      Author: Benjamin
 */

#ifndef OTHERCOSMICOBJECTSRESPONSE_H_
#define OTHERCOSMICOBJECTSRESPONSE_H_

#include "../../core.h"
#include "../CosmicObject.hpp"
#include "../math/Vector.hpp"
namespace brain
{
	namespace cosmic
	{
		/*!
		 * Cet évènement est émis en réponse à un OtherCosmicObjectsRequest
		 */
		class OtherCosmicObjectsResponse: public IEvent
		{
			public:
				inline OtherCosmicObjectsResponse(ISystem_sptr&& source) :
						IEvent(source)
				{
				}

				OtherCosmicObjectsResponse(const OtherCosmicObjectsResponse& other) = default;
				OtherCosmicObjectsResponse(OtherCosmicObjectsResponse&& other) = default;
				virtual ~OtherCosmicObjectsResponse() = default;

			public:
				OtherCosmicObjectsResponse& operator=(OtherCosmicObjectsResponse&& other) = default;
				OtherCosmicObjectsResponse& operator=(const OtherCosmicObjectsResponse& other) = default;
		};
	}
}
#endif /* OTHERCOSMICOBJECTSRESPONSE_H_ */
