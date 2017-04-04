#ifndef JUDGE_H
#define JUDGE_H

#include "const.h"
#include "ia.h"

class Judge : public QObject
{
    Q_OBJECT
public:
    explicit Judge(QObject *parent = 0);

    // Retourne le nombre de match gagné par chaque IA
    // Both side indique si doit faire alterner celui qui commence
    pair<int, int> gagnant(unsigned int nbParties, bool bothSide);

    inline void setParticipant1(IA *p) {m_participant1 = p;}
    inline void setParticipant2(IA *p) {m_participant2 = p;}

private:
    vector<char> m_grille;
    IA *m_participant1;
    IA *m_participant2;

    char jouerUnePartie(IA *participant1, IA *participant2);

    char victory();

signals:

public slots:
};

#endif // JUDGE_H
