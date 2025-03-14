#include "view.h"
#include <QKeyEvent>
#include <QApplication>

View::View()
     : m_gameScene(new GameScene(this))//, m_gameScene(new GameScene(this)), m_gameOver(new GameOver(this))
{
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width()+2, m_gameScene->sceneRect().height()+2);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    QGraphicsView::keyReleaseEvent(event);
}

/* MEC 12/8/2024 | Meant to connect the end screen with the function to make it appear
 *
void View::createConnections()
{
    connect(m_gameOver, &GameOver::gameActivated, [this](){
        setScene(m_gameScene);
        m_gameScene->init();
    });
}

*/
