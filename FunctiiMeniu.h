#pragma once

#include "FunctiiVotantiCandidati.h"
#include <map>
#include <unordered_map>
#include <vector>

int incercariFrauda = 0;

enum comandaMeniu{
    Op1,
    Op2,
    Op3
};

istream& operator>>(istream& is, comandaMeniu& comanda_meniu ){
    char a;
    is >> a;
    if(a == '+') comanda_meniu = Op1;
    else if (a == '?') comanda_meniu = Op2;
    else if (a == '*') comanda_meniu = Op3;
    return is;
}

vector<string> listaIntrareCandidati;

void Comanda1(map<string, Votant> myMap, unordered_map<string, Candidat> *mapForCandidati){
    string CNP_citit, nume_candidat_citit;
    cin.ignore();
    getline(cin, CNP_citit, ' ');
    getline(cin, nume_candidat_citit, '\n');
    auto it = myMap.find(CNP_citit);
    if(it == myMap.end()){
        cout << "CNP invalid" << '\n';
        incercariFrauda++;
    }
    else if(*myMap.at(CNP_citit).votInregistrat == 1){
        cout << "Vot deja inregistrat" << '\n';
        incercariFrauda++;
    }
    else if(myMap.at(CNP_citit).varstaVotant() == 0) cout << "Persoana minora\n";
    else{
        *myMap.at(CNP_citit).votInregistrat = 1;
        nr_total_voturi++;
        if(mapForCandidati->find(nume_candidat_citit) != mapForCandidati->end()){
            mapForCandidati->at(nume_candidat_citit).CandidatVotat();
        }
        else{
            Candidat candid(nume_candidat_citit);
            mapForCandidati->insert({nume_candidat_citit, candid});
            listaIntrareCandidati.push_back(nume_candidat_citit);
        }
    }
}

void Comanda2(unordered_map<string, Candidat> *mapForCandidati){
    cout << "Statistici\n==========\n";
    //crearea unui comparator//
    struct cmp{
        bool operator()(const int& a, const int& b) const{
            return b < a;
        }
    };
    //crearea unui multimap cu cheie numarul de voturi//
    multimap<int, Candidat, cmp> mapForCandidati1;
    int k = 0;
    for(auto it = mapForCandidati->begin(); it != mapForCandidati->end(); it++){
        if(it->second.voturi_candidat == 1) k++;
        mapForCandidati1.insert({it->second.voturi_candidat, it->second});
    }
    if(k == mapForCandidati->size()){
        auto it = mapForCandidati->begin();
        for(int i = 0; i < listaIntrareCandidati.size(); i++){
            cout << listaIntrareCandidati[i]<<": 1 voturi (";
            printf("%.2f", it->second.CalcProcentDinVoturi());
            cout << "%)\n";
        }
    }
    else {
        for (auto it = mapForCandidati1.begin(); it != mapForCandidati1.end(); it++) {
            cout << it->second.nume_candidat << ": " << it->first << " voturi (";
            printf("%.2f", it->second.CalcProcentDinVoturi());
            cout << "%)\n";
        }
    }
    cout << "Incercari de frauda: " << incercariFrauda;
}


