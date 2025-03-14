#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QDir>
#include <QGraphicsRectItem>
#include "entities/mario.h"
#include "entities/questionblock.h"
#include "entities/mushroom.h"
#include "entities/enemy.h"

//int gameScore = 0; // MEC 12/8/2024 | Meant to add the Coin Counter/gameScore and initialize it to 0
//const QSize NUMBER_SIZE = QSize(32,32); //Changing the font size of gameScore

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_mostRightX(200000),  //ADDED GAME()
      m_loopSpeed(int(1000.0f/GLOBAL::FPS))
{

    m_mapManager.updateMapSketch(0);
    m_mapManager.convertFromSketch(0);
    m_mostRightX = float(m_mapManager.getMapSketchWidth()*GLOBAL::TILE_SIZE.width()-GLOBAL::SCREEN_SIZE.width());
    m_mario = new Mario();
    m_mario->setMaxX(m_mostRightX+GLOBAL::SCREEN_SIZE.width());
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i] = new KeyStatus();
    }
    m_mouse = new MouseStatus();
    setSceneRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();

}

KeyStatus *GameScene::keys(int keyCode)
{
    return m_keys[keyCode];
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    while( m_loopTime > m_loopSpeed)
    {
        const float elapsedTime = 1.0f/FPS;
//input
        handlePlayerInput();
        m_mario->update(elapsedTime, *this);
//update
        for(int i = 0; i < Block::BLOCKS.size(); ++i)
        {
            Block::BLOCKS.at(i)->update(elapsedTime);
        }
        for(int i = 0; i < Mushroom::MUSHROOMS.size(); ++i)
        {
            Mushroom::MUSHROOMS.at(i)->update(elapsedTime);
        }
        for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
        {
            Enemy::ENEMIES.at(i)->update(getCameraX(*m_mario), elapsedTime);
        }
       // drawScore(); MEC| was hoping for a score to appear at the top right corner (failed)
//draw
        clear();
        setBackgroundBrush(QBrush(QColor(Qt::black)));
        float cameraPosX = std::clamp(getCameraX(*m_mario), 0.0f, m_mostRightX);
        QGraphicsRectItem* bgRect = new QGraphicsRectItem();
        bgRect->setRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        bgRect->setPos(cameraPosX, 0);
        bgRect->setPen(QColor(0, 219, 255));
        bgRect->setBrush(QColor(0, 219, 255));
        addItem(bgRect);
        m_mapManager.drawBackground(cameraPosX, *this);
        m_mapManager.drawForeground(cameraPosX, *this);
        m_mario->draw(*this);
        for(int i = 0; i < Mushroom::MUSHROOMS.size(); ++i)
        {
            Mushroom::MUSHROOMS.at(i)->draw(*this);
        }
        for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
        {
            Enemy::ENEMIES.at(i)->draw(*this);
        }
        setSceneRect(cameraPosX, 0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        //Add boundary
        QGraphicsRectItem* lRect = new QGraphicsRectItem();
        lRect->setPen(QColor(Qt::black));
        lRect->setBrush(QColor(Qt::black));
        lRect->setRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        lRect->setPos(sceneRect().x()-GLOBAL::SCREEN_SIZE.width(), 0);
        lRect->setZValue(1000);
        addItem(lRect);
        QGraphicsRectItem* rRect = new QGraphicsRectItem();
        rRect->setPen(QColor(Qt::black));
        rRect->setBrush(QColor(Qt::black));
        rRect->setRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        rRect->setPos(sceneRect().x()+GLOBAL::SCREEN_SIZE.width(), 0);
        rRect->setZValue(1000);
        addItem(rRect);

        //reset key/mouse status, reset frame counter
        resetKeyStatus();
        m_loopTime -= m_loopSpeed;
      //  drawScore(); MEC| was hoping for a score to appear at the top right corner (failed)
    }
}

void GameScene::handlePlayerInput()
{
    if(m_keys[GLOBAL::R_KEY]->m_released || m_keys[GLOBAL::ENTER_KEY]->m_released)
    {
        resetGameScene();
    }
    if(m_keys[GLOBAL::Z_KEY]->m_released)
    {
        //renderGameScene();//uncomment if you want to make screenshots
    }
}

void GameScene::resetKeyStatus()
{
    for(int i = 0; i < GLOBAL::COUNT_OF_KEYS; ++i)
    {
        m_keys[i]->m_released = false;
    }
    m_mouse->m_released = false;
}

void GameScene::resetGameScene()
{
    Block::BLOCKS.clear();
    Mushroom::MUSHROOMS.clear();
    Enemy::ENEMIES.clear();
    m_mapManager.updateMapSketch(0);
    m_mapManager.convertFromSketch(0);
    m_mario->resetStatus();
}

void GameScene::renderGameScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

float GameScene::getCameraX(const Mario &mario)
{
    if(mario.x() < GLOBAL::SCREEN_SIZE.width()/2){
        return 0.0f;
    }
    else
    {
        return mario.position().x() - GLOBAL::SCREEN_SIZE.width()/2;
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(GLOBAL::KeysMapper.contains(event->key()))
    {
        m_keys[GLOBAL::KeysMapper[event->key()]]->m_held = true;
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(GLOBAL::KeysMapper.contains(event->key()))
    {
        m_keys[GLOBAL::KeysMapper[event->key()]]->m_held = false;
        m_keys[GLOBAL::KeysMapper[event->key()]]->m_released = true;
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = true;
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = false;
    m_mouse->m_released = true;
    QGraphicsScene::mouseReleaseEvent(event);
}


/*  MEC 12/8/2024 Attempted to add a function that will determine when it is at a gameover screen.
 *
void GameScene::activeGameOver()
{
    emit gameOverActivated();
}

const QString GameScene::PATH_TO_GAME_OVER = ":/res/sprite/message.png"; //meant to initialize the gameover screen as a png
const QString GameScene::PATH_TO_FONT = ":/res/font/04B_19.ttf"; //To use a specific font when adding words into the png.
*/

/* PLEASE ADD COMMENTS CORRECTLY!!!
 * THE FOLOWING CODE BELOW WAS MADE BY SAM
 *
// below here the code been added
void GameScene::drawScore()
{
    QString scoreText = QString::number(m_game().m_score);
    int unityPartVal = 0;
    int decimalPartValue = 0;
    int hendredthPartValue = 0;

    if(scoreText.length() == 1) // 0 - 9
    {
        unityPartVal = scoreText.toInt();
        decimalPartValue = 0;
        hendredthPartValue = 0;
    }
    else if(scoreText.length() == 2) // 10 - 99
    {
        unityPartVal = scoreText.last(1).toInt();
        decimalPartValue = scoreText.first(1).toInt();
        hendredthPartValue = 0;
    }
    else if(scoreText.length() == 3) // 100 - 999
    {
        unityPartVal = scoreText.last(1).toInt();
        hendredthPartValue = scoreText.first(1).toInt();
        QString copyVal = scoreText;
        copyVal.chop(1);
        decimalPartValue = copyVal.last(1).toInt();
    }

    QGraphicsPixmapItem* unityPartScoreItem = new QGraphicsPixmapItem(m_allNumbersPixmap.copy(unityPartVal * Game::NUMBER_SIZE.width(), 0, Game::NUMBER_SIZE.width(), Game::NUMBER_SIZE.width()));
    unityPartScoreItem->moveBy( m_game().RESOLUTION.width() - Game::NUMBER_SIZE.width(), 0);
    addItem(unityPartScoreItem);

    QGraphicsPixmapItem* decimalPartScoreItem = new QGraphicsPixmapItem(m_allNumbersPixmap.copy(decimalPartValue * Game::NUMBER_SIZE.width(), 0, Game::NUMBER_SIZE.width(), Game::NUMBER_SIZE.width()));
    decimalPartScoreItem->moveBy(m_game().RESOLUTION.width() - 2 * Game::NUMBER_SIZE.width(), 0);
    addItem(decimalPartScoreItem);

    QGraphicsPixmapItem* hundrethPartScoreItem = new QGraphicsPixmapItem(m_allNumbersPixmap.copy(hendredthPartValue * Game::NUMBER_SIZE.width(), 0, Game::NUMBER_SIZE.width(), Game::NUMBER_SIZE.height()));
    hundrethPartScoreItem->moveBy(m_game().RESOLUTION.width() - 3 * Game::NUMBER_SIZE.width(), 0);
    addItem(hundrethPartScoreItem);
}
const QString GameScene::PATH_TO_GAME_OVER = ":/res/sprite/message.png";
*/
