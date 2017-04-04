#include "iareseauneurone.h"

IAReseauNeurone::IAReseauNeurone(string filename) : IA()
{
    //vector<int> neuroneParCouche = {18, 14, 9};
    m_reseau = new ReseauNeurone(filename);
}

IAReseauNeurone::~IAReseauNeurone()
{
    delete m_reseau;
}


int IAReseauNeurone::play()
{
    // 9 premier, mes pions (1 si il y en a 0 sinon)
    // 9 derniers, les pions de l'adversaire

    vector<float> entree;

    // Les 9 permiers, mes pions
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] == m_couleurPions)
            entree.push_back(1);
        else
            entree.push_back(0);
    }

    // Les 9 derniers, les pions de l'adversaire
    for(unsigned int i = 0; i < m_grille.size(); i++)
    {
        if(m_grille[i] == !m_couleurPions)
            entree.push_back(1);
        else
            entree.push_back(0);
    }

    // On calcul le vecteur de sorti avec un poids sur chaque coups
    vector<float> result = m_reseau->calculResult(entree);

    // On cherche le coups avec le meilleur poids qu'on a le droit de jouer
    // Booleen qui indique si on a trouvé le coup a jouer
    bool find = false;
    while(!find)
    {
        int indiceMax = -1;
        float maxi = -1;
        for(unsigned int i = 0; i < result.size(); i++)
        {
            if(result[i] > maxi)
            {
                maxi = result[i];
                indiceMax = i;
            }
        }

        if(m_grille[indiceMax] != VIDE)
        {
            result[indiceMax] = -1;
        }
        else
        {
            return indiceMax;
        }
    }
}

pair<int, int> IAReseauNeurone::train(char typeMethode)
{
    pair<int, int> retour;
    const int combatParIa = 10000;

    IA *adversaire = new IA; // IA random pour s'entrainer;

    Judge *juge = new Judge;

    juge->setParticipant1(this);
    juge->setParticipant2(adversaire);


    pair<int, int> result = juge->gagnant(combatParIa, true);

    // On cherche a minimiser le score (nombre de parties perdues)
    int scoreActu = result.second;
    retour.first = scoreActu;

    for(int i = 0; i < 1000; i++)
    {
        vector<Modif> modifs = modifPoids();

        result = juge->gagnant(combatParIa, true);

        if(result.second > scoreActu) // Si les changement sont moins bon, on revient comme avant
        {
            for(unsigned int i = 0; i < modifs.size(); i++)
            {
                m_reseau->getPoids(modifs[i].couche, modifs[i].x, modifs[i].y) = modifs[i].ancienneValue;
            }
        }
        else
        {
            scoreActu = result.second;
        }
    }

    retour.second = scoreActu;

    m_reseau->save(m_reseau->getFileName());

    return retour;
}

vector<Modif> IAReseauNeurone::modifPoids()
{
    // Retourne un vecteur avec les modif qui ont été faites au hasard pour pouvoir revenir a l'état précédent
    vector<Modif> retour;
    int nombreModif = rand() % 3 + 1;

    for(int i = 0; i < nombreModif; i++)
    {
        Modif m;
        m.couche = rand() % (m_reseau->getNbCouche() - 1);

        m.x = rand() % (m_reseau->getCoucheSize(m.couche));
        m.y = rand() % (m_reseau->getCoucheSize(m.couche + 1));

        m.ancienneValue = m_reseau->getPoids(m.couche, m.x, m.y);

        m_reseau->getPoids(m.couche, m.x, m.y) = (rand() % NB_VALEUR_POID) / (double)NB_VALEUR_POID;
        retour.push_back(m);
    }
    return retour;
}
