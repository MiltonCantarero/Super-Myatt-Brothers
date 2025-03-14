/*         PROVIED FILE WAS MADE BY MEC
 *          Meant to have all the code for gameover screen where the player can click any key or screen and restart the game again.
 *          did not go as planned.
 *
 * #include "gameover.h"
#include "../gamescene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>

GameOver::GameOver(QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(0,0, GLOBAL::RESOLUTION_FACTOR.width(), GLOBAL::RESOLUTION_FACTOR.height());   //MEANT TO ESTABLISH SIZE AND LOAD THE PIXMAP for GAMEOVER
    loadPixmap();
    init();
}

void GameOver::init()
{
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap);
    addItem(bgItem);

    QGraphicsPixmapItem *titleItem = new QGraphicsPixmapItem(m_titlePixmap.scaled(GLOBAL::RESOLUTION_FACTOR.width(), GLOBAL::RESOLUTION_FACTOR.height()));
    addItem(titleItem);

    int id = QFontDatabase::addApplicationFont(GameScene::PATH_TO_FONT);
    QString fontFamilyName = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont _font = QFont(fontFamilyName, GameScene::FONT_SIZE, 50);  //changing font
    QGraphicsSimpleTextItem *textItem = new QGraphicsSimpleTextItem();
    textItem->setFont(_font);
    textItem->setText("   Press any \nkey or button..."); //adding text to png hopefully
    textItem->setPen(QPen(GameScene::FONT_COLOR));
    textItem->setBrush(QBrush(GameScene::FONT_COLOR));
    textItem->setPos((GLOBAL::RESOLUTION_FACTOR.width() - textItem->boundingRect().width())/2, 125);
    addItem(textItem); //adding text

}

void GameOver::keyPressEvent(QKeyEvent *event)
{
    emit gameActivated();
    QGraphicsScene::keyPressEvent(event);
}

void GameOver::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit gameActivated();
    QGraphicsScene::mousePressEvent(event);
}

void GameOver::loadPixmap()
{
    if(m_bgPixmap.load(GameScene::PATH_TO_GAME_OVER))
    {
        qDebug() << "BG pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BG pixmap is NOT loaded successfully";
    }

    if(m_titlePixmap.load(GameScene::PATH_TO_GAME_OVER))
    {
        qDebug() << "Title pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "Title pixmap is NOT loaded successfully";
    }
}

*/
