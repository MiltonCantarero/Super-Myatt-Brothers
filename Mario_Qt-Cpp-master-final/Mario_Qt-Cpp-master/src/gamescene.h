/*
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QElapsedTimer>
#include <QTimer>
#include "utils/mapmanager.h"
#include "utils/global.h"
//#include "entities/mario.h"
class Mario;
struct KeyStatus
{
    bool m_held = false;
    bool m_released = false;
};

struct MouseStatus
{
    float m_x = 0.0f;
    float m_y = 0.0f;
    bool m_released = false;
    bool m_pressed = false;
};

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);
    KeyStatus* keys(int keyCode);
    void drawScore();  //Com
    QPixmap m_allNumbersPixmap; //COM
signals:

private slots:
    void loop();

private:
    void handlePlayerInput();
    void resetKeyStatus();
    void resetGameScene();
    void renderGameScene();


    float getCameraX(const Mario& mario);
    float m_mostRightX;
    KeyStatus* m_keys[256];
    MouseStatus* m_mouse;

    const int FPS = 60;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime = 0.0f, m_loopTime = 0.0f;
    const float m_loopSpeed;

    MapManager m_mapManager;
    Mario *m_mario;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
*/

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QElapsedTimer>
#include <QTimer>
#include <QGraphicsTextItem>
#include "utils/mapmanager.h"
#include "utils/global.h"
#include <QColor> //MEC | to be able to add the color white for the text

class Mario;

struct KeyStatus {
    bool m_held = false;
    bool m_released = false;
};

struct MouseStatus {
    float m_x = 0.0f;
    float m_y = 0.0f;
    bool m_released = false;
    bool m_pressed = false;
};

class GameScene : public QGraphicsScene {
    Q_OBJECT
public slots:
    //void activeGameOver();
public:
    explicit GameScene(QObject *parent = nullptr);
    KeyStatus* keys(int keyCode);
    //static const QString PATH_TO_GAME_OVER;
    //static const QString PATH_TO_FONT;
   // static constexpr int FONT_SIZE = 20;
    //static constexpr QColor WHITE = QColor(255, 255, 255);
   // static constexpr QColor FONT_COLOR = WHITE;
   // void init();

signals:
//void gameOverActivated();
private slots:
    void loop();
    //void activeGameOver();
   //void updateTimer(); // 2024-12-06 TJG: Slot to update and display elapsed game time

private:
    void handlePlayerInput();
    void resetKeyStatus();
    void resetGameScene();
    void renderGameScene();
    float getCameraX(const Mario& mario);

    float m_mostRightX;
    KeyStatus* m_keys[256];
    MouseStatus* m_mouse;

    const int FPS = 60;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime = 0.0f, m_loopTime = 0.0f;
    const float m_loopSpeed;

    MapManager m_mapManager;
    Mario *m_mario;

    /* 2024-12-06 TJG: Timer-related variables for tracking and displaying game elapsed time */
    QTimer* gameTimer;                // Timer to track elapsed game time (1-second intervals)
    int elapsedTime;                  // Stores the total time elapsed in seconds
    QGraphicsTextItem* timerDisplay;  // Text display for showing elapsed game time on the screen

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
