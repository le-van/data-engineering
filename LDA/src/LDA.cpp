//============================================================================
// Name        : LDA.cpp
// Author      : lehongvan
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

const int z=16;		// number of latent factors
const int d=19098;  // number of documents
const int w=1878;
const int ROUND=100; // number of EM rounds
const double alpha=50/z;
const double beta=200/w;

int tp[d][z] = {0};
int tw[z][w] = {0};

vector< int > w_index;
vector< int > d_index;
vector< vector <pair <int, int> > > d_list;
map< int, string > w_info;
map< int, string > d_info;

void readDocsFile();
void readWordsFile();
void readPapersFile();
void initialize();
void LDA();
void output();

int main() {
		time_t start;
		time(&start);

		//******************** Read File ********************//
		readDocsFile();
		readWordsFile();
		readPapersFile();

		//******************** Initialize ********************//
		initialize();

		//*********************** LDA ************************//
		for (int r=0; r<ROUND; ++r) {
			LDA();
		}

		//*************** Write to output file ***************//
		output();

		time_t end;
		time(&end);
		cout << "Execution time: " << difftime(end, start) << " seconds" << endl;

	return 0;
}

void readDocsFile(){
	string line;
	ifstream myfile ("docs.txt");
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
			d_list.push_back (w_list);
	    }
	    myfile.close();
	 }
	else cout << "Unable to open file　docs.txt";
}

void readWordsFile(){
	string line;
	ifstream myfile ("wlist.txt");
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
	else cout << "Unable to open file wlist.txt";
}

void readPapersFile(){
	string line;
	ifstream myfile ("papers.txt");
	if (myfile.is_open()) {
		int d_index = 0;
		while (getline (myfile,line)) {
			d_info.insert(pair<int, string> (d_index, line));
			d_index++;
	    }
	    myfile.close();
	 }
	 else cout << "Unable to open file papers.txt";
}

void initialize() {
	// Random P(z)
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(0,z-1);

	// loop for docs
	for (int i=0; i<d; ++i) {
		// loop for words
		for (int j=0; j<d_list[i].size(); ++j) {
			int t_random = distribution(generator);
			d_list[i][j].second = t_random;
			// update matrix
			if (tp[i][t_random] == 0) tp[i][t_random] = 1;
			else tp[i][t_random] += 1;

			if (tw[t_random][d_list[i][j].first] == 0) tw[t_random][d_list[i][j].first] = 1;
			else tw[t_random][d_list[i][j].first] += 1;
		}
	}
}

void LDA(){
	// calculate total times topic is assigned to all words in the corpus
	vector <double> tw_total;
	for (int k=0; k<z; k++) {
		double total = 0;
		for (int j=0; j<w; ++j) {
			if (tw[k][j] > 0) total += tw[k][j];
		}
		tw_total.push_back(total);
	}

	// loop for docs
	for (int i=0; i<d; ++i) {
		// loop for words
		for (int j=0; j<d_list[i].size(); ++j) {
			int w_id = d_list[i][j].first;
			int topic = d_list[i][j].second;

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

			d_list[i][j].second = assigned_topic;
			tw[assigned_topic][w_id] += 1;
			tp[i][assigned_topic] += 1;
			tw_total[assigned_topic] += 1;
		}
	}
}

void output(){
	// Write words
	ofstream w_output;
	w_output.open ("LDA_words.txt");
	for (int i=0; i<z; ++i) {
		w_output << "Topic " << i << "\n";
		for (int j=0; j<20; j++){
			int max = distance(tw[i], max_element(tw[i], tw[i]+w));
			w_output << w_info.find(w_index[max])->second << "(" << tw[i][max] << ")/";
			tw[i][max] = 0;
		}
		w_output << "\n";
	}
	w_output.close();

	// Write docs
	ofstream d_output;
	d_output.open ("LDA_docs.txt");
	for (int i=0; i<z; ++i) {
		d_output << "Topic " << i << "\n";
		for (int j=0; j<20; j++){
			int max = distance(tp[i], max_element(tp[i], tp[i]+d));
			d_output << "\t" << d_info.find(max)->second << "\n";
			tp[i][max] = 0;
		}
		d_output << "\n";
	}
	d_output.close();
}
