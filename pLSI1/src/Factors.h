/*
 * Factors.h
 *
 *  Created on: Jun 5, 2014
 *      Author: lehongvan
 */

//=================================
// include guard
#ifndef FACTORS_H_
#define FACTORS_H_

//=================================
// included dependencies
#include <map>
#include <random>
//=================================
// the actual class
class Factors
{
public:
	const static int NUMBER_OF_FACTORS = 16;			// number of latent factors
	double Pz[NUMBER_OF_FACTORS]={};	// probability of factors
	void randomFactors();

};

#endif /* FACTORS_H_ */
