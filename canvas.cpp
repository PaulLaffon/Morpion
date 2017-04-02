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
            int x = i % NB_CASE_HORIZONTAL;
            int y = i / NB_CASE_HORIZONTAL;

            if(grille[i] == JOUEUR1 || grille[i] == VICTOIRE_JOUEUR1)
            {
                if(grille[i] == JOUEUR1)
                    painter.setPen(QPen(Qt::white, 8));
                else
                    painter.setPen(QPen(Qt::red, 8));

                painter.drawLine(x * TAILLE_CASE + 12, y * TAILLE_CASE + 12, (x+1) * TAILLE_CASE - 12, (y+1) * TAILLE_CASE - 12);
                painter.drawLine((x+1) * TAILLE_CASE - 12, y * TAILLE_CASE + 12, x * TAILLE_CASE + 12, (y+1) * TAILLE_CASE - 12);
            }
            else // Si c'est un pion du joueur 2
            {
                if(grille[i] == JOUEUR2)
                {
                    painter.setBrush(Qt::white);
                    painter.setPen(Qt::white);
                }
                else // SI c'est un pion de victoire
                {
                    painter.setBrush(Qt::red);
                    painter.setPen(Qt::red);
                }

                painter.drawEllipse(QPoint((x + 0.5) * TAILLE_CASE, (y + 0.5) * TAILLE_CASE), TAILLE_CASE / 2 - 10, TAILLE_CASE / 2 - 10);
            }
        }
    }

    painter.end();
}
