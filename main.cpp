#include "FunctiiMeniu.h"
#include <fstream>
#include <map>

int main(){
    map<string, Votant> votanti;
    ifstream f;
    f.open("C:\\Users\\sgogi\\CLionProjects\\Tema 6 - Votul electronic\\evidenta.csv");
    while(!f.eof()){
        Votant votantProba;
        getline(f, votantProba.nume_votant, ',');
        getline(f, votantProba.adresa_votant, ',');
        string a = votantProba.adresa_votant;
        getline(f, votantProba.CNP_votant, ',');
        getline(f, votantProba.serie_Nr_CI_votant, '\n');
        votanti.insert({votantProba.CNP_votant, votantProba});
    }
    f.close();
    unordered_map<string, Candidat> *candidati;
    candidati = new unordered_map<string, Candidat>;
    comandaMeniu comanda_citita;
    while(cin >> comanda_citita){
        switch(comanda_citita){
            case Op1:
                Comanda1(votanti, candidati);
                break;
            case Op2:
                Comanda2(candidati);
                break;
            case Op3:
                Comanda2(candidati);
                delete candidati;
                return 0;
            default:
                return 0;
        }
    }
}








