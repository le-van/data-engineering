/*
 * Docs.h
 *
 *  Created on: Jun 5, 2014
 *      Author: lehongvan
 */


//=================================
// include guard
#ifndef DOCS_H_
#define DOCS_H_

//=================================
// included dependencies
#include <map>
#include <random>

#include "Factors.h"
using namespace std;
//=================================
// the actual class
class Docs
{
public:
	const static int NUMBER_OF_DOCS = 19097;  	// number of documents
	map<int, map<int,int>> d_list;		// map of docs with key: id of doc, value: map of words and word frequency

	double Pdz[Factors::NUMBER_OF_FACTORS][NUMBER_OF_DOCS]={};
	void randomDocs();
};



#endif /* DOCS_H_ */
