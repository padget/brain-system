/*
 * CosmicEvent.h
 *
 *  Created on: 8 janv. 2014
 *      Author: bmathieu
 */

#ifndef COSMICEVENT_H_
#define COSMICEVENT_H_

#include "../../core.h"
namespace brain
{
	namespace cosmic
	{
		/*!
		 * Un TimeDtEvent signal qu'une unité de temps est passé.
		 */
		class TimeDtEvent: public IEvent
		{
			public:
				template <typename system>
				using t = std::enable_if_t<std::is_same<std::shared_ptr<ISystem>, std::remove_reference_t<system>>::value, system>;

				template <typename system, class = t<system>>
				inline TimeDtEvent(system&& source) :
						IEvent(source)
				{
				}

				TimeDtEvent(const TimeDtEvent& other) = default;
				TimeDtEvent(TimeDtEvent&& other) = default;
				virtual ~TimeDtEvent() = default;

			public:
				TimeDtEvent& operator=(TimeDtEvent&& other) = default;
				TimeDtEvent& operator=(const TimeDtEvent& other) = default;
		};
	}
}
#endif /* COSMICEVENT_H_ */
