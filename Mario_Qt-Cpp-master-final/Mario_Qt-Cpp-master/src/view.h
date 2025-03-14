#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "gamescene.h"
//#include "entities/gameover.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();

signals:

private:
   // void createConnections();
    GameScene* m_gameScene;
    //GameOver* m_gameOver;

    // QWidget interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
