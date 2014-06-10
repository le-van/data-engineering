/*
 * pLSI.h
 *
 *  Created on: Jun 5, 2014
 *      Author: lehongvan
 */

#ifndef PLSI_H_
#define PLSI_H_

//=================================
// included dependencies
#include <iostream>
#include <random>
#include <fstream>

#include "Docs.h"
#include "Words.h"
#include "Factors.h"

using namespace std;
//=================================
// the actual class
class pLSI
{
public:
	Docs docs;
	Words words;
	Factors factors;
	void readDocsFile();
};




#endif /* PLSI_H_ */
