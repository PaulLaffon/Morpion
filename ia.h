#ifndef IA_H
#define IA_H

#include "const.h"

class IA : public QObject
{
    Q_OBJECT
public:
    explicit IA(QObject *parent = 0);

    virtual int play(); // Methode qui renvoie la case sur laquelle l'IA joue
    virtual void updateGrille(const vector<char> &g);

protected:
    vector<char> m_grille;

signals:

public slots:

};

#endif // IA_H
