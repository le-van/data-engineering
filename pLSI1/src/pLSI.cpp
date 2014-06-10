//============================================================================
// Name        : pLSI1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "pLSI.h"

//*************** Read File ***************//
void pLSI::readDocsFile() {
	string line;
	int line_count = 0;

	ifstream myfile ("/Users/lehongvan/Documents/workspace2/pLSI1/src/docs.txt");
	if (myfile.is_open()) {
		while (getline (myfile,line) && line_count<Docs::NUMBER_OF_DOCS)
		{
//			cout << line_count << endl;
			string word;
			int d_index;
			map<int,int> w_freq;
			for (string::iterator it=line.begin(); it!=line.end(); ++it)
			{
				if(*it == '\t')
				{
					d_index = atoi(word.c_str());
					word = "";
//					cout << d_index << endl;
				}
				else if(*it == ' ')
				{
					int word_index = atoi(word.c_str());
					//First time the word is seen in this document
					map<int,int>::iterator w_it = w_freq.find(word_index);
				    if(w_it == w_freq.end())
				    {
//			        	cout << word_index << endl;
				        w_freq.insert(pair<int, int>(word_index, 1));
				    }
				    else //The word has been seen before
				    {
//			        	 cout << word_index << endl;
				        w_freq.insert(pair<int, int>(word_index, w_it->second++));
				    }

				    //First time the word is seen in all documents
				    if(find(words.w_list.begin(), words.w_list.end(), word_index) == words.w_list.end())
				    {
				    	words.w_list.push_back(word_index);
				    }
				    word = "";
				}
				else
				{
				    word.push_back(*it);
				}
			}
//			cout << d_index << endl;
			docs.d_list.insert(pair<int, map<int, int>>(d_index, w_freq));
//			d_list.assign(d_index);
			line_count++;
		}
		myfile.close();

		words.NUMBER_OF_WORDS = words.w_list.size();

	//		for (map<int, map<int, int>>::const_iterator i = d_list.begin(); i != d_list.end(); i++)
	//		{
	//			for (map<int, int>::const_iterator j = i->second.begin(); j != i->second.end(); j++)
	//			{
	//				cout << "d=" << i->first << " w=" << j->first << " d_list=" << j->second << endl;
	//			}
	//		}
	//	    typedef map<int, int>::const_iterator MapIterator;
	//	    for (MapIterator iter = w_freq.begin(); iter != w_freq.end(); iter++)
	//	    {
	//	        cout << "Key: " << iter->first << endl << "Values:" << iter->second << endl;
	//	    }
	}
	else cout << "Unable to open file";

		for ( int i = 0; i < docs.d_list.size(); i++) {
			// loop for words
			for (map<int, int>::const_iterator j = docs.d_list[i].begin(); j != docs.d_list[i].end(); j++) {
	//			cout << "d=" << i << " w=" << j->first << " d_list=" << j->second << endl;
			}
		}
}
