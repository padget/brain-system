/*
 * Math.hpp
 *
 *  Created on: 10 janv. 2014
 *      Author: bmathieu
 */

#ifndef MATH_UTILS_HPP_
#define MATH_UTILS_HPP_

#include "../../core.h"
#include "const.h"

#include <cmath>
#include <vector>
#include <functional>

namespace brain
{
	namespace cosmic
	{
		class Time
		{
			public:
				/*! Temps unitaire en seconde pris*/
				static constexpr double dt = 1.0;
		};

		template <typename Vector>
		class Binary
		{
			public:
				/*!
				 * Calcule la somme de deux vecteurs
				 * @param a Vecteur A
				 * @param b Vecteur B
				 * @return Le vecteur résultant de la somme de a+b
				 */
				static Vector add(Vector& a, Vector& b)
				{
					Vector add;

					for (int i = 0; i < Vector::m_size; ++i)
					{
						add.coordinates()[i] = a.coordinates()[i] + b.coordinates()[i];
					}

					return add;
				}

				/*!
				 * Calcule la différence de deux vecteurs
				 * @param a Vecteur A
				 * @param b Vecteur B
				 * @return Le vecteur résultant de la différence de a-b
				 */
				static Vector minus(Vector& a, Vector& b)
				{
					Vector minus;

					for (int i = 0; i < Vector::m_size; ++i)
					{
						minus.coordinates()[i] = a.coordinates()[i] + b.coordinates()[i];
					}

					return minus;
				}
		};

		template <typename Vector>
		class Dist
		{
			public:
				/*!
				 * Calcule la distance cartésienne dans un espace à N dimension.
				 * @param a Point A
				 * @param b Point B
				 * @return Distance entre le A et B en m
				 */
				static typename Vector::type dist(CosmicObject<Vector>& a, CosmicObject<Vector>& b)
				{
					Vector& vecA = a.coordinates();
					Vector& vecB = b.coordinates();

					for (int i = 0; i < Vector::m_size; ++i)
					{
						typename Vector::type diff = vecA.coordinates()[i] - vecB.coordinates()[i];
						dist += diff * diff;
					}

					return std::sqrt(dist);
				}
		};

		template <typename Vector>
		class Gravity
		{
			public:
				/*!
				 * Calcule la force de gravité entre deux objets dans un espace à N dimension.
				 * @param a Objet A
				 * @param b Objet B
				 * @return La force de gravité entre A et B en N ( = kg.m.s-2)
				 */
				static typename Vector::type gravity(CosmicObject<Vector>& a, CosmicObject<Vector>& b)
				{
					typename Vector::type dist = Dist<Vector>::dist(a, b);
					return Newton::G * a.mass() * b.mass() / (dist * dist);
				}

				/*!
				 * Calcule le champs gravitationnel en un point de l'espace d'un objet a sur un objet b
				 * @param a Objet A
				 * @param dist Distance considérée pour le calcul
				 * @return la valeur du champs gravitationnel de a sur b en m.s-2 (accélération de a sur b)
				 */
				static typename Vector::type gravitationalfield(CosmicObject<Vector>& a, double dist)
				{
					return Newton::G * a.mass() / (dist * dist);
				}

				/*!
				 * Calcule la vitesse d'échappement pour que l'objet B puisse se défaire de l'attraction
				 * gravitationelle de l'objet A.
				 * @param a Objet A
				 * @param dist distance considérée pour le calcul
				 * @return La vitesse d'échappement en m.s-1
				 */
				static typename Vector::type escapeVelocity(CosmicObject<Vector>& a, double dist)
				{
					return std::sqrt(2 * Newton::G * a.mass() / dist);
				}
		};

		typedef Gravity<Vector3D> Gravity3D;
		typedef Gravity<Vector3D> Gravity2D;

		template <typename Vector>
		class Celerity
		{
			public:
				/*!
				 * Calcule le vecteur vitesse en fonction de deux vecteurs de coordonnées spatiale.
				 * @param A Vecteur spatial A
				 * @param B Vecteur spatial B
				 * @return Le vecteur vitesse
				 */
				static Vector celerity(Vector& A, Vector& B)
				{
					Vector celerity;

					for (int i = 0; i < Vector::m_size; ++i)
					{
						celerity.coordinates()[i] =
								(A.coordinates()[i] - B.coordinates()[i]) / Time::dt;
					}

					return celerity;
				}

				static Vector toCoordinates(Vector& celerity, Vector& coordNminus1)
				{
					Vector coordinate;

					for (int i = 0; i < Vector::m_size; ++i)
					{
						coordinate.coordinates()[i] =
								celerity.coordinates()[i] * Time::dt + coordNminus1.coordinates()[i];
					}

					return coordinate;
				}
		};

