/*
 * Docs.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: lehongvan
 */
#include "Docs.h"


void Docs::randomDocs(){
	// Random P(d|z)
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution_d(0,1);

	for (int i=0; i<Factors::NUMBER_OF_FACTORS; ++i) {
		for (int j=0; j<NUMBER_OF_DOCS; ++j) {
			Pdz[i][j] = distribution_d(generator);
//			cout << "z=" << i << " d=" << j << " Pdz=" << Pdz[i][j] << endl;
		}
	}
}


