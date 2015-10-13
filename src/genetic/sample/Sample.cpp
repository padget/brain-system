/*
 * Sample.cpp
 *
 *  Created on: 10 mars 2014
 *      Author: Benjamin
 */

#include "Sample.h"
#include <random>
#include <chrono>
#include <array>
#include <list>

using namespace std;
using namespace std::chrono;

using namespace brain;
using namespace brain::genetic;

Population::Population() :
		IPopulation<Sample>()
{
}

Population::Population(unsigned initialesize) :
		IPopulation<Sample>(initialesize)
{
}

void Population::initiate()
{
	unsigned seed(system_clock::now().time_since_epoch().count());
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0, 1);

	Logger<Population>::debug("Population initiale : ");

	for (unsigned i = 0; i < m_initialsize; ++i)
	{
		Sample sample;
		array<int, 5> gen;

		for (unsigned i = 0; i < gen.size(); ++i)
		{
			gen[i] = distribution(generator);
		}

		sample.init(gen);
		m_samples.push_back(sample);
		Logger<Population>::debug(sample.str());
	}
}

bool Population::canbestopped()
{
	static unsigned stop = 0;
	stop++;

	unsigned added = 0;

	for (Sample& sample : m_samples)
	{
		for (int i : sample.gen())
		{
			added += i;
		}
	}

	if (added >= m_samples.size() * 5 || stop == 1)
	{
		Logger<Sample>::info("Je m'arrête là");
		return true;
	}
	else
	{
		Logger<Sample>::info(string("Je continue encore une génération"));
		return false;
	}
}

void Sample::init(std::array<int, 5>& gen)
{
	m_gen = gen;
}

std::array<int, 5>& Sample::gen()
{
	return m_gen;
}

void Population::reproduct()
{
	Sample* dad = nullptr;
	Sample* mum = nullptr;

	list<Sample> samples;
	std::array<int, 5> gen;

	for (Sample& sample : m_samples)
	{
		if (dad == nullptr)
		{
			dad = &sample;
			continue;
		}

		if (mum == nullptr)
		{
			if (dad != nullptr)
			{
				mum = &sample;
				Sample child;
				int cpt = 0;

				for (int& i : gen)
				{
					if (cpt < 3)
					{
						i = dad->gen()[cpt];
					}
					else
					{
						i = mum->gen()[cpt];
					}

					cpt++;
				}

				child.init(gen);
				samples.push_back(child);
				Logger<Population>::debug(
						string("reproduction : ") + dad->simplestr() + " avec " + mum->simplestr() + " donne : " + child.simplestr());
				mum = nullptr;
				dad = nullptr;
			}
		}
	}

	m_samples.insert(m_samples.end()++, samples.begin(), samples.end());
}

void Population::evaluate()
{
	for (Sample& sample : m_samples)
	{
		int score = 0;

		for (int i : sample.gen())
		{
			score += i;
		}

		sample.score((double) score);
	}
}

void Population::mute()
{
	static unsigned seed(system_clock::now().time_since_epoch().count());
	static default_random_engine generator(seed);

	unsigned size = m_samples.size() - 1 >= 0 ? m_samples.size() - 1 : 0;
	unsigned maxMutation = size * 5 / 100 + 1;

	uniform_int_distribution<unsigned> howManySample(0, maxMutation);
	Logger<Population>::trace(string("nb max mutation : ") + conv2str<int>()(maxMutation));

	unsigned nbMutatedSample = howManySample(generator);
	unsigned cpt1 = 0;

	while (cpt1 < nbMutatedSample)
	{
		uniform_int_distribution<unsigned> whichSample(0, size);
		unsigned choosedSample = whichSample(generator);
		unsigned cpt2 = 0;

		for (Sample& sample : m_samples)
		{
			if (cpt2 == choosedSample)
			{
				Sample mem = sample;

				uniform_int_distribution<unsigned> whichGen(0, sample.gen().size() - 1);
				unsigned choosedgen = whichGen(generator);
				int& value = sample.gen()[choosedgen];
				value = value == 1 ? 0 : 1;

				Logger<Population>::debug(
						string("mutation : ") + mem.simplestr() + " ==> " + sample.simplestr() + " sample[" + conv2str<int>()(choosedSample) + "] gen [" + conv2str<
								int>()(choosedgen) + "]");
			}

			cpt2++;
		}

		cpt1++;
	}
}

void Population::select()
{
	unsigned i = 0;

	for (Sample& sample : m_samples)
	{
		if (i >= m_initialsize)
		{
			break;
		}
		else
		{
			sample.selected(true);
		}

		++i;
	}
}

string Sample::str()
{
	conv2str<int> i2s;
	return string("[") + i2s(m_id) + "] " + i2s(gen()[0]) + i2s(gen()[1]) + i2s(gen()[2]) + i2s(gen()[3]) + i2s(gen()[4]) + " : age (" + i2s(
			age()) + "), score(" + conv2str<double>()(score()) + ")";
}

Sample::Sample() :
		ISample()
{
}

Sample::Sample(const Sample& other) :
		ISample(other),
		m_gen(other.m_gen)
{
}

Sample::~Sample()
{
}

Sample& Sample::operator =(const Sample& other)
{
	if (this != &other)
	{
		this->ISample::operator =(other);
		m_gen = other.m_gen;
	}

	return *this;
}

std::string Population::className()
{
	return string("Population");
}

void Population::help()
{
}

Population::~Population()
{
}

ISystem_sptr Population::clone()
{
	return ISystem_sptr(new Population(*this));
}

Sample::Sample(Sample&& other) :
		ISample(other),
		m_gen(move(other.m_gen))
{
}

Sample& Sample::operator =(Sample&& other)
{
	if (this != &other)
	{
		this->ISample::operator =(other);
		m_gen = move(other.m_gen);
	}

	return *this;
}

std::string Sample::simplestr()
{
	conv2str<int> i2s;
	return "[" + i2s(m_id) + "] " + i2s(gen()[0]) + i2s(gen()[1]) + i2s(gen()[2]) + i2s(gen()[3]) + i2s(gen()[4]);
}

