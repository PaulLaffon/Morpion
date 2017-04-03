#ifndef JEU_H
#define JEU_H

#include "const.h"
#include "ia.h"

class Jeu : public QObject
{
    Q_OBJECT

public:
    Jeu(QWidget *parent = nullptr);
    ~Jeu();

    void recommencer(bool avecIA, char typeIa, bool IACommence);

private:
    vector<char> m_grille;

    char m_tourActu;
    bool m_partieFinie;

    char m_typeOfIa;
    char m_tourIa;


    IA *m_ia;

    void victory(); // Envoie un signal (victoire) si un joueur a gagné
    void indiquerVainqueur(int pos1, int pos2, int pos3);
    void playIA();

signals:
    void changementGrille(vector<char> &g);
    void signalVictoire(char vainqueur);

public slots:
    void actualiserGrille(int numero);
};

#endif // JEU_H
