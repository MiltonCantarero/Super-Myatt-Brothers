/* 2024-11-23 MHS: Created new .h file for the King Goomba enemy entity*/
/*2024-12-6 MHS: king goomba is going to be a normal enemy */

#ifndef KINGGOOMBA_H
#define KINGGOOMBA_H

#include "enemy.h"
#include "../utils/animator.h"

class Block;
class Enemy;
class kingGoomba : public Enemy
{
public:
    static constexpr const float KGOOMBA_SPEED = 50.f; //makes king goomba slower than a normal goomba
    static constexpr const float KGOOMBA_DEATH_TIMER = 1.5f;
    static constexpr const int KGOOMBA_HEALTH = 3; //makes king goomba have more health
    //than normal goomba (hopefully T_T); made int so that, hopefully, it can help with making it live longer
    kingGoomba(float x, float y);
    virtual ~kingGoomba();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    virtual void update(int cameraX, float elapsedTime) override;
    void setMaxX(int maxX); //sets boundary so it doesn't walk out of the screen

    void checkCollisionWithBlocks();
    void collideWithBlock(Block* block);
    void checkCollisonWithEnemies();
    void collideWithEnemy(Enemy* enemy);
    void marioStomp(); /* 2024-11-25  MHS: method that will initialize king goomba losing health
   // when mario stomps on him */

private:
    void createAnimation();
    void setAnimation(QString state);
    virtual QRect hitBox() override;
    void setDirection(bool isRight);
    int direction() const;

    float m_velocityX, m_velocityY;
    QPixmap m_texturePixmap;
    Animator m_animator;
    bool m_isRight;
    int m_healthCounter; //gives king goomba additional health
    float m_speed;
    float m_deathCounter;
    float m_offsetY; // stores the y-offset for sprite scaling
    float m_maxX; //part of boundary
};

#endif // KINGGOOMBA_H
