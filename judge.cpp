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

        // Si une personne veut jouer dans une case non autorisée, elle a perdu
        if(m_grille[coup] != VIDE)
        {
            return !tourActu;
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

pair<int, int> Judge::gagnant(IA *j1, IA *j2, unsigned int nbParties, bool bothSide)
{
    pair<int, int> result = {0, 0}; // Nombre de partie gangé par chaque IA

    for(unsigned int i = 0; i < nbParties; i++)
    {
        if(bothSide && i % 2 == 0)
        {
            char duel = jouerUnePartie(j2, j1);

            // Si il y a match nul, on ne compatibilise pas
            if(duel == JOUEUR1)
                result.second++;
            else if(duel == JOUEUR2)
                result.first++;
        }
        else
        {
            char duel = jouerUnePartie(j1, j2);

            // Si il y a match nul, on ne compatibilise pas
            if(duel == JOUEUR1)
                result.first++;
            else if(duel == JOUEUR2)
                result.second++;
        }
    }

    return result;
}

void Judge::loadRandom(int pop) // Constructeur aléatoire
{
    for(int i = 0; i < pop; i++)
    {
        population.push_back(new IAReseauNeurone()); // On crée une population aléatoire
    }
}


void Judge::saveGenetique(const string& filename)
{
    ofstream file;
    file.open(filename);

    file << population.size() << endl;

    for(unsigned int i = 0; i < population.size(); i++)
    {
        population[i]->save(file);
    }

    file.close();
}

void Judge::loadGenetique(const string &filename)
{
    ifstream file;
    file.open(filename);

    int popSize;
    file >> popSize;

    for(int i = 0; i < popSize; i++)
    {
        population.push_back(new IAReseauNeurone(file));
    }

    file.close();
}

bool compare(IAReseauNeurone *a, IAReseauNeurone *b)
{
    return a->getScore() > b->getScore();
}

void Judge::rankGenetique()
{
    for(IAReseauNeurone *i : population)
        i->resetScore();

    for(unsigned int i = 0; i < population.size() - 1; i++)
    {
        for(unsigned int j = i + 1; j < population.size(); j++)
        {
            // On joue la partie dans un sens
            char result1 = jouerUnePartie(population[i], population[j]);

            // On change les score en fonction du gagnant (match nul = 0)
            if(result1 == JOUEUR1)
            {
                population[i]->scoreWin();
                population[j]->scoreLose();
            }
            else if(result1 == JOUEUR2)
            {
                population[j]->scoreWin();
                population[i]->scoreLose();
            }

            // On joue la partie dans l'autre sens
            result1 = jouerUnePartie(population[j], population[i]);

            // On change les score en fonction du gagnant (match nul = 0)
            if(result1 == JOUEUR2)
            {
                population[i]->scoreWin();
                population[j]->scoreLose();
            }
            else if(result1 == JOUEUR1)
            {
                population[j]->scoreWin();
                population[i]->scoreLose();
            }
        }
    }

    sort(population.begin(), population.end(), compare);
}


void Judge::saveBest(const string &filename)
{
    population[0]->save(filename);
}

// Retourne le nombre d'individus eliminer
int Judge::selectGenetique()
{
    unsigned int size = population.size();
    int numberEliminate = 0;
    // On élimine aléatoirement les individus, avec plus de chance sur les mauvais
    for(unsigned int i = 1; i < size; i++)
    {
        if(rand() % size < i)
        {
            // Une fois l'individu delete, on mets la valeur a nullptr pour retourver les cases vides
            delete population[i];
            population[i] = nullptr;
            numberEliminate++;
        }
    }
    qDebug("Nombre eliminé : %d", numberEliminate);
    return numberEliminate;
}

void Judge::reproduceGentique()
{
    int killed = selectGenetique(); // On récupère le nombre d'individus éliminés
    int indiceFirt = 0;

    // On remet 2% de la population de façon random
    for(unsigned int i = 0; i < population.size() / 50; i++)
    {
        while(population[indiceFirt] != nullptr)
            indiceFirt++;

        killed--;
        population[indiceFirt] = new IAReseauNeurone();
    }

    // Tant qu'il reste des case vides dans le tableau
    while(killed > 0)
    {
        while(population[indiceFirt] != nullptr)
            indiceFirt++;

        int indiceParent1, indiceParent2;

        // On prends les parents parmis les 10% des meilleurs
        do
        {
            indiceParent1 = rand() % (population.size() / 10);
            indiceParent2 = rand() % (population.size() / 10);
        }while(population[indiceParent1] == nullptr || population[indiceParent2] == nullptr);

        population[indiceFirt] = new IAReseauNeurone(*population[indiceParent1], *population[indiceParent2]);

        killed--;
    }
}


void Judge::evolve(int generation)
{
    for(int i = 0; i < generation; i++)
    {
        rankGenetique();

        qDebug("Generation : %d", i);
        qDebug("Best : %d", getMaxScore());
        qDebug("Low : %d", getMinScore());

        reproduceGentique();
    }

    rankGenetique();
}














