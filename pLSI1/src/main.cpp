///*
// * main.cpp
// *
// *  Created on: May 30, 2014
// *      Author: lehongvan
// */
//#include "pLSI.h"
//
//int main() {
//	time_t start;
//	time(&start);
//
//	//*************** Read File ***************//
//	pLSI::readDocsFile();
//
//	//*************** Initialize ***************//
//	// Assign probability distributions, P(z), P(d|z), and P(w|z) randomly
//
//
//	// Random P(z)
//
//	// Random P(d|z)
//
//	// Random P(w|z)
//
//
//
////	//*************** EM ***************//
////	for (int r=0; r<round; ++r) {
////
////		//*************** E step ***************//
////		vector<map <int, double>> Pwdz[z]={};
////		for (int k=0; k<z; ++k) {
////			vector<map <int, double>> z_vector;
////			// loop for documents
////			for (map<int, map<int, int>>::const_iterator i = d_list.begin(); i != d_list.end(); i++) {
//////			for ( int i = 0; i < d_list.size(); i++) {
////				map <int, double> w_map;
////				// loop for words
////				for (map<int, int>::const_iterator j = i->second.begin(); j != i->second.end(); j++) {
//////				for ( int j = 0; j < d_list[i].size(); j++) {
////					double Pzx = Pz[k] * Pdz[k][i->first] * Pwz[k].find(j->first)->second;
////					w_map.insert(pair<int, double>(j->first, Pzx));
////
//////					cout << " z: " << k << " d: " <<  i->first << " w: " << j->first << " Pwdz: " << Pzx << endl;
////				}
////				z_vector.push_back(w_map);
////			}
////			Pwdz[k] = z_vector;
////		}
////
////
////
////		//*************** M step ***************//
////		for (int k=0; k<z; ++k) {
////			Pz[k] = 0;
////			//calculate Pdz
////			// loop for documents
//////			for ( int i = 0; i < d_list.size(); i++) {
////			for (map<int, map<int, int>>::const_iterator i = d_list.begin(); i != d_list.end(); i++) {
////				Pdz[k][i->first] = 0;
////				// loop for words
//////				for (map<int, int>::const_iterator j = d_list[i].begin(); j != d_list[i].end(); j++) {
////				for (map<int, int>::const_iterator j = i->second.begin(); j != i->second.end(); j++) {
////					Pdz[k][i->first] += j->second * Pwdz[k][i->first].find(j->first)->second;
//////					cout << "z=" << k << " d=" << i->first << " w=" << j->first << " d_list=" << j->second << " Pdwz= " << Pwdz[k][i->first][j->first] << endl;
////				}
//////				cout << "z=" << k << " d=" << i->first << " Pdz= " << Pdz[k][i->first] << endl;
////
////				//calculate Pz
////				Pz[k] += Pdz[k][i->first];
////			}
////
//////			cout << "round=" << r << " z=" << k << " Pz=" << Pz[k] << endl;
////
////			//calculate Pwz
////			// loop for words
////			for ( int j = 0; j < w_list.size(); j++) {
////				double Pwz_new = 0;
////				// loop for documents
//////				for ( int i = 0; i < d_list.size(); i++) {
////				for (map<int, map<int, int>>::const_iterator i = d_list.begin(); i != d_list.end(); i++) {
////					if (i->second.find(w_list[j]) != i->second.end()){
////						map<int, int>::const_iterator w_found = i->second.find(w_list[j]);
////						Pwz_new += w_found->second * Pwdz[k][i->first].find(w_found->first)->second;
//////						cout << "Pwz z=" << k << " d=" << i->first << " w=" << w_list[j] << " d_list=" << w_found->second << " Pdwz= " << Pwdz[k][i->first].find(w_found->first)->second << endl;
////					}
////				}
////				Pwz[k].find(j)->second = Pwz_new;
//////				cout << "Pwz round=" << r << " z=" << k << " w=" << w_list[j] << " Pwz=" << Pwz_new << endl;
////			}
////		}
////	}
//
//	time_t end;
//	time(&end);
//	cout << "Time: " << difftime(start, end) << endl;
//	return 0;
//}
//
//
//
