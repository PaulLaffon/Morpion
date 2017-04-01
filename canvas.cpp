#include "canvas.h"

canvas::canvas(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(TAILLE_HORIZONTAL, TAILLE_VERTICAL);
    grille.resize(NB_CASE_HORIZONTAL * NB_CASE_VERTICAL, VIDE);

}

void canvas::mouseReleaseEvent(QMouseEvent *event)
{
    const int x = event->x() / TAILLE_CASE;
    const int y = event->y() / TAILLE_CASE;

    emit click(y * NB_CASE_HORIZONTAL + x);
}

void canvas::updateGrille(vector<char>& g)
{
    grille = g;
    repaint();
}

void canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QColor noir(0, 0, 0);
    QColor blanc(255, 255, 255);
    QColor bleu(0, 0, 255);
    QColor rouge(255, 0, 0);
    QColor vert(0, 255, 0);


    // Rempli la zone en noir
    painter.fillRect(0, 0, TAILLE_HORIZONTAL, TAILLE_VERTICAL, noir);


    // Dessiner les lignes horizonales
    for(int i = 1; i < NB_CASE_VERTICAL; i++)
    {
        painter.fillRect(0, TAILLE_CASE * i - TAILLE_ESPACE, TAILLE_HORIZONTAL, 2 * TAILLE_ESPACE, blanc);
    }

    // Dessiner les lignes verticales
    for(int i = 1; i < NB_CASE_HORIZONTAL; i++)
    {
        painter.fillRect(TAILLE_CASE * i - TAILLE_ESPACE, 0, 2 * TAILLE_ESPACE, TAILLE_VERTICAL, blanc);
    }

    for(unsigned int i = 0; i < grille.size(); i++)
    {
        if(grille[i] != VIDE)
        {
            QColor colorActu;

            if(grille[i] == JOUEUR1)
                colorActu = rouge;
            else if(grille[i] == JOUEUR2)
                colorActu = bleu;
            else if(grille[i] == PION_VICTOIRE)
                colorActu = vert;

            int x = i % NB_CASE_HORIZONTAL;
            int y = i / NB_CASE_HORIZONTAL;

            painter.fillRect(x * TAILLE_CASE, y * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, colorActu);
        }
    }

    painter.end();
}
