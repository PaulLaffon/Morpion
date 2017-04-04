#include "jeu.h"

Jeu::Jeu(QWidget *parent) : QObject(parent)
{
    m_grille.resize(NB_CASE_HORIZONTAL * NB_CASE_VERTICAL, VIDE);
    m_typeOfIa = AUCUNE_IA;
}

Jeu::~Jeu()
{
    if(m_typeOfIa != AUCUNE_IA)
        delete m_ia;
}

// Slot qui récupère la position du clic et qui actualise la grille en conséquences
void Jeu::actualiserGrille(int numero)
{
    if(m_grille[numero] == VIDE && !m_partieFinie)
    {
        m_grille[numero] = m_tourActu;

        // On emmet ce signal pour indiquer qu'il y a eu un changement sur la grille
        emit changementGrille(m_grille);

        m_tourActu = !m_tourActu; // On change le tour du joueur

        victory(); // Regarde si un joueur gagne

        // Si il n'y pas d'IA
        if(m_typeOfIa != AUCUNE_IA && !m_partieFinie)
        {
            playIA();
        }
    }
}

// Active la fonction indiquerVainqueur si la partie est finie avec le gagnant (ou match nul)
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
    {
        indiquerVainqueur(VIDE, VIDE, VIDE);
    }
}

// Emet un signal pour afficher le vainqueur
void Jeu::indiquerVainqueur(int pos1, int pos2, int pos3)
{
    m_partieFinie = true;

    // SI il y a match nul
    if(pos1 == VIDE)
    {
        emit signalVictoire(VIDE);
    }

    char vainqueur = m_grille[pos1];


    if(vainqueur == JOUEUR1)
        m_grille[pos1] = m_grille[pos2] = m_grille[pos3] = VICTOIRE_JOUEUR1;
    else if(vainqueur == JOUEUR2)
        m_grille[pos1] = m_grille[pos2] = m_grille[pos3] = VICTOIRE_JOUEUR2;

    emit changementGrille(m_grille);
    emit signalVictoire(vainqueur); // Affiche un messageBox
}

// Recommence ou commence la partie en fonction des paramètres
void Jeu::recommencer(bool avecIA, char typeIA, bool IACommence)
{
    m_tourActu = JOUEUR1;

    if(!avecIA)
    {
        m_typeOfIa = AUCUNE_IA;
    }
    else
    {
        if(IACommence)
            m_tourIa = JOUEUR1;
        else
            m_tourIa = JOUEUR2;


        // Si le type d'IA change, on doit recharger le nouveau type
        if(m_typeOfIa != typeIA)
        {
            if(m_typeOfIa != AUCUNE_IA)
                delete m_ia;

            m_typeOfIa = typeIA;


            switch (m_typeOfIa) {
            case RANDOM_IA:
                m_ia = new IA();
                break;
            case MIN_MAX_IA:
                m_ia = new IAMinMax();
                break;
            default:
                break;
            }
        }
    }

    m_partieFinie = false;
    for(auto &i : m_grille)
        i = VIDE;

    emit changementGrille(m_grille);

    if(m_tourActu == m_tourIa && m_typeOfIa != AUCUNE_IA)
    {
        playIA();
        emit changementGrille(m_grille);
    }
}

//Fait jouer l'IA qui a été chargée en mémoire
void Jeu::playIA()
{
    QTime t;
    t.start();

    m_ia->updateGrille(m_grille, m_tourIa);
    unsigned int coups = m_ia->play();

    // Voir le temps de calcul du coup
    //qDebug("Time elapsed: %d ms", t.elapsed());

    if(coups >= m_grille.size() || m_grille[coups] != VIDE)
    {
        // Do nothing
        m_tourActu = !m_tourActu;
        return;
    }
    else
    {
        m_grille[coups] = m_tourIa;
    }
    m_tourActu = !m_tourActu;

    emit changementGrille(m_grille);
    victory();
}
