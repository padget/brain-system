/*
 * ISample.cpp
 *
 *  Created on: 6 mars 2014
 *      Author: bmathieu
 */

#include "ISample.h"

using namespace std;

using namespace brain;
using namespace brain::genetic;

ISample::ISample() :
		IObject(),
		m_score(0),
		m_selected(false),
		m_age(0)

{
	static unsigned cpt = 0;
	cpt++;
	m_id = cpt;
}

ISample::ISample(const ISample& other) :
		IObject(other),
		m_score(other.m_score),
		m_selected(other.m_selected),
		m_age(other.m_age),
		m_id(other.m_id)
{
}

ISample::~ISample()
{
}

ISample& ISample::operator =(const ISample& other)
{
	if (this != &other)
	{
		this->IObject::operator =(other);
		m_score = other.m_score;
		m_selected = other.m_selected;
		m_age = other.m_age;
		m_id = other.m_id;
	}

	return *this;
}

void ISample::score(double score)
{
	m_score = score;
}

double ISample::score()
{
	return m_score;
}

void ISample::selected(bool selected)
{
	m_selected = selected;
}

double ISample::score() const
{
	return m_score;
}

bool ISample::selected()
{
	return m_selected;
}

bool ISample::selected() const
{
	return m_selected;
}

void ISample::age(unsigned age)
{
	m_age = age;
}

unsigned ISample::age()
{
	return m_age;
}

unsigned ISample::age() const
{
	return m_age;
}

ISample::ISample(ISample&& other) :
		IObject(other),
		m_score(move(other.m_score)),
		m_selected(move(other.m_selected)),
		m_age(move(other.m_age)),
		m_id(move(other.m_id))
{
}

ISample& ISample::operator =(ISample&& other)
{
	if (this != &other)
	{
		this->IObject::operator =(other);
		m_score = move(other.m_score);
		m_selected = move(other.m_selected);
		m_age = move(other.m_age);
		m_id = move(other.m_id);
	}

	return *this;
}
