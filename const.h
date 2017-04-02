#ifndef CONST_H
#define CONST_H

using namespace std;

#include <QApplication>
#include <QObject>

#include <QWidget>

#include <QPainter>
#include <QPaintEvent>
#include <QPen>

#include <QHBoxLayout>
#include <QPushButton>

#include <QMessageBox>

#include <vector>

enum {VIDE = -1, JOUEUR1 = 0, JOUEUR2 = 1, VICTOIRE_JOUEUR1 = 2, VICTOIRE_JOUEUR2 = 3};

#define TAILLE_CASE 100
#define NB_CASE_HORIZONTAL 3
#define NB_CASE_VERTICAL 3

#define TAILLE_VERTICAL TAILLE_CASE * NB_CASE_VERTICAL
#define TAILLE_HORIZONTAL TAILLE_CASE * NB_CASE_HORIZONTAL

#define TAILLE_ESPACE 5




#endif // CONST_H
