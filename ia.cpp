#include "ia.h"

IA::IA(QObject *parent) : QObject(parent)
{

}

void IA::updateGrille(const vector<char> &g)
{
    m_grille = g;
}

int IA::play()
{
    vector<short> caseVide;
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] == VIDE)
            caseVide.push_back(i);
    }

    int n = rand() % caseVide.size();
    return caseVide[n];
}
