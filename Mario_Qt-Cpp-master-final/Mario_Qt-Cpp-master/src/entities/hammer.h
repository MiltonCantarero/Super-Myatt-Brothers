/* 2024-12-08 TJG: Created new .h file for the hammer bro entity*/

#ifndef Hammer_H
#define Hammer_H

#include "enemy.h"
#include "../utils/animator.h"

class Block;
class Enemy;
class Hammer : public Enemy
{
public:
    static constexpr const float HAMMER_SPEED = 80.f;
    static constexpr const float HAMMER_DEAD_TIMER = 1.5f;
    Hammer(float x, float y);
    virtual ~Hammer();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    virtual void update(int cameraX, float elapsedTime) override;

    void checkCollisionWithBlocks();
    void collideWithBlock(Block* block);
    void checkCollisonWithEnemies();
    void collideWithEnemy(Enemy* enemy);
    void marioStomp();

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
    float m_speed;
    float m_deathCounter;
    float m_offsetY;

};

#endif // Hammer_H
