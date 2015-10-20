/*
 * Vector.h
 *
 *  Created on: 8 janv. 2014
 *      Author: Benjamin
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <array>
#include <cmath>
namespace brain
{
	namespace cosmic
	{
		template <typename literal, unsigned vecSize>
		class Vector
		{
			typedef literal type;

			protected:
				std::array<literal, vecSize> m_coordinates;

			public:
				static const unsigned m_size = vecSize;

				Vector(std::array<literal, vecSize> coordinates = { }) :
						m_coordinates(coordinates)
				{
				}

				Vector(const Vector<literal, vecSize>& other) :
						m_coordinates(other.m_coordinates)
				{
				}

				Vector(Vector<literal, vecSize> && other) :
						m_coordinates(std::move(other.m_coordinates))
				{
				}

				Vector<literal, vecSize>& operator=(const Vector<literal, vecSize>& other)
				{
					if (this != &other)
					{
						m_coordinates = other.m_coordinates;
					}

					return (*this);
				}

				Vector<literal, vecSize>& operator=(Vector<literal, vecSize>&& other)
				{
					if (this != &other)
					{
						m_coordinates = std::move(other.m_coordinates);
					}

					return (*this);
				}

				static constexpr unsigned size()
				{
					return m_size;
				}

				std::array<literal, vecSize>& coordinates()
				{
					return m_coordinates;
				}

				/*!
				 * Calcule la norme d'un vecteur.
				 * @return la valeur de la norme du vecteur
				 */
				double norm()
				{
					literal norm = 0.0;

					for (int i = 0; i < m_size; ++i)
					{
						norm += m_coordinates[i] * m_coordinates[i];
					}

					return std::sqrt(norm);
				}
		};

		typedef Vector<double,2> Vector2D;
		typedef Vector<double,3> Vector3D;
		typedef Vector<double,4> Vector4D;
		typedef Vector<double,5> Vector5D;
		typedef Vector<double,6> Vector6D;
		typedef Vector<double,7> Vector7D;
		typedef Vector<double,8> Vector8D;
		typedef Vector<double,9> Vector9D;
		typedef Vector<double,10> Vector10D;
		typedef Vector<double,11> Vector11D;
		typedef Vector<double,12> Vector12D;
		typedef Vector<double,13> Vector13D;
		typedef Vector<double,14> Vector14D;
		typedef Vector<double,15> Vector15D;
		typedef Vector<double,16> Vector16D;
	}
}
#endif /* VECTOR_H_ */
