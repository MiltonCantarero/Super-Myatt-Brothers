#include "enemy.h"
#include "goomba.h"
#include "koopa.h" //MEC 11-22-2024| Initializing Koopa as an enemy.
#include "koopashell.h" //MEC 11-28-2024| INitializing Shell as an enemy.
#include "kinggoomba.h" /* 2024-11-23 MHS: adds king goomba as enemy (?) */
#include "bowser.h" /* 2024-12-6 MHS: initializes bowser as an enemy*/
#include "Hammer.h" /* 2024-12-08 TJG: adds hammer as enemy (?) */
#include <QDebug>

QList<Enemy*> Enemy::ENEMIES;

Enemy::Enemy(float x, float y)
    : m_isAlive(true)
{
    setPosition(x, y);
    ENEMIES.push_back(this);
}

Enemy::~Enemy()
{
    ENEMIES.removeOne(this);
}

void Enemy::CreateEnemy(Type type, QPointF position)
{
    if(type == Type::Goomba)
    {
        Goomba* goomba = new Goomba(position.x(), position.y());
    }
}

void Enemy::CreateKoopa(TypeKoopa type, QPointF position)  //initializes Koopa as an enemy
{
    if(type == TypeKoopa::Koopa)
    {
        Koopa* koopa = new Koopa(position.x(), position.y());  //maybe changes the position of the enemy??
    }
}

/*
void Enemy::CreateShell(TypeShell type, QPointF position) // MEC 11/28/2024 - initializes Shell as an enemy
{
    if(type == TypeShell::KoopaShell)
    {
        KoopaShell* shell = new KoopaShell(position.x(), position.y());
    }
}
*/

void Enemy::CreateEnemyKingGoomba(TypeKingGoomba type, QPointF position)  //Make sure to comment this.
{
    if(type == TypeKingGoomba::kingGoomba)
    {
        kingGoomba* kinggoomba = new kingGoomba(position.x(), position.y());
    }
}
void Enemy::CreateEnemyHammer(TypeHammer type, QPointF position)  // 2024-12-08 TJG: Makes hammer an enemy.
{
    if(type == TypeHammer::hammer)
    {
        Hammer* hammer = new Hammer(position.x(), position.y());
    }
}

/*
void Enemy::CreateBowser(TypeBowser type, QPointF position) //2024-12-6 MHS: initilizes bowser as an enemy
{
    if(type == TypeBowser::Bowser)
    {
        Bowser*  bowser = new Bowser(position.x(), position.y());
    }
}
*/
void Enemy::setAlive(bool on)
{
    m_isAlive = on;
}

bool Enemy::isAlive() const
{
    return m_isAlive;
}

void Enemy::setShell(bool on)  //MEC 11/28/2024 | Similar to isAlive a boolean value to know when a koopa is in shell form
{
    m_isShell = on;
}

bool Enemy::isShell() const //MEC 11/28/2024 | ^^^^^^
{
    return m_isShell;
}

void Enemy::startMoving()  //MEC 12/02/2024 | (work on progress) to make shell move
{

    setPosition(position().x() + 10, position().y());
}
