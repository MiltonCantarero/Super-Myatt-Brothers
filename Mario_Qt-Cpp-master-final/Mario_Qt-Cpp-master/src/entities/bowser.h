
/* 2024-11-23 MHS: Created new .h file for the Bowser enemy entity*/
/*2024-12-6 MHS: add bowser to replace king goomba as the final boss */
/*
#ifndef BOWSER_H
#define BOWSER_H
#include "enemy.h"
#include "../utils/animator.h"

class Block;
class Enemy;
class Bowser : public Enemy
{
public:
    static constexpr const float BOWSER_SPEED = 80.f;
    static constexpr const float BOWSER_DEAD_TIMER = 1.5f;
    Bowser(float x, float y);
    virtual ~Bowser();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    virtual void update(int cameraX, float elapsedTime) override;
    void checkCollisionWithBlocks();
    void collideWithBlock(Block* block);
    void checkCollisonWithEnemies();
    void collideWithEnemy(Enemy* enemy);
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
    float m_deathCounter;
    float m_speed;
};

#endif // BOWSER_H
*/
