/* 2024-11-23 MHS: Created new .cpp file for King Goomba enemy entity */
#include "kinggoomba.h"
#include <QGraphicsPixmapItem>
#include "block.h"
#include "enemy.h"
#include "src/entities/mario.h"

/*
 * To look into specic values like the texture sizes look into global.h inside the utils folder
 * Good Luck!!! and don't try to stress yourself see this a fun little project rather than homework!
 */

/* my notes ijbol..
 * ok so below kingGoomba::collisionWithEnemy is a new function called
 * kingGoomba::marioStomp
 * this one is the second option to see if it allows mario to stomp on it more than once
 * for the second option though, i modified kinggoomba.h and .cpp, but i also added
 * like 2 things to mario.h and mario.cpp but i don't know if they're going to work
 * or how to initialize them T_T
 */

kingGoomba::kingGoomba(float x, float y)
    : Enemy(x, y), m_isRight(false), m_healthCounter(KGOOMBA_HEALTH)
{
    createAnimation();
    // m_health = KGOOMBA_HEALTH;
    //commented out for now bc idk if it's going to change anything if it's outside {} too
    m_speed = KGOOMBA_SPEED;
    //m_healthCounter = KGOOMBA_HEALTH;
    m_deathCounter = KGOOMBA_DEATH_TIMER;

    // 2024-12-2 MHS: adjusts y-positioning for larger sprite at initialization hopefully
    float scaledHeight = 2 * GLOBAL::TILE_SIZE.height();
    float originalHeight = GLOBAL::TILE_SIZE.height();
    m_offsetY = scaledHeight - originalHeight;

    // place king goomba higher (manually) to avoid sinking into the ground
    setPosition(x, y - m_offsetY);
}

kingGoomba::~kingGoomba()
{
}

void kingGoomba::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setZValue(GLOBAL::ENEMY_LAYER);

    /*2024-12-2 MHS: try to adjust y-positioning now that scaling size has changed */
    float scaledHeight = 2 * GLOBAL::TILE_SIZE.height();
    float originalHeight = GLOBAL::TILE_SIZE.height();
    m_offsetY = (scaledHeight - originalHeight) / 16.0f;

    // Set the adjusted position
    pItem->setPos(int(position().x()), int(position().y() + m_offsetY));
    pItem->setPixmap(m_animator.pixmap());
    scene.addItem(pItem);
}

