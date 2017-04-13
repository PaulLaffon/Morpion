#include "iareseauneurone.h"

// Constructeur aléatoire
IAReseauNeurone::IAReseauNeurone() : IA(), score(0)
{
    vector<int> neuroneParCouche = {19, 14, 9};
    m_reseau = new ReseauNeurone(neuroneParCouche);
}

IAReseauNeurone::IAReseauNeurone(const string &filename) : IA(), score(0)
{
    m_reseau = new ReseauNeurone(filename);
}

IAReseauNeurone::IAReseauNeurone(ifstream &file) : IA(), score(0)
{
    m_reseau = new ReseauNeurone(file);
}

IAReseauNeurone::IAReseauNeurone(const IAReseauNeurone &parent1, const IAReseauNeurone &parent2)
{
    m_reseau = new ReseauNeurone(parent1.getReseau(), parent2.getReseau());
}

IAReseauNeurone::~IAReseauNeurone()
{

}


int IAReseauNeurone::play()
{
    // 9 premier, mes pions (1 si il y en a 0 sinon)
    // 9 derniers, les pions de l'adversaire
    // Dernier 1 si début de partie, 0 sinon

    vector<float> entree;
    bool vide = true; // indique si c'est le début de la partie ou pas

    // Les 9 permiers, mes pions
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        entree.push_back((m_grille[i] == m_couleurPions));

        if(m_grille[i] != VIDE)
            vide = false;
    }

    // Les 9 derniers, les pions de l'adversaire
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        entree.push_back((m_grille[i] == !m_couleurPions));
    }

    // On ajoute le dernier qui inqique le début de la partie
    entree.push_back((float)vide);

    // On calcul le vecteur de sorti avec un poids sur chaque coups
    vector<float> result = m_reseau->calculResult(entree);
/*
    for(unsigned int i = 0; i < result.size(); i++)
    {
        qDebug("%d : %f", i, result[i]);
    }
*/

    // On retourne l'indice de l'élément max
    return distance(result.begin(), max_element(result.begin(), result.end()));
}

