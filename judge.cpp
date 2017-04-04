#include "judge.h"

Judge::Judge(QObject *parent) : QObject(parent)
{
    m_grille.resize(NB_CASE_HORIZONTAL * NB_CASE_VERTICAL, VIDE);
}

// Retourne JOUEUR1, JOUEUR2 ou NUL
char Judge::jouerUnePartie(IA *participant1, IA *participant2)
{
    // On vide la grille
    for(unsigned int i = 0; i < m_grille.size(); i++)
        m_grille[i] = VIDE;

    // On simule une partie
    char tourActu = JOUEUR1;
    char result = VIDE;
    short coup;

    do
    {
        if(tourActu == JOUEUR1)
        {
            participant1->updateGrille(m_grille, tourActu);
            coup = participant1->play();
        }
        else if(tourActu == JOUEUR2)
        {
            participant2->updateGrille(m_grille, tourActu);
            coup = participant2->play();
        }

        // On joue le coup
        m_grille[coup] = tourActu;

        // On change le tour
        tourActu = !tourActu;

        // On regarde si il y a victoire
        result = victory();

    }while(result == VIDE);

    // On retourne le resultat du match
    return result;
}

// Retourne NUL si match nul, VIDE si la partie n'est pas finie, JOUEUR1 ou JOUEUR2 si il y a un gagnant
char Judge::victory()
{
    // Victoire à l'horizontale
    for(int i = 0; i < NB_CASE_HORIZONTAL*NB_CASE_VERTICAL; i+=NB_CASE_VERTICAL)
    {
        if(m_grille[i] == m_grille[i + 1] && m_grille[i] == m_grille[i + 2] && m_grille[i] != VIDE)
            return m_grille[i];
    }

    // Victoire à la verticale
    for(int i = 0; i < NB_CASE_HORIZONTAL; i++)
    {
        if(m_grille[i] == m_grille[i + NB_CASE_HORIZONTAL] && m_grille[i] == m_grille[i + 2*NB_CASE_HORIZONTAL] && m_grille[i] != VIDE)
            return m_grille[i];
    }

    // Diagonale haut-gauche, bas droite
    if(m_grille[0] == m_grille[4] && m_grille[0] == m_grille[8] && m_grille[0] != VIDE)
        return m_grille[0];

    // Diagonale haut-gauche, bas droite
    if(m_grille[2] == m_grille[4] && m_grille[2] == m_grille[6] && m_grille[2] != VIDE)
        return m_grille[2];

    // On vérifie qu'il n'y a pas match nul
    bool matchNul = true;
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] == VIDE)
        {
            matchNul = false;
            break;
        }
    }

    if(matchNul)
        return NUL;

    return VIDE;
}

pair<int, int> Judge::gagnant(unsigned int nbParties, bool bothSide)
{
    pair<int, int> result = {0, 0}; // Nombre de partie gangé par chaque IA

    for(unsigned int i = 0; i < nbParties; i++)
    {
        if(bothSide && i % 2 == 0)
        {
            char duel = jouerUnePartie(m_participant2, m_participant1);

            // Si il y a match nul, on ne compatibilise pas
            if(duel == JOUEUR1)
                result.second++;
            else if(duel == JOUEUR2)
                result.first++;
        }
        else
        {
            char duel = jouerUnePartie(m_participant1, m_participant2);

            // Si il y a match nul, on ne compatibilise pas
            if(duel == JOUEUR1)
                result.first++;
            else if(duel == JOUEUR2)
                result.second++;
        }
    }

    return result;
}
