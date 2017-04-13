#ifndef JUDGE_H
#define JUDGE_H

#include "const.h"
#include "ia.h"
#include "iareseauneurone.h"

class Judge : public QObject
{
    Q_OBJECT
public:
    explicit Judge(QObject *parent = 0);

    // Retourne le nombre de match gagné par chaque IA
    // Both side indique si doit faire alterner celui qui commence
    pair<int, int> gagnant(IA *j1, IA *j2, unsigned int nbParties, bool bothSide);

    void loadRandom(int pop);
    void saveGenetique(const string& filename);
    void loadGenetique(const string& filename);

    void rankGenetique();

    void reproduceGentique();
    void evolve(int generation);

    void saveBest(const string& filename);

    inline int getMaxScore() {return population[0]->getScore();}
    inline int getMinScore() {return population.back()->getScore();}

private:
    vector<char> m_grille;
    vector<IAReseauNeurone*> population;

    // Retourne NUL si match nul, VIDE si la partie n'est pas finie, JOUEUR1 ou JOUEUR2 si il y a un gagnant
    char jouerUnePartie(IA *participant1, IA *participant2);

    // Fonction interne pour checker la victoire
    char victory();

    int selectGenetique(); // Selectionne les individus les meilleurs depuis le tableau trié et renvoie le nombre d'individu éliminé

signals:

public slots:
};

#endif // JUDGE_H
