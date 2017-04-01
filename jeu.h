#ifndef JEU_H
#define JEU_H

#include "const.h"

class Jeu : public QObject
{
    Q_OBJECT

public:
    Jeu(QWidget *parent = nullptr);

private:
    vector<char> m_grille;

    char m_tourActu;
    bool m_partieFinie;


    void victory(); // Envoie un signal (victoire) si un joueur a gagné
    void indiquerVainqueur(int pos1, int pos2, int pos3);

signals:
    void changementGrille(vector<char> &g);
    void signalVictoire(char vainqueur);

public slots:
    void actualiserGrille(int numero);
    void recommencer();
};

#endif // JEU_H
