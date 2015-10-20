/*
 * Const.h
 *
 *  Created on: 8 janv. 2014
 *      Author: bmathieu
 */

#ifndef CONST_H_
#define CONST_H_
/*!
 * Normes des unités :
 *  - distance en m
 *  - masse en kg
 *  - gravité en m3 kg-1 s-2
 *  - temps en s
 *  - force en N (kg m s-2)
 */
namespace brain
{
	namespace cosmic
	{
		class Newton
		{
			public:
				/*! Constante de la gravité universelle en m3 kg-1 s-2*/
				static constexpr double G = 6.6742e-11;
		};

		class Galilee
		{
			public:
				/*! Constante de la gravité terrestre en m s-2*/
				static constexpr double g = 9.81;
		};

		class Einstein
		{
		};

		class Earth
		{
			public:
				/*! Masse de la Terre */
				static constexpr double mass = 5.972e24;
				/*! Rayon équatorial de la Terre */
				static constexpr double radius = 6371e3;

		};

		class Sun
		{
			public:
				/*! Masse du soleil */
				static constexpr double mass = 1.989e30;
				/*! Rayon équatorial du soleil */
				static constexpr double radius = 695500e3;
		};

		class StdDist
		{
			public:
				/*! Distance Terre - Soleil : Unité Astronomique */
				static constexpr double UA = 149.600000e9;
				/*! Distance parcouru par la lumière en un an : Année Lumière */
				static constexpr double al = 9460730472580.8e3;
		};
	}
}
#endif /* CONST_H_ */
