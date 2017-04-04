#include "ia.h"

IA::IA(QObject *parent) : QObject(parent)
{

}

void IA::updateGrille(const vector<char> &g, char couleurIA)
{
    m_grille = g;
    m_couleurPions = couleurIA;
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

pair<int, int> IA::train(char typeMethode)
{
    qDebug("On ne peut pas entrainer cette classe avec cette methode : %c", typeMethode);
}
