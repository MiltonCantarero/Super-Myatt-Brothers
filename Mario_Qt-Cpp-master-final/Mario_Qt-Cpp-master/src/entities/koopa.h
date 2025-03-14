#ifndef KOOPA_H
#define KOOPA_H
#include "enemy.h"
#include "../utils/animator.h"

class Block;
class Enemy;
class Koopa : public Enemy //class Koopa : public Enemy
{
public:
    static constexpr const float KOOPA_SPEED = 80.f;
    static constexpr const float KOOPA_DEAD_TIMER = 1.5f;
    Koopa(float x, float y);
    virtual ~Koopa();
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
    void checkShell(Enemy *enemy); //Adds new function to change isShell value on enemy.h

    float m_velocityX, m_velocityY;
    QPixmap m_texturePixmap;
    Animator m_animator;
    bool m_isRight;
    float m_deathCounter;
    float m_speed;
};

#endif // KOOPA_H
