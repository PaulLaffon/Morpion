#include "jeu.h"

Jeu::Jeu(QWidget *parent) : QObject(parent)
{
    m_grille.resize(NB_CASE_HORIZONTAL * NB_CASE_VERTICAL, VIDE);
    m_tourActu = JOUEUR1;
    m_partieFinie = false;
}

void Jeu::actualiserGrille(int numero)
{
    if(m_grille[numero] == VIDE && !m_partieFinie)
    {
        m_grille[numero] = m_tourActu;

        // On emmet ce signal pour indiquer qu'il y a eu un changement sur la grille
        emit changementGrille(m_grille);

        m_tourActu = !m_tourActu; // On change le tour du joueur

        victory(); // Regarde si un joueur gagne
    }
}

void Jeu::victory()
{
    // Victoire à l'horizontale
    for(int i = 0; i < NB_CASE_HORIZONTAL*NB_CASE_VERTICAL; i+=NB_CASE_VERTICAL)
    {
        if(m_grille[i] == m_grille[i + 1] && m_grille[i] == m_grille[i + 2] && m_grille[i] != VIDE)
        {
            indiquerVainqueur(i, i + 1, i + 2);
            return;
        }
    }

    // Victoire à la verticale
    for(int i = 0; i < NB_CASE_HORIZONTAL; i++)
    {
        if(m_grille[i] == m_grille[i + NB_CASE_HORIZONTAL] && m_grille[i] == m_grille[i + 2*NB_CASE_HORIZONTAL] && m_grille[i] != VIDE)
        {
            indiquerVainqueur(i, i + NB_CASE_HORIZONTAL, i + 2*NB_CASE_HORIZONTAL);
            return;
        }
    }

    // Diagonale haut-gauche, bas droite
    if(m_grille[0] == m_grille[4] && m_grille[0] == m_grille[8] && m_grille[0] != VIDE)
    {
        indiquerVainqueur(0, 4, 8);
        return;
    }

    // Diagonale haut-gauche, bas droite
    if(m_grille[2] == m_grille[4] && m_grille[2] == m_grille[6] && m_grille[2] != VIDE)
    {
        indiquerVainqueur(2, 4, 6);
        return;
    }
}

void Jeu::indiquerVainqueur(int pos1, int pos2, int pos3)
{
    m_partieFinie = true;
    char vainqueur = m_grille[pos1];

    m_grille[pos1] = m_grille[pos2] = m_grille[pos3] = PION_VICTOIRE;

    emit changementGrille(m_grille);
    emit signalVictoire(vainqueur); // Affiche un messageBox
}

void Jeu::recommencer()
{
    m_tourActu = JOUEUR1;
    m_partieFinie = false;
    for(auto &i : m_grille)
        i = VIDE;

    emit changementGrille(m_grille);
}
