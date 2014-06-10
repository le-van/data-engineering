/*
 * Factors.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: lehongvan
 */

#include "Factors.h"

void Factors::randomFactors() {
	// Random P(z)
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution_z(0,1);

	int Z[Factors::NUMBER_OF_FACTORS]={};
	double z_total = 0;
	for (int i=0; i<Factors::NUMBER_OF_FACTORS; ++i) {
	    double z_random = distribution_z(generator);

	    z_total += z_random;
	    Z[i] = z_random;
	}


	for (int i=0; i<Factors::NUMBER_OF_FACTORS; ++i) {
		Pz[i] = Z[i]/z_total;
//	    cout << "z=" << i << " Pz=" << Pz[i] << endl;
	}
}


