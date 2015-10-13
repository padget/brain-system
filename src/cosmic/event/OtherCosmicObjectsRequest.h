/*
 * OtherCosmicObjectRequest.h
 *
 *  Created on: 15 janv. 2014
 *      Author: Benjamin
 */

#ifndef OTHERCOSMICOBJECTREQUEST_H_
#define OTHERCOSMICOBJECTREQUEST_H_
#include "../../core.h"
/*!
 * Cet évènement est émis lorsque la connaissance de CosmicObjects
 * est requise par l'émetteur.
 */
namespace brain
{
	namespace cosmic
	{
		class OtherCosmicObjectRequest: public IEvent
		{
			public:
				inline OtherCosmicObjectRequest(ISystem_sptr& source) :
						IEvent(source)
				{
				}

				OtherCosmicObjectRequest(const OtherCosmicObjectRequest& other) = default;
				OtherCosmicObjectRequest(OtherCosmicObjectRequest&& other) = default;
				virtual ~OtherCosmicObjectRequest() = default;

			public:
				OtherCosmicObjectRequest& operator=(OtherCosmicObjectRequest&& other) = default;
				OtherCosmicObjectRequest& operator=(const OtherCosmicObjectRequest& other) = default;
		};
	}
}

#endif /* OTHERCOSMICOBJECTREQUEST_H_ */