void kingGoomba::update(float elapsedTime)
{
    m_velocityY += GLOBAL::GRAVITY;
    m_velocityX = direction()*m_speed*elapsedTime;
    m_animator.update(elapsedTime);
    checkCollisionWithBlocks();
    checkCollisonWithEnemies();
    //collideWithMario(); //might need to rework this if it doesn't work

    /*2024-12-2 MHS: try to correct the y-position offset for the larger sprite */
    float scaledHeight = 2 * GLOBAL::TILE_SIZE.height(); // this is the scaled height
    float originalHeight = 2 * GLOBAL::TILE_SIZE.height(); //original height
    m_offsetY = scaledHeight - originalHeight;

    /*2024-12-2 MHS: update position to apply offsetY */
    setPosition(position().x() + m_velocityX, position().y() + m_velocityY - m_offsetY
                /*- 5* = if we want to make him bounce*/);
    if(m_velocityX > std::fabs(0.1f))
    {
        setAnimation("running");
    }

    //custom for health
    if(m_healthCounter <= 0) //2024-11-25 MHS: checks if health is depleted
    {
        setAlive(false);
    }
    //try to figure out how to mesh ^ and v together to make a counter for the health so it goes up to 3
    //then king goomba dies
    if (!isAlive())
    {
        m_speed = 0.0f;
        m_deathCounter -= elapsedTime;
        setAnimation("die");
        if (m_deathCounter < 0.0f)
        {
            delete this; // Deletes King Goomba once death animation is complete
            return;
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

    //2024-12-4 MHS: boundary so king goomba doesn't walk off the screen at the end
  /*  if(position().x() < 0.0f)
    {
        setX(0.0f);
    }
    if(position().y() > GLOBAL::SCREEN_SIZE.height()+2*GLOBAL::TILE_SIZE.height())
    {
        setY(GLOBAL::SCREEN_SIZE.height()+3*GLOBAL::TILE_SIZE.height());
        //setHurt();
        //setHurt();
    }
    if(position().x() > m_maxX - GLOBAL::TILE_SIZE.width())
    {
        setX(m_maxX - GLOBAL::TILE_SIZE.width());
    }

}*/

    /*2024-12-4 MHS: boundary (hopefully)*/
   /* void kingGoomba::setMaxX(int maxX)
    {
        m_maxX = maxX;
    }
*/
}

void kingGoomba::update(int cameraX, float elapsedTime)
{
    if(position().x() >= cameraX - GLOBAL::TILE_SIZE.width() - GLOBAL::ENTITY_UPDATE_AREA
        && position().x() < GLOBAL::ENTITY_UPDATE_AREA + GLOBAL::SCREEN_SIZE.width() + cameraX)
    {
        update(elapsedTime);
    }
}

void kingGoomba::checkCollisionWithBlocks()
{
    for(int i = 0; i < Block::BLOCKS.size(); ++i)
    {
        collideWithBlock(Block::BLOCKS.at(i));
    }
}

void kingGoomba::collideWithBlock(Block *block)
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
void kingGoomba::checkCollisonWithEnemies()
{
    for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
    {
        collideWithEnemy(Enemy::ENEMIES.at(i));
    }
}

void kingGoomba::collideWithEnemy(Enemy *enemy)
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

/* 2024-11-25 MHS: new function, hopefully so that mario can stomp on king goomba more than once*/
void kingGoomba::marioStomp()
{
    m_healthCounter--; //should decrement king goomba's health when mario stomps on it

    //if statement to check if king goomba's health is depleted
    if(m_healthCounter <= 0)
    {
        setAlive(false); //i don't know if it's going to be redundant having it here AND in the update function, this might need to be taken off?
    }
}

void kingGoomba::createAnimation()
{
    m_texturePixmap.load(":/res/enemies_18x18.png");
    //m_texturePixmap.load(":/res/enemy_test.png");

    float TSW = GLOBAL::ENEMY_TEXTURE_SIZE.width();
    float TSH = GLOBAL::ENEMY_TEXTURE_SIZE.height();
    float TW  = GLOBAL::TILE_SIZE.width(); //Can be used to make the enemy bigger
    float TH  = GLOBAL::TILE_SIZE.height();//^^^^^^^^^^^^^^^

    //0 1 2frames
    //Think of each number being part of an array in the png (Changing enemy, changing color, width of Enemy, Height of Enemy)
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(0, 3*TSH, TSW, TSH).scaled(2*TW, 2*TH));//.scaled can probably help with KingGoomba
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(TSW, 3*TSH, TSW, TSH).scaled(2*TW, 2*TH));
    //"running_f_" is for when it turns around
    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(0, 3*TSH, TSW, TSH).scaled(2*TW, 2*TH).transformed(QTransform().scale(-1,1)));
    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(TSW, 3*TSH, TSW, TSH).scaled(2*TW, 2*TH).transformed(QTransform().scale(-1,1)));

    // for when it dies                              notice it goes 3 to the right(0,1,2)
    m_animator.m_mapStates["die"].push_back(m_texturePixmap.copy(2*TSW, 3*TSH, TSW, TSH).scaled(2*TW, 2*TH));
    m_animator.m_mapStates["die_f_"].push_back(m_texturePixmap.copy(2*TSW, 3*TSH, TSW, TSH).scaled(2*TW, 2*TH).transformed(QTransform().scale(-1,1)));

    m_animator.changeState("running");
    m_animator.m_timeBetweenFrames = 0.5f;
}

void kingGoomba::setAnimation(QString state)
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

QRect kingGoomba::hitBox()
{
    // Define the width and height based on scaling
    float hitboxWidth = 2 * GLOBAL::TILE_SIZE.width();
    float hitboxHeight = 2 * GLOBAL::TILE_SIZE.height();

    // Adjust the vertical offset only by half the scaling difference
    m_offsetY = (hitboxHeight - GLOBAL::TILE_SIZE.height()) / 2.0f;

    // Return the properly adjusted hitbox
    return QRect(position().x(), position().y() + m_offsetY, hitboxWidth, hitboxHeight);
}

void kingGoomba::setDirection(bool isRight)
{
    m_isRight = isRight;
}

int kingGoomba::direction() const
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
