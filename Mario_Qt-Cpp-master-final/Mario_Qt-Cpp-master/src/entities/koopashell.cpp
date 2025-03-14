/*

#include "koopashell.h" //#include "goomba.h"
#include <QGraphicsPixmapItem>
#include "block.h"
#include "enemy.h"
//#include <iostream>

//bool changingToShell = true; //

KoopaShell::KoopaShell(float x, float y)//Goomba::Goomba(float x, float y)
    :Enemy(x,y), m_isRight(false)//: Enemy(x, y), m_isRight(false)
{
    createAnimation();
    m_deathCounter = KOOPASHELL_DEAD_TIMER;
    m_speed        = 0;

}

KoopaShell::~KoopaShell() //Goomba::~Goomba()
{
}

void KoopaShell::draw(GameScene &scene) //void Goomba::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setZValue(GLOBAL::ENEMY_LAYER);
    pItem->setPos(int(position().x()), int(position().y()-GLOBAL::TILE_SIZE.height()));
    //setPosition(position().x(), position().y()-GLOBAL::TILE_SIZE.height());
    pItem->setPixmap(m_animator.pixmap());
    scene.addItem(pItem);
    // std::cout << "value of x: " << int(position().x()) << " value of y: " << int(position().y());
}

void KoopaShell::update(float elapsedTime) //void Goomba::update(float elapsedTime)
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

void KoopaShell::update(int cameraX, float elapsedTime)
{
    if( position().x() >= cameraX - GLOBAL::TILE_SIZE.width() - GLOBAL::ENTITY_UPDATE_AREA
        && position().x() < GLOBAL::ENTITY_UPDATE_AREA + GLOBAL::SCREEN_SIZE.width() + cameraX  )
    {
        update(elapsedTime);
    }
}

void KoopaShell::checkCollisionWithBlocks() //void Goomba::checkCollisionWithBlocks()
{
    for(int i = 0; i < Block::BLOCKS.size(); ++i)
    {
        collideWithBlock(Block::BLOCKS.at(i));
    }
}

void KoopaShell::collideWithBlock(Block *block) //void Goomba::collideWithBlock(Block *block)
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

void KoopaShell::checkCollisonWithEnemies() //void Goomba::checkCollisonWithEnemies()
{
    for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
    {
        collideWithEnemy(Enemy::ENEMIES.at(i));
    }
}

void KoopaShell::collideWithEnemy(Enemy *enemy) //void Goomba::collideWithEnemy(Enemy *enemy)
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
            enemy -> setAlive(true);
        }
    }
    else // Moving Right
    {
        CollideX = position().x() + hitBox().width() + m_velocityX;
        if(enemy->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
            enemy -> setAlive(true);
        }
    }
}

void KoopaShell::createAnimation() //void Goomba::createAnimation()
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
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH));  //changed to match Koopa
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH));  //changed height to get his eyes

    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH).transformed(QTransform().scale(-1,1)));
    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH).transformed(QTransform().scale(-1,1)));


    m_animator.m_mapStates["die"].push_back(m_texturePixmap.copy(7*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH));
    m_animator.m_mapStates["die_f_"].push_back(m_texturePixmap.copy(8*TSW, 6*TSH, TSW, 2*TSH).scaled(TW, 2*TH).transformed(QTransform().scale(-1,1)));

    m_animator.changeState("running");
    m_animator.m_timeBetweenFrames = 0.5f;
}

void KoopaShell::setAnimation(QString state) //void Goomba::setAnimation(QString state)
{
    if(m_isRight)
    {
        m_animator.changeState(state + "_f_");
    }
    else
    {
        m_animator.changeState(state);
    }
}

QRect KoopaShell::hitBox() //QRect Goomba::hitBox()
{
    return QRect(position().x(), position().y(), GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}

void KoopaShell::setDirection(bool isRight) //void Goomba::setDirection(bool isRight)
{
    m_isRight = isRight;
}

int KoopaShell::direction() const //int Goomba::direction() const
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

int KoopaShell::setSpeed(int Speed){
    return m_speed = Speed;
}


void KoopaShell::checkShell(Enemy *enemy){   //MEC 11/28/2024 | Checks if Koopa is in shell form and sets boolean value to false
    //if(changingToShell){
    enemy-> setShell(true);
    //}
}

*/
