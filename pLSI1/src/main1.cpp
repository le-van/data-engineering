/*
 * main.cpp
 *
 *  Created on: May 30, 2014
 *      Author: lehongvan
 */
#include <iostream>
#include <random>
#include <map>
#include <fstream>
using namespace std;

int main() {
	const int z=16;		// number of latent factors
	const int d=19097;  // number of documents
	int w=0;    		// number of words
	const int round=10; // number of EM rounds
	vector<int> w_list;
	map<int, map<int,int> > d_list;

	//*************** Read File ***************//
	string line;
	int line_count = 0;

	time_t start;
	time(&start);

	ifstream myfile ("/Users/lehongvan/Documents/workspace2/pLSI1/src/docs.txt");
	if (myfile.is_open()) {
		while (getline (myfile,line) && line_count<d) {
			cout << line << endl;
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
				else if(*it == ' ' || it+1 == line.end())
			    {
					if (it+1 == line.end()) word.push_back(*it);
					int word_index = atoi(word.c_str());

					//First time the word is seen in this document
					map<int,int>::iterator w_it = w_freq.find(word_index);
			         if(w_it == w_freq.end())
			         {
			        	 cout << word_index << endl;
			        	 w_freq.insert(pair<int, int>(word_index, 1));
			         }
			         else //The word has been seen before
			         {
//			        	 cout << word_index << endl;
			        	 w_freq.insert(pair<int, int>(word_index, w_it->second++));
			         }

			         //First time the word is seen in all documents
			         if(find(w_list.begin(), w_list.end(), word_index) == w_list.end())
			         {
			        	 w_list.push_back(word_index);
			         }
			         word = "";
			    }
			    else
			    {
			         word.push_back(*it);
			    }
			}
//			cout << d_index << endl;
			d_list.insert(pair<int, map<int, int> >(d_index, w_freq));
//			d_list.assign(d_index);
			line_count++;
	    }
	    myfile.close();

	    w = w_list.size();

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

	for ( int i = 0; i < d_list.size(); i++) {
		// loop for words
		for (map<int, int>::const_iterator j = d_list[i].begin(); j != d_list[i].end(); j++) {
//			cout << "d=" << i << " w=" << j->first << " d_list=" << j->second << endl;
		}
	}

//	sort(w_list.begin(), w_list.end());
//	for ( int i = 0; i < w_list.size(); i++) {
//		cout << "i= " << i << " " << w_list[i]-i << endl;
//	}

	//*************** Initialize ***************//
	// Assign probability distributions, P(z), P(d|z), and P(w|z) randomly


	// Random P(z)
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution_z(0,z);

	int Z[z]={};
	double z_total = 0;
	for (int i=0; i<z; ++i) {
	    int z_random = distribution_z(generator);

	    z_total += z_random;
	    Z[i] = z_random;
	}

	double Pz[z]={};
	for (int i=0; i<z; ++i) {
	    Pz[i] = Z[i]/z_total;
//	    cout << "z=" << i << " Pz=" << Pz[i] << endl;
	}

	// Random P(d|z)
	std::uniform_int_distribution<int> distribution_d(0,d);

	double Pdz[z][d]={};
	for (int i=0; i<z; ++i) {
		for (int j=0; j<d; ++j) {
			int d_random = distribution_d(generator);
			Pdz[i][j] = (double)d_random/d;
//			cout << "z=" << i << " d=" << j << " Pdz=" << Pdz[i][j] << endl;
		}
	}

	// Random P(w|z)
	std::uniform_int_distribution<int> distribution_w(0,w);

	map<int, double> Pwz[z]={};

	cout << w << endl;
	for (int i=0; i<z; ++i) {
	    map<int, double> w_map;
	    for (int j = 0; j < w_list.size(); j++)
		{
			int w_random = distribution_w(generator);
			w_map.insert(pair<int, double> (w_list[j], (double)w_random/w));
//			cout << "z=" << i << " w=" << w_list[j] << " Pwz=" << random << endl;
		}
		Pwz[i] = w_map;
	}

//	for (int i=0; i<z; ++i) {
//		for (map<int, double>::const_iterator j = Pwz[i].begin(); j != Pwz[i].end(); j++) {
//			cout << " z: " << i << " w: " << j->first << " value: " << (double)j->second << endl;
//		}
//	}

	//*************** EM ***************//
	for (int r=0; r<round; ++r) {

		//*************** E step ***************//
		vector<map <int, double> > Pwdz[z]={};
		for (int k=0; k<z; ++k) {
			vector<map <int, double> > z_vector;
			// loop for documents
			for (map<int, map<int, int> >::const_iterator i = d_list.begin(); i != d_list.end(); i++) {
//			for ( int i = 0; i < d_list.size(); i++) {
				map <int, double> w_map;
				// loop for words
				for (map<int, int>::const_iterator j = i->second.begin(); j != i->second.end(); j++) {
//				for ( int j = 0; j < d_list[i].size(); j++) {
					double Pzx = Pz[k] * Pdz[k][i->first] * Pwz[k].find(j->first)->second;
					w_map.insert(pair<int, double>(j->first, Pzx));

//					cout << " z: " << k << " d: " <<  i->first << " w: " << j->first << " Pwdz: " << Pzx << endl;
				}
				z_vector.push_back(w_map);
			}
			Pwdz[k] = z_vector;
		}



		//*************** M step ***************//
		for (int k=0; k<z; ++k) {
			Pz[k] = 0;
			//calculate Pdz
			// loop for documents
//			for ( int i = 0; i < d_list.size(); i++) {
			for (map<int, map<int, int> >::const_iterator i = d_list.begin(); i != d_list.end(); i++) {
				Pdz[k][i->first] = 0;
				// loop for words
//				for (map<int, int>::const_iterator j = d_list[i].begin(); j != d_list[i].end(); j++) {
				for (map<int, int>::const_iterator j = i->second.begin(); j != i->second.end(); j++) {
					Pdz[k][i->first] += j->second * Pwdz[k][i->first].find(j->first)->second;
//					cout << "z=" << k << " d=" << i->first << " w=" << j->first << " d_list=" << j->second << " Pdwz= " << Pwdz[k][i->first][j->first] << endl;
				}
//				cout << "z=" << k << " d=" << i->first << " Pdz= " << Pdz[k][i->first] << endl;

				//calculate Pz
				Pz[k] += Pdz[k][i->first];
			}

//			cout << "round=" << r << " z=" << k << " Pz=" << Pz[k] << endl;

			//calculate Pwz
			// loop for words
			for ( int j = 0; j < w_list.size(); j++) {
				double Pwz_new = 0;
				// loop for documents
//				for ( int i = 0; i < d_list.size(); i++) {
				for (map<int, map<int, int> >::const_iterator i = d_list.begin(); i != d_list.end(); i++) {
					if (i->second.find(w_list[j]) != i->second.end()){
						map<int, int>::const_iterator w_found = i->second.find(w_list[j]);
						Pwz_new += w_found->second * Pwdz[k][i->first].find(w_found->first)->second;
//						cout << "Pwz z=" << k << " d=" << i->first << " w=" << w_list[j] << " d_list=" << w_found->second << " Pdwz= " << Pwdz[k][i->first].find(w_found->first)->second << endl;
					}
				}
				Pwz[k].find(j)->second = Pwz_new;
//				cout << "Pwz round=" << r << " z=" << k << " w=" << w_list[j] << " Pwz=" << Pwz_new << endl;
			}
		}
	}

	time_t end;
	time(&end);
	cout << "Time: " << difftime(start, end) << endl;
	return 0;
}



