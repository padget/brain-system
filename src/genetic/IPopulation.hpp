/*
 * IGeneticProcessor.h
 *
 *  Created on: 6 mars 2014
 *      Author: bmathieu
 */

#ifndef IGENETICPROCESSOR_H_
#define IGENETICPROCESSOR_H_

#include "../core.h"
#include <list>
#include <algorithm>
#include <memory>

namespace brain
{
	namespace genetic
	{
		class NSGenetic
		{
		};

		typedef IEvent ReproductEvent;
		typedef IEvent MuteEvent;
		typedef IEvent SelectEvent;
		typedef IEvent SortEvent;
		typedef IEvent EvaluateEvent;
		typedef IEvent PurgeEvent;

		template <typename Sample>
		class IPopulation: public ISystem, public ISingleton<IPopulation<Sample>>
		{
			protected:
				std::list<Sample> m_samples;
				unsigned m_initialsize;
				unsigned long m_nbgeneration;

			public:
				IPopulation() :
						ISystem(),
						m_initialsize(0),
						m_nbgeneration(0)
				{
					auto&& freproduct([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.reproduct();});
					auto&& fmute([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.mute();});
					auto&& fevaluate([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.evaluate();});
					auto&& fselect([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.select();});
					auto&& fpurge([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.purge();});
					auto&& fsort([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.sort();});

					bind(typeid(ReproductEvent), freproduct);
					bind(typeid(MuteEvent), fmute);
					bind(typeid(EvaluateEvent), fevaluate);
					bind(typeid(SelectEvent), fselect);
					bind(typeid(PurgeEvent), fpurge);
					bind(typeid(SortEvent), fsort);
				}

				IPopulation(unsigned initialsize) :
						ISystem(),
						m_initialsize(initialsize),
						m_nbgeneration(0)
				{
					auto&& freproduct([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.reproduct();});
					auto&& fmute([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.mute();});
					auto&& fevaluate([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.evaluate();});
					auto&& fselect([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.select();});
					auto&& fpurge([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.purge();});
					auto&& fsort([](ISystem& s, std::shared_ptr<IEvent> e)
					{	Logger<IPopulation<Sample>>::info("Population");
						IPopulation<Sample>& pop = dynamic_cast<IPopulation<Sample>&>(s);
						pop.sort();});

					bind(typeid(ReproductEvent), freproduct);
					bind(typeid(MuteEvent), fmute);
					bind(typeid(EvaluateEvent), fevaluate);
					bind(typeid(SelectEvent), fselect);
					bind(typeid(PurgeEvent), fpurge);
					bind(typeid(SortEvent), fsort);
				}

				IPopulation(const IPopulation<Sample>& other) :
						ISystem(other),
						m_initialsize(other.m_initialsize),
						m_nbgeneration(0)
				{
				}

				IPopulation(IPopulation<Sample> && other) :
						ISystem(other),
						m_initialsize(other.m_initialsize),
						m_nbgeneration(0)
				{
				}

				virtual ~IPopulation()
				{
				}

				IPopulation<Sample>& operator =(const IPopulation<Sample>& other)
				{
					if (this != &other)
					{
						this->IObject::operator =(other);
						m_initialsize = other.m_initialsize;
						m_nbgeneration = 0;
					}

					return *this;
				}

				IPopulation<Sample>& operator =(IPopulation<Sample> && other)
				{
					if (this != &other)
					{
						this->IObject::operator =(other);
						m_initialsize = move(other.m_initialsize);
						m_nbgeneration = 0;
					}

					return *this;
				}

				std::list<Sample>& samples()
				{
					return m_samples;
				}

				void sort()
				{
					m_samples.sort([](const Sample& s1, const Sample& s2) -> bool
					{	return s1.score() > s2.score();});
				}

				void purge()
				{
					m_samples.remove_if([](const Sample& sample)->bool
					{	return !sample.selected();});

					for (Sample& sample : m_samples)
					{
						sample.selected(false);
						Logger<NSGenetic>::debug(sample.str());
					}
				}

				unsigned initialSize()
				{
					return m_initialsize;
				}

				unsigned initialSize() const
				{
					return m_initialsize;
				}

				virtual std::string str()
				{
					return "\n - Taille initiale : " + conv2str<unsigned>()(m_initialsize) + "\n - Taille          : " + conv2str<unsigned>()(
							m_samples.size()) + "\n - Génération      : " + conv2str<unsigned>()(m_nbgeneration);
				}

				void growold()
				{
					for (Sample& sample : m_samples)
					{
						sample.age(sample.age() + 1);
					}

					++m_nbgeneration;
				}

				void process()
				{
					initiate();

					do
					{
						std::shared_ptr<ReproductEvent> reproductEvent(new ReproductEvent(this));
						send(reproductEvent);
						std::shared_ptr<MuteEvent> muteEvent(new MuteEvent(this));
						send(muteEvent);
						std::shared_ptr<EvaluateEvent> evaluateEvent(new EvaluateEvent(this));
						send(evaluateEvent);
						std::shared_ptr<SortEvent> sortEvent(new SortEvent(this));
						send(sortEvent);
						std::shared_ptr<SelectEvent> selectEvent(new SelectEvent(this));
						send(selectEvent);
						std::shared_ptr<PurgeEvent> purgeEvent(new PurgeEvent(this));
						send(purgeEvent);

						growold();

						Logger<NSGenetic>::info(str());
					}
					while (!canbestopped());

					Logger<NSGenetic>::info(str());
				}

				virtual void run(const std::vector<std::string>& vec)
				{
					ISystem::run(vec);
					m_initialsize = 3;
					process();
				}

				virtual void initiate() = 0;
				virtual void mute() = 0;
				virtual void reproduct() = 0;
				virtual void evaluate() = 0;
				virtual void select() = 0;
				virtual bool canbestopped() = 0;
		};
	} /* namespace genetic */
}
#endif /* IGENETICPROCESSOR_H_ */
