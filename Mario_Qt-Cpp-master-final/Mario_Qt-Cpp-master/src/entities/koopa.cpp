
#include "koopa.h" //#include "goomba.h"
#include <QGraphicsPixmapItem>
#include "block.h"
#include "enemy.h"
//#include <iostream>


Koopa::Koopa(float x, float y)//Goomba::Goomba(float x, float y)
    :Enemy(x,y), m_isRight(false)//: Enemy(x, y), m_isRight(false)
{
    createAnimation();
    m_deathCounter = KOOPA_DEAD_TIMER;
    m_speed        = KOOPA_SPEED;

}

Koopa::~Koopa() //Goomba::~Goomba()
{
}

void Koopa::draw(GameScene &scene) //void Goomba::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setZValue(GLOBAL::ENEMY_LAYER);
    pItem->setPos(int(position().x()), int(position().y()-GLOBAL::TILE_SIZE.height()));
    //setPosition(position().x(), position().y()-GLOBAL::TILE_SIZE.height());
    pItem->setPixmap(m_animator.pixmap());
    scene.addItem(pItem);
    //std::cout << "value of x: " << int(position().x()) << " value of y: " << int(position().y());
}

void Koopa::update(float elapsedTime) //void Goomba::update(float elapsedTime)
{
    m_velocityY += GLOBAL::GRAVITY;
    m_velocityX = direction()*m_speed*elapsedTime;
    m_animator.update(elapsedTime);
    checkCollisionWithBlocks();
    checkCollisonWithEnemies();
    setPosition(position().x() + m_velocityX, position().y() + m_velocityY);
    if(m_velocityX > std::fabs(0.1f))
    {
        setAnimation("running");
    }


    if(!isAlive())
    {
        m_speed = 0.0f;
        m_deathCounter -= elapsedTime;
        setAnimation("die");
        if(m_deathCounter < 0.0f)
        {
            delete this;
        }

       // Enemy::CreateShell(Enemy::TypeShell::KoopaShell, QPointF(position().x(), position().y())); //Creates the new Entity Shell.

    }
    if(position().x() < 0.0f - GLOBAL::TILE_SIZE.width())
    {
        delete this;
    }
    if(position().y() > GLOBAL::SCREEN_SIZE.height()+GLOBAL::TILE_SIZE.height())
    {
        delete this;
    }
}

void Koopa::update(int cameraX, float elapsedTime)
{
    if( position().x() >= cameraX - GLOBAL::TILE_SIZE.width() - GLOBAL::ENTITY_UPDATE_AREA
        && position().x() < GLOBAL::ENTITY_UPDATE_AREA + GLOBAL::SCREEN_SIZE.width() + cameraX  )
    {
        update(elapsedTime);
    }
}

void Koopa::checkCollisionWithBlocks() //void Goomba::checkCollisionWithBlocks()
{
    for(int i = 0; i < Block::BLOCKS.size(); ++i)
    {
        collideWithBlock(Block::BLOCKS.at(i));
    }
}

void Koopa::collideWithBlock(Block *block) //void Goomba::collideWithBlock(Block *block)
{
    // Calculate potential new position
    float CollideX;
    float CollideY;
    float shrinkPixel = 5.f, shrinkFactor = 0.9f;//For one tile row, column to avoid block

    //X-axis
    if (m_velocityX <= 0.0f) // Moving Left
    {
        CollideX = position().x() + m_velocityX;
        if(block->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
        }
    }
    else // Moving Right
    {
        CollideX = position().x() + hitBox().width() + m_velocityX;
        if(block->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
        }
    }
    //Y-axis
    if(m_velocityY > 0.0f) // Moving Down
    {
        CollideY = position().y() + hitBox().height() + m_velocityY;
        if(block->hitBox().contains(position().x()+shrinkPixel, CollideY)
            ||
            block->hitBox().contains(position().x()+shrinkFactor*hitBox().width() , CollideY))
        {
            m_velocityY = 0.0f;
        }
    }
}

void Koopa::checkCollisonWithEnemies() //void Goomba::checkCollisonWithEnemies()
{
    for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
    {
        collideWithEnemy(Enemy::ENEMIES.at(i));
    }
}

void Koopa::collideWithEnemy(Enemy *enemy) //void Goomba::collideWithEnemy(Enemy *enemy)
{
    // Calculate potential new position
    float CollideX;
    float CollideY;
    float shrinkPixel = 5.f, shrinkFactor = 0.9f;//For one tile row, column to avoid block

    //X-axis
    if (m_velocityX <= 0.0f) // Moving Left
    {
        CollideX = position().x() + m_velocityX;
        if(enemy->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
        }
    }
    else // Moving Right
    {
        CollideX = position().x() + hitBox().width() + m_velocityX;
        if(enemy->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
        }
    }
}

void Koopa::createAnimation() //void Goomba::createAnimation()
{
    m_texturePixmap.load(":/res/enemies_18x18.png");

    float TSW = GLOBAL::ENEMY_TEXTURE_SIZE.width();
    float TSH = GLOBAL::ENEMY_TEXTURE_SIZE.height();
    float TW  = GLOBAL::TILE_SIZE.width(); //Can be used to make the enemy bigger
    float TH  = GLOBAL::TILE_SIZE.height();//^^^^^^^^^^^

    // std::ofstream outfile("output.txt");
    // std::cout << "Width:" << TSW << "  Height:" << TSH << "  TWidth:" << TW << "  THeight:" << TH;

    //0 1 2frames
    //Think of each number being part of an array in the png     4toRight
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(3*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH));  //changed to match Koopa
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(4*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH));  //changed height to get his eyes

    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(3*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH).transformed(QTransform().scale(-1,1)));
    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(4*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH).transformed(QTransform().scale(-1,1)));


    m_animator.m_mapStates["die"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH));
    m_animator.m_mapStates["die_f_"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH).transformed(QTransform().scale(-1,1)));

    m_animator.changeState("running");
    m_animator.m_timeBetweenFrames = 0.5f;
}

void Koopa::setAnimation(QString state) //void Goomba::setAnimation(QString state)
{
    if(m_isRight)             //Reversed to fix Koopa's direction animation.
    {
        m_animator.changeState(state + "_f_");
    }
    else
    {
        m_animator.changeState(state);
    }
}

QRect Koopa::hitBox() //QRect Goomba::hitBox()
{
    return QRect(position().x(), position().y(), GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}

void Koopa::setDirection(bool isRight) //void Goomba::setDirection(bool isRight)
{
    m_isRight = isRight;
}

int Koopa::direction() const //int Goomba::direction() const
{
    if(m_isRight)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