		template <typename Vector>
		class Acceleration
		{
			public:
				/*!
				 * Calcule le vecteur accélération en fonction de deux vecteurs vitesse.
				 * @param A Vecteur vitesse A
				 * @param B Vecteur vitesse B
				 * @return Le vecteur accélération
				 */
				static Vector acceleration(Vector& A, Vector& B)
				{
					Vector acceleration;

					for (int i = 0; i < Vector::m_size; ++i)
					{
						acceleration.coordinates()[i] =
								(A.coordinates()[i] - B.coordinates()[i]) / Time::dt;
					}

					return acceleration;
				}

				static Vector toCelerity(Vector& acc, Vector& vNminus1)
				{
					Vector celerity;

					for (int i = 0; i < Vector::m_size; ++i)
					{
						celerity.coordinates()[i] = acc.coordinates()[i] * Time::dt + vNminus1
								.coordinates()[i];
					}

					return celerity;
				}
		};

		namespace math
		{
			template <typename T>
			class Set
			{
					std::vector<T> m_data;

				public:
					bool contains(T& t)
					{
						return true;
					}

					typename std::vector<T>::iterator begin() noexcept
					{
						return m_data.begin();
					}

					typename std::vector<T>::const_iterator begin() const noexcept
					{
						return m_data.begin();
					}

					typename std::vector<T>::iterator end() noexcept
					{
						return m_data.end();
					}

					typename std::vector<T>::const_iterator end() const noexcept
					{
						return m_data.end();
					}
			};

			template <typename T>
			class Structure
			{
					Set<T> m_set;

					T m_addneutral;
					T m_multneutral;

					std::function<T(T, T)> m_addlow;
					std::function<T(T, T)> m_multlow;

				public:
					Structure()
					{
					}

					Structure(const Set<T>& set, std::function<T(T, T)>& addlow) :
							m_set(set),
							m_addlow(addlow)
					{
					}

					Structure(const Set<T>& set, std::function<T(T, T)>& addlow,
							std::function<T(T, T)>& multlow) :
							m_set(set),
							m_addlow(addlow),
							m_multlow(multlow)
					{
					}

					virtual ~Structure()
					{
					}

					bool isGroup()
					{
						bool result = true;

						//Composition interne
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								result &= m_set.contains(m_addlow(a, b));
							}
						}

						//Associativité
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								for (T& c : m_set)
								{
									result &= m_addlow(m_addlow(a, b), c) == m_addlow(a,
											m_addlow(b, c));
								}
							}
						}

						//Element neutre
						T* neutral = nullptr;

						for (T& a : m_set)
						{
							if (!result)
							{
								break;
							}

							bool exist = false;

							for (T& e : m_set)
							{
								exist |= m_addlow(a, e) == a && m_addlow(e, a) == a;

								if (exist)
								{
									if (neutral != nullptr && neutral != &e)
									{
										return false;
									}
									else
									{
										neutral = &e;
									}
								}
							}

							result &= exist;
						}

						//Symétrie
						if (neutral != nullptr)
						{
							for (T& a : m_set)
							{
								bool exist = false;

								for (T& b : m_set)
								{
									exist |=
											m_addlow(a, b) == *neutral && m_addlow(b, a) == *neutral;
								}

								result &= exist;
							}
						}
						else
						{
							return false;
						}

						return result;
					}

					bool isCommutativGroup()
					{
						bool result = true;

						result &= isGroup();

						//Commutatif
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								result &= m_addlow(a, b) == m_addlow(b, a);
							}
						}

						return result;
					}

					bool isRing()
					{
						bool result = true;
						result &= isCommutativGroup();

						//Associatif
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								for (T& c : m_set)
								{
									result &= m_multlow(a, m_multlow(b, c)) == m_multlow(
											m_multlow(a, b), c);
								}
							}
						}

						//Distributif
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								for (T& c : m_set)
								{
									result &= m_multlow(a, m_addlow(b, c)) == m_addlow(
											m_multlow(a, b), m_multlow(b, c));
								}
							}
						}

						return result;
					}

					bool isCommutativRing()
					{
						bool result = true;

						result &= isRing();

						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								result &= m_multlow(a, b) == m_multlow(b, a);
							}
						}

						return result;
					}

					bool isCorps()
					{
						bool result = true;

						result &= isRing();

						//Composition interne
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								result &= m_set.contains(m_multlow(a, b));
							}
						}

						//Associativité
						for (T& a : m_set)
						{
							for (T& b : m_set)
							{
								for (T& c : m_set)
								{
									result &= m_multlow(m_multlow(a, b), c) == m_multlow(a,
											m_multlow(b, c));
								}
							}
						}

						//Element neutre
						T* neutral = nullptr;

						for (T& a : m_set)
						{
							if (!result)
							{
								break;
							}

							bool exist = false;

							for (T& e : m_set)
							{
								exist |= m_multlow(a, e) == a && m_multlow(e, a) == a;

								if (exist)
								{
									if (neutral != nullptr && neutral != &e)
									{
										return false;
									}
									else
									{
										neutral = &e;
									}
								}
							}
						}

						return result;
					}

					bool isCommutativCorps()
					{
						bool result = true;

						result &= isCorps();

						return result;
					}

			}
			;

			class Tensor
			{
			};
		}
	}
}
#endif /* MATH_HPP_ */
