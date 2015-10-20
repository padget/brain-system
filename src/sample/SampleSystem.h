#ifndef SAMPLESYSTEM_H_
#define SAMPLESYSTEM_H_

#include "../core.h"
#include <string>
#include "SampleEvent.h"

namespace brain
{
	class SampleSystem:
	    public system
	{
		public:
			SampleSystem() noexcept;
			SampleSystem(const SampleSystem& other) = default;
			SampleSystem(SampleSystem&& other) noexcept= default;
			virtual ~SampleSystem() noexcept= default;

			virtual SampleSystem& operator=(const SampleSystem& other) noexcept= default;
			virtual SampleSystem& operator=(SampleSystem&& other) noexcept= default;
			std::string className();
			void help();

			virtual isystem_sptr clone() ;
	};
}

#endif /* SAMPLESYSTEM_H_ */
