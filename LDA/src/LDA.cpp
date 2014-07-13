//============================================================================
// Name        : LDA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <fstream>
using namespace std;

const int z=32;		// number of latent factors
const int d=19098;  // number of documents
const int w=1878;
const int ROUND=200; // number of EM rounds
const double alpha=0.001;
const double beta=0.05;

int tp[d][z] = {0};
int tw[z][w] = {0};

vector<int> w_index;
vector<int> d_index;
vector < vector <pair <int, int> > > d_info;
map<int, string> w_info;

void readDocsFile();
void readWordsFile();
void initialize();
void lda();
void output();

int main() {
		time_t start;
		time(&start);

		//*************** Read File ***************//
		readDocsFile();
		readWordsFile();

		//*************** Initialize ***************//
		initialize();

		//*************** EM ***************//
		for (int r=0; r<ROUND; ++r) {
			lda();
		}

		//*************** Write to output file ***************//
		output();

		time_t end;
		time(&end);
		cout << "Time: " << difftime(start, end) << endl;

	return 0;
}

void readDocsFile(){
	string line;

		ifstream myfile ("/Users/lehongvan/Documents/workspace2/LDA/src/docs.txt");
		if (myfile.is_open()) {
			while (getline (myfile,line)) {
				string word;
				int index;
				vector < pair <int,int> > w_list;
				for (string::iterator it=line.begin(); it!=line.end(); ++it)
				{
					if(*it == '\t')
					{
						index = atoi(word.c_str());
						d_index.push_back(index);
						word = "";
					}
					else if(*it == ' ' || it+1 == line.end())
				    {
						if (it+1 == line.end()) word.push_back(*it);
						int word_index = atoi(word.c_str());

						// Before random topics for each word, assign 0 to every words
						w_list.push_back(pair<int, int>(word_index, 0));

				         //First time the word is seen in all documents
				         if(find(w_index.begin(), w_index.end(), word_index) == w_index.end())
				         {
				        	 w_index.push_back(word_index);
				         }
				         word = "";
				    }
				    else
				    {
				         word.push_back(*it);
				    }
				}
				d_info.push_back (w_list);
		    }
		    myfile.close();
		 }
		else cout << "Unable to open file";
}

void readWordsFile(){
	string line;

		ifstream myfile ("/Users/lehongvan/Documents/workspace2/pLSI/src/wlist.txt");
		if (myfile.is_open()) {
			while (getline (myfile,line)) {
				string word;
				int word_index;
				for (string::iterator it=line.begin(); it!=line.end(); ++it)
				{
					if(*it == '\t' || *it == ' ')
					{
						if(atoi(word.c_str()) != 0) {
							word_index = atoi(word.c_str());
						}
						else {
							w_info.insert(pair<int, string> (word_index, word));
							break;
						}
						word = "";
				    }
				    else
				    {
				         word.push_back(*it);
				    }
				}
		    }
		    myfile.close();
		 }
		else cout << "Unable to open file";
}

void initialize() {
	// Random P(z)
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(0,z-1);

	// loop for docs
	for (int i=0; i<d; ++i) {
		// loop for words
		for (int j=0; j<d_info[i].size(); ++j) {
			int t_random = distribution(generator);
			d_info[i][j].second = t_random;
			// update matrix
			if (tp[i][t_random] == 0) tp[i][t_random] = 1;
			else tp[i][t_random] += 1;

			if (tw[t_random][d_info[i][j].first] == 0) tw[t_random][d_info[i][j].first] = 1;
			else tw[t_random][d_info[i][j].first] += 1;
		}
	}

//	for (int i=0; i<z; i++) {
//		for (int j=0; j<w; j++) {
//			if (tw[i][j] > 1) cout << "topic: " << i << " word: " << j << " number: " << tw[i][j] << endl;
//		}
//	}
//	// loop for docs
//	for (int i=0; i<d; ++i) {
//		// loop for words
//		for (int j=0; j<d_info[i].size(); ++j) {
//			vector<int>::iterator word_it = find (w_index.begin(), w_index.end(), d_info[i][j].first);
//			int word_idx = distance(w_index.begin(), word_it);
//			cout << "docs: " << i << "words: " << word_idx << "topic: " << d_info[i][j].second << endl;
//		}
//	}

}

void lda(){

	// calculate total times topic is assigned to all words in the corpus
	vector <double> tw_total;
	for (int k=0; k<z; k++) {
		cout << "lda" << endl;
		double total = 0;
		for (int j=0; j<w; ++j) {
			if (tw[k][j] > 0) total += tw[k][j];
		}
		cout << "topic: " << k << "total: " << total << endl;
		tw_total.push_back(total);
	}

	// loop for docs
	for (int i=0; i<d; ++i) {
		// loop for words
		for (int j=0; j<d_info[i].size(); ++j) {
			int w_id = d_info[i][j].first;
			int topic = d_info[i][j].second;
			tw[topic][w_id] -= 1;
			tp[i][topic] -= 1;
			tw_total[topic] -= 1;

			vector<double> Pz;
			double Pz_total = 0;
			for (int k=0; k<z; k++) {
				double Pz_cal = (tp[i][k] + alpha) * (tw[k][w_id] + beta) / tw_total[k];
				Pz.push_back(Pz_cal);
				Pz_total += Pz_cal;
			}

			// Normalize
			for (int k=0; k<z; k++) {
				Pz[k] = Pz[k] / Pz_total;
			}

			// construct a trivial random generator engine from a time-based seed:
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			default_random_engine generator (seed);
			discrete_distribution<int> dist(Pz.begin(), Pz.end());
			int assigned_topic = dist(generator);
			cout << "docs: " << i << "words: " << w_id << "topic: " << assigned_topic << endl;

			d_info[i][j].second = assigned_topic;
			tw[assigned_topic][w_id] += 1;
			tp[i][assigned_topic] += 1;
			tw_total[assigned_topic] += 1;
		}
	}
}

void output(){
	// Write P(w|z)
	ofstream Pwz_output;
	Pwz_output.open ("Pwz.txt");

	for (int i=0; i<z; ++i) {
		Pwz_output << "Topic " << i << "\n";
		for (int j=0; j<30; j++){
			int max = distance(tw[i], max_element(tw[i], tw[i]+w));
			Pwz_output << w_info.find(w_index[max])->second << "(" << tw[i][max] << ")/";
			tw[i][max] = 0;
		}
		Pwz_output << "\n";
	}

	Pwz_output.close();
}
