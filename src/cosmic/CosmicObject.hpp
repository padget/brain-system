/*
  Type 'std::string' could not be resolved * CosmicObject.h
  *
  *  Created on: 8 janv. 2014
  *      Author: bmathieu
  */

 #ifndef COSMICOBJECT_H_
#define COSMICOBJECT_H_

#include "../core.h"
#include <type_traits>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <sstream>
#include "event/TimeDtEvent.h"
namespace brain
{
    namespace cosmic
    {
		void timedtevent(ISystem& s, std::shared_ptr<IEvent> e);

		/*!
		 * Un CosmicObject est un object quelconque de l'espace qui possède une masse et un rayon.
		 * Le rayon est une approximation du volume réel de l'objet car celui n'est pas nécessairement
		 * sphérique. Malgré tout, à l'échelle cosmologique, la plupart des objets sont soit des sphères,
		 * soit des disques. Donc l'approximation est semble-t-il correcte.
		 */
		template <typename Vector>
		class CosmicObject: public ISystem
		{
			double m_mass;
			double m_radius;
			Vector m_coordinates;
			Vector m_celerity;

		public:
			CosmicObject() :
				ISystem(),
				m_mass(0.0),
				m_radius(0.0)
			{
				bind(typeid(TimeDtEvent), timedtevent);
			}

			CosmicObject(double mass, double radius, Vector& coordinates, Vector& celerity) :
				ISystem(),
				m_mass(mass),
				m_radius(radius),
				m_coordinates(coordinates),
				m_celerity(celerity)
			{
				bind(typeid(TimeDtEvent), timedtevent);
			}

			CosmicObject(double mass, double radius,
						 std::array<double, Vector::m_size> coordinates,
						 std::array<double, Vector::m_size> celerity) :
				ISystem(),
				m_mass(mass),
				m_radius(radius),
				m_coordinates(coordinates),
				m_celerity(celerity)
			{
				bind(typeid(TimeDtEvent), timedtevent);
			}

			CosmicObject(const CosmicObject& other) :
				ISystem(other),
				m_mass(other.m_mass),
				m_radius(other.m_radius),
				m_coordinates(other.m_coordinates),
				m_celerity(other.m_celerity)
			{
				bind(typeid(TimeDtEvent), timedtevent);
			}

			virtual ~CosmicObject()
			{
			}

			virtual CosmicObject& operator=(const CosmicObject& other)
			{
				if (this != &other)
				{
					this->ISystem::operator =(other);
					m_mass = other.m_mass;
					m_radius = other.m_radius;
					m_coordinates = other.m_coordinates;
					m_celerity = other.m_celerity;
				}

				return (*this);
			}

			double mass()
			{
				return m_mass;
			}
			void mass(double mass)
			{
				m_mass = mass;
			}

			double radius()
			{
				return m_radius;
			}

			void radius(double radius)
			{
				m_radius = radius;
			}

			Vector& coordinates()
			{
				return m_coordinates;
			}

			Vector& celerity()
			{
				return m_celerity;
			}

			virtual void run(const std::vector<std::string>& args)
			{
				if (args.size() == 2 + Vector::size() * 2)
				{
					std::istringstream ssmass(args[0]);
					ssmass >> m_mass;

					std::istringstream ssradius(args[1]);
					ssradius >> m_radius;

					for (unsigned i = 0; i < Vector::size(); ++i)
					{
						std::istringstream sscoordinates(args[2 + i]);
						sscoordinates >> m_coordinates.coordinates()[i];
					}

					for (unsigned i = 0; i < Vector::size(); ++i)
					{
						std::istringstream sscelerity(args[2 + Vector::size() + i]);
						sscelerity >> m_celerity.coordinates()[i];
					}

					ISystem::run(args);
				}
				else
				{
					Logger<CosmicObject<Vector>>::warn(
						"Les arguments du CosmicObject ne sont pas corrects : ");
					help();
				}

				std::shared_ptr<cosmic::TimeDtEvent> e{new TimeDtEvent(shared_conv<ISystem>(this->shared_from_this()))};
				send(e);
			}

			virtual std::string className()
			{
				std::ostringstream oss;
				oss << Vector::size() << "D";
				return std::string("CosmicObject") + oss.str();
			}

			virtual void help()
			{
				Logger<CosmicObject<Vector>>& logger = Logger<CosmicObject<Vector>>::single();
				logger.info("############# COSMIC OBJECT HELP ###########");
				logger.info(
					" Pour utiliser ce ISystem c'est CosmicObject + <Dimension du repère spatial>");
				logger.info(" ex : CosmicObject3");
				logger.info("");
				logger.info(" Pour lancer ce ISystem, les arguments sont les suivants :");
				logger.info(
					" mass (double), rayon (double), ... coordonnées (doubles), ... vitesse (doubles)");
				logger.info(
					" /!\\ Les vecteurs doivent être de même dimension que celui du CosmicObject<N>D");
				logger.info("############################################");
			}

			virtual ISystem_sptr clone()
			{
				return ISystem_sptr(new CosmicObject<Vector>(*this));
			}
		};
    }
}
#endif /* COSMICOBJECT_H_ */
