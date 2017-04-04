#include "iaminmax.h"

IAMinMax::IAMinMax() : IA()
{

}

int IAMinMax::evaluation()
{
    // Victoire à l'horizontale
    for(int i = 0; i < NB_CASE_HORIZONTAL*NB_CASE_VERTICAL; i+=NB_CASE_VERTICAL)
    {
        if(m_grille[i] == m_grille[i + 1] && m_grille[i] == m_grille[i + 2] && m_grille[i] != VIDE)
        {
            if(m_grille[i] == m_couleurPions)
                return INFINI;
            else
                return -INFINI;
        }
    }

    // Victoire à la verticale
    for(int i = 0; i < NB_CASE_HORIZONTAL; i++)
    {
        if(m_grille[i] == m_grille[i + NB_CASE_HORIZONTAL] && m_grille[i] == m_grille[i + 2*NB_CASE_HORIZONTAL] && m_grille[i] != VIDE)
        {
            if(m_grille[i] == m_couleurPions)
                return INFINI;
            else
                return -INFINI;
        }
    }

    // Diagonale haut-gauche, bas droite
    if(m_grille[0] == m_grille[4] && m_grille[0] == m_grille[8] && m_grille[0] != VIDE)
    {
        if(m_grille[0] == m_couleurPions)
            return INFINI;
        else
            return -INFINI;
    }

    // Diagonale haut-gauche, bas droite
    if(m_grille[2] == m_grille[4] && m_grille[2] == m_grille[6] && m_grille[2] != VIDE)
    {
        if(m_grille[2] == m_couleurPions)
            return INFINI;
        else
            return -INFINI;
    }

    // SI personne ne gagne
    return 0;
}

int IAMinMax::nbCaseVide()
{
    int nb = 0;
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] == VIDE)
        {
            nb++;
        }
    }

    return nb;
}

int IAMinMax::mini(int caseVides, int profondeur)
{
    if(caseVides == 0) // Si on ne peut jouer nul part
        return evaluation() - profondeur; // Ici on enlève la profondeur car on cherche a gagné le plus rapidement possible

    int score = evaluation(); // On regarde si il y a un gagnant
    int minimum = INFINI + 1;

    if(score != 0) // Si quelqu'un a gagné la partie, ça ne sert a rien de continuer
        return score - profondeur;

    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] != VIDE)
            continue;

        // On simule le coup
        m_grille[i] = !m_couleurPions;


        minimum = min(minimum, maxi(caseVides - 1, profondeur + 1));

        // On revient en arrière
        m_grille[i] = VIDE;
    }

    return minimum + profondeur;
}

int IAMinMax::maxi(int caseVides, int profondeur)
{
    if(caseVides == 0) // Si on ne peut jouer nul part
        return evaluation() + profondeur; // Ici on enlève la profondeur car on cherche a perdre le plus loin possible

    int score = evaluation(); // On regarde si il y a un gagnant
    int maximum = -INFINI - 1;

    if(score != 0) // Si quelqu'un a gagné la partie, ça ne sert a rien de continuer
        return score + profondeur;

    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] != VIDE)
            continue;

        // On simule le coup
        m_grille[i] = m_couleurPions;

        maximum = max(maximum, mini(caseVides - 1, profondeur - 1));

        // On revient en arrière
        m_grille[i] = VIDE;
    }

    return maximum - profondeur;
}

int IAMinMax::play()
{
    int maximum = -INFINI - 1;
    int indiceMax = -1;

    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] != VIDE)
            continue;

        m_grille[i] = m_couleurPions; // On simule le coup

        int temp = mini(nbCaseVide(), 1);

        if(temp > maximum)
        {
            maximum = temp;
            indiceMax = i;
        }
        else if(temp == maximum) // Pour introduire un peu d'aléatoire dans les paries
        {
            if(rand() % 4 == 0)
                indiceMax = i;
        }

        m_grille[i] = VIDE; // On remet bien
    }

    return indiceMax;
}
