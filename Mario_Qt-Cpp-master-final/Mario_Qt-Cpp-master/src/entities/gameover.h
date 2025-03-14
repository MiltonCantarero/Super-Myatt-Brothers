/*
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsScene>

class GameOver : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameOver(QObject *parent = nullptr);
    void init();
signals:
    void gameActivated();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void loadPixmap();
    QPixmap m_bgPixmap;
    QPixmap m_titlePixmap;
};

#endif // GAMEOVER_H
*/
