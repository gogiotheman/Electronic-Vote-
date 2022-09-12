#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Votant{
public:
    Votant(){
        votInregistrat = new uint32_t;
        *votInregistrat = 0;
    }
    string nume_votant;
    string adresa_votant;
    string CNP_votant;
    string serie_Nr_CI_votant;
    bool varstaVotant(){
        if(CNP_votant[0] == '1' || CNP_votant[0] == '2') return 1;
        char s[2];
        s[0] = CNP_votant[1];
        s[1] = CNP_votant[2];
        int an_nastere = atoi(s);
        s[0] = CNP_votant[3];
        s[1] = CNP_votant[4];
        int luna_nastere = atoi(s);
        if(an_nastere == 0 && luna_nastere <= 5) return 1;
        return 0;
    }
    uint32_t *votInregistrat;
};

float nr_total_voturi = 0;

class Candidat{
public:
    Candidat(string nume){
        voturi_candidat = 1;
        nume_candidat = nume;
    };
    string nume_candidat;
    float voturi_candidat;
    void CandidatVotat(){
        voturi_candidat++;
    }
    float CalcProcentDinVoturi(){
        return (voturi_candidat * 100)/nr_total_voturi;
    }
};