#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"


class Enemy : public Entity
{
public:
    enum class Type{
        None, Goomba
    };
    enum class TypeKoopa{ //MEC 11-22-2024| Making a new type for Koopa.
        None, Koopa
    };
    enum class TypeShell{ //MEC-11-28-2024| Making a new type for Shell.
        None, KoopaShell
    };
    enum class TypeKingGoomba{
        None, kingGoomba /* 2024-11-24 MHS: comment later */
    };
    enum class TypeBowser{
        None, Bowser /*2024-12-6 MHS: making a new type for bowser */
    };
    enum class TypeHammer{
        None, hammer /* 2024-12-08 TJG: New type hammer */
    };
    Enemy(float x, float y);
    virtual ~Enemy();
    virtual QRect hitBox() = 0;
    virtual void update(int cameraX, float elapsedTime) = 0;
    static QList<Enemy*> ENEMIES;
    static void CreateEnemy(Type type, QPointF position);
    static void CreateKoopa(TypeKoopa type, QPointF position); //MEC 11-22-2024| INitializing the Koopa as an enemy
    static void CreateShell(TypeShell type, QPointF position); //MEC 11-28-2024| Initializing the shell as an enemy
    static void CreateEnemyKingGoomba(TypeKingGoomba type, QPointF position); /* 2024-11-23 MHS: to create king goomba in enemy.cpp*/
    static void CreateBowser(TypeBowser type, QPointF position); /* 2024-12-6 MHS: initialize bowser as an enemy*/
    static void CreateEnemyHammer(TypeHammer type, QPointF position); /* 2024-12-08 TJG: to create hammer in enemy.cpp*/
    void setAlive(bool on);
    void setShell(bool on); //MEC 11/28/2024 | Sets value to True
    bool isAlive() const;
    bool isShell() const; //MEC 11/28/2024 | Checks if it ever reaches false
    void startMoving(); //MEC 11/2/2024 | forces the shell to begin moving
private:
    bool m_isAlive;
    bool m_isShell; //MEC 11/28/2024 \ For isShell()
};

#endif // ENEMY_H
