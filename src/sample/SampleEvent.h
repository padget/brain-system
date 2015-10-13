/*
 * SampleEvent.h
 *
 *  Created on: 7 janv. 2014
 *      Author: bmathieu
 */

#ifndef SAMPLEEVENT_H_
#define SAMPLEEVENT_H_

#include "../core.h"
namespace brain
{
	class SampleEvent: public event
	{
		public:
			inline SampleEvent(isystem_sptr&& source) :
					event(source)
			{
			}

			inline SampleEvent(isystem_sptr& source) :
					event(source)
			{
			}

			SampleEvent(const SampleEvent& other) = default;
			SampleEvent(SampleEvent&& other) = default;
			virtual ~SampleEvent() = default;

		public:
			SampleEvent& operator=(const SampleEvent& other) = default;
			SampleEvent& operator=(SampleEvent&& other) = default;
	};
}
#endif /* SAMPLEEVENT_H_ */
