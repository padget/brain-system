/*
 * ISample.h
 *
 *  Created on: 6 mars 2014
 *      Author: bmathieu
 */

#ifndef ISAMPLE_H_
#define ISAMPLE_H_
#include <string>
#include "../core.h"

namespace brain
{
	namespace genetic
	{

		class ISample: public IObject
		{
				double m_score;
				bool m_selected;
				unsigned m_age;

			protected:
				unsigned m_id;

			public:
				ISample();
				ISample(const ISample& other);
				ISample(ISample&& other);

				virtual ~ISample();

				ISample& operator=(ISample&& other);
				ISample& operator=(const ISample& other);

				void score(double score);
				double score();
				double score() const;

				void selected(bool selected);
				bool selected();
				bool selected() const;

				void age(unsigned age);
				unsigned age();
				unsigned age() const;
		};
	} /* namespace genetic */
}
#endif /* ISAMPLE_H_ */
