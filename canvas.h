#ifndef CANVAS_H
#define CANVAS_H

#include "const.h"

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    vector<char> grille;

signals:
    void click(int numero);

public slots:
    void  updateGrille(vector<char>& g);
};

#endif // CANVAS_H
