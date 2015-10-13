/*
 * Sample.h
 *
 *  Created on: 10 mars 2014
 *      Author: Benjamin
 */

#ifndef SAMPLE_H_2
#define SAMPLE_H_2

#include "../ISample.h"
#include "../IPopulation.hpp"
#include <string>
#include <array>
namespace brain
{
	namespace genetic
	{
		class Sample;

		class Population: public IPopulation<Sample>
		{
			public:
				Population();
				Population(unsigned initialesize);
				~Population();

				virtual void initiate();
				virtual void mute();
				virtual void reproduct();
				virtual void evaluate();
				virtual void select();
				virtual bool canbestopped();

				virtual std::string className();
				virtual void help();
				virtual ISystem_sptr clone();
		};

		class Sample: public ISample
		{
				std::array<int, 5> m_gen;

			public:
				Sample();
				Sample(const Sample& other);
				Sample(Sample&& other);
				virtual ~Sample();

				Sample& operator=(const Sample& other);
				Sample& operator=(Sample&& other);
				void init(std::array<int, 5>& gen);

				std::array<int, 5>& gen();
				std::string str();
				std::string simplestr();
		};
	} /* namespace genetic */
}
#endif /* SAMPLE_H_ */
