#include "mapmanager.h"
#include <QGraphicsPixmapItem>
#include "../gamescene.h"
#include "../entities/block.h"
#include "../entities/questionblock.h"
#include "../entities/enemy.h"

const QMap<QRgb, QPoint> MapManager::colorToPointOfSpriteMap={
    {qRgb(146, 219, 0  ), QPoint(5 , 0 )},
    {qRgb(146, 146, 0  ), QPoint(4 , 0 )},
    {qRgb(146, 182, 0  ), QPoint(6 , 0 )},
    //{qRgb(181, 165, 213), QPoint(3 , 0)}, //king goomba just in case
    {qRgb(70 , 190, 70 ), QPoint(1 , 1 )},
    {qRgb(145, 219, 145), QPoint(0 , 1 )},
    {qRgb(57 , 244, 57 ), QPoint(2 , 1 )},
    {qRgb(142, 234, 142), QPoint(4 , 1 )},
    {qRgb(143, 185, 143), QPoint(3 , 1 )},
    {qRgb(13 , 142,  13), QPoint(5 , 1 )},
    {qRgb(255, 255, 255), QPoint(7 , 0 )},
    {qRgb(240, 240, 240), QPoint(8 , 0 )},
    {qRgb(235, 235, 235), QPoint(9 , 0 )},
    {qRgb(225, 225, 225), QPoint(7 , 1 )},
    {qRgb(215, 215, 215), QPoint(8 , 1 )},
    {qRgb(205, 205, 205), QPoint(9 , 1 )},
    {qRgb(255, 73 ,  85), QPoint(12, 1 )},
    {qRgb(167, 37 ,  45), QPoint(12, 0 )}
};

const QMap<QRgb, GLOBAL::CELL_TYPE> MapManager::colorToCellMap=
{
    {qRgb(182, 73 ,   0), GLOBAL::CELL_TYPE::Brick0                  },
    {qRgb(245, 228, 156), GLOBAL::CELL_TYPE::Koopa                  }, //MEC 11-27-2024 Declares the koopa color in the png
    {qRgb(255, 255,   0), GLOBAL::CELL_TYPE::Coin                   },
    {qRgb(181, 165 ,   213), GLOBAL::CELL_TYPE::KingGoomba           }, /*2024-12-2 MHS: sets king goomba's specific position*/
    {qRgb(107, 181, 174), GLOBAL::CELL_TYPE::Bowser                   },  /*2024-12-2 MHS: declares bowser's color in the png*/
    {qRgb(255, 163 ,   177), GLOBAL::CELL_TYPE::Hammer           }, /*2024-12-08 TJG: set hammer rgb in png*/
    {qRgb(0  , 146,   0), GLOBAL::CELL_TYPE::TopLeftPipe0           },
    {qRgb(0  , 182,   0), GLOBAL::CELL_TYPE::LeftPipe0              },
    {qRgb(0  , 160,   0), GLOBAL::CELL_TYPE::TopRightPipe0          },
    {qRgb(0  , 200,   0), GLOBAL::CELL_TYPE::RightPipe0             },
    {qRgb(255, 73 ,  85), GLOBAL::CELL_TYPE::QuestionBlock0M        },//MushRoom
    {qRgb(255, 146,  85), GLOBAL::CELL_TYPE::QuestionBlock0         },
    {qRgb(  0,   0,   0), GLOBAL::CELL_TYPE::Wall0                  },
    {qRgb(146,  73,   0), GLOBAL::CELL_TYPE::Wall1                  }
};

const QMap<GLOBAL::CELL_TYPE, QPoint> MapManager::cellToPointOfSpriteMap=   //this uses points using the map16x16.png so you
{
    {GLOBAL::CELL_TYPE::Brick0,                  QPoint(0 , 0)},            //will need to use the same points as topLeftPipe and right (MEC)
    {GLOBAL::CELL_TYPE::Koopa,                  QPoint(1, 0)},  // MEC 11-27-2024 Same as the one in line 31 ^^.
    {GLOBAL::CELL_TYPE::Coin,                   QPoint(-1,-1)},
    {GLOBAL::CELL_TYPE::KingGoomba,              QPoint(0, 20)}, /*2024-12-2 MHS: sets king goomba's specific position*/
    {GLOBAL::CELL_TYPE::Hammer,              QPoint(0, 30)}, /*2024-12-08 TJG: sets hammer*/
    {GLOBAL::CELL_TYPE::Bowser,              QPoint(0, 40)},  /*2024-12-6 MHS: declares bowser's color in the png */
    {GLOBAL::CELL_TYPE::TopLeftPipe0,           QPoint(10, 0)},
    {GLOBAL::CELL_TYPE::LeftPipe0,              QPoint(10, 1)},
    {GLOBAL::CELL_TYPE::TopRightPipe0,          QPoint(11, 0)},
    {GLOBAL::CELL_TYPE::RightPipe0,             QPoint(11, 1)},
    {GLOBAL::CELL_TYPE::QuestionBlock0,          QPoint(6 , 1)},
    {GLOBAL::CELL_TYPE::QuestionBlock0M,          QPoint(6 , 1)},
    {GLOBAL::CELL_TYPE::Wall0,                  QPoint(2 , 0)},
    {GLOBAL::CELL_TYPE::Wall1,                  QPoint(3 , 0)}
    // {GLOBAL::CELL_TYPE::PIPE_FIRST, QPoint(10, 0)}, // MEC| Trying same QPoint as TopleftPipe
    // {GLOBAL::CELL_TYPE::PIPE_LAST, QPoint(11, 0)}
    // {GLOBAL::CELL_TYPE::PIPE_FIRST, QPoint(12, 0)}, // 2024-12-02 TJG: Added PIPE_FIRST sprite point
    //{GLOBAL::CELL_TYPE::PIPE_LAST, QPoint(13, 0)}   // 2024-12-02 TJG: Added PIPE_LAST sprite point
};

const QMap<QRgb, QString> MapManager::colorToEnemy=
{
{qRgb(182, 73 ,   0), "Goomba"                  }
};

const QMap<QRgb, QString> MapManager::colorToKoopa=  //MEC 11/22/2024| Declares color of Koopa
    {
        {qRgb(245, 228, 156), "Koopa"}
};
/*const QMap<QRgb, QString> MapManager::colorToShell= //MEC 11/28/2024| Declares color of Shell
    {
        {qRgb(245, 288, 156), "Shell"}
};*/

const QMap<QRgb, QString> MapManager::colorToKingGoomba=
    {
        {qRgb(181, 165 ,   213), "KingGoomba"                  } /*2024-11-23 MHS: declares king goomba*/
};
/*const QMap<QRgb, QString> MapManager::colorToBowser=
    {
        {qRgb(181, 165 ,   213), "Bowser"                       } /*2024-12-6 MHS: declares bowser's color*/
//};


const QMap<QRgb, QString> MapManager::colorToHammer=
    {
        {qRgb(255, 163 ,   177), "Hammer"                  } /*2024-12-08 TJG: declares hammer*/
};
MapManager::MapManager()
    : 	m_cellSprite(":/res/map16x16.png")
{

}

int MapManager::getMapSketchHeight() const
{
    return m_mapSketch.height();
}

int MapManager::getMapSketchWidth() const
{
    return m_mapSketch.width();
}

int MapManager::getMapWidth() const
{
    return m_map.size();
}

void MapManager::drawBackground(int cameraX, GameScene &scene)
{
    unsigned short map_end = ceil((GLOBAL::SCREEN_SIZE.width() + cameraX) / static_cast<float>(GLOBAL::TILE_SIZE.width()));
    unsigned short map_height = floor(m_mapSketch.height() / 3.f);
    unsigned short map_start = floor(cameraX / static_cast<float>(GLOBAL::TILE_SIZE.width()));


    for (unsigned short a = map_start; a < map_end; a++)
    {
        for (unsigned short b = 0; b < map_height; b++)
        {
            unsigned short sprite_x = 0;
            unsigned short sprite_y = 0;

            QColor pixel = m_mapSketch.pixelColor(a, b + 2 * map_height);
            QRgb pixelRGB = m_mapSketch.pixel(a, b + 2 * map_height);
            if (255 == pixel.alpha())
            {
                if(colorToPointOfSpriteMap.contains(pixelRGB))
                {
                    sprite_x = colorToPointOfSpriteMap[pixelRGB].x();
                    sprite_y = colorToPointOfSpriteMap[pixelRGB].y();
                }

                QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
                pItem->setPos(GLOBAL::TILE_SIZE.width() * a, GLOBAL::TILE_SIZE.width() * b);
                pItem->setPixmap(m_cellSprite.copy(QRect(16*sprite_x, 16*sprite_y, 16, 16)).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
                scene.addItem(pItem);
               // drawScore();
            }

        }
    }

}

void MapManager::drawForeground(int cameraX, GameScene &scene)
{
    unsigned short map_end = ceil((GLOBAL::SCREEN_SIZE.width() + cameraX) / static_cast<float>(GLOBAL::TILE_SIZE.width()));
    unsigned short map_height = floor(m_mapSketch.height() / 3.f);
    unsigned short map_start = floor(cameraX / static_cast<float>(GLOBAL::TILE_SIZE.width()));

    for (unsigned short a = map_start; a < map_end; a++)
    {
        for (unsigned short b = 0; b < map_height; b++)
        {
            foreach(Block* block, Block::BLOCKS)
            {
                if(int(block->position().x()) == int(a*GLOBAL::TILE_SIZE.width())
                        &&
                        int(block->position().y()) == int(b*GLOBAL::TILE_SIZE.height())     )
                {
                    block->draw(scene);
                }
            }
        }
    }
}

void MapManager::setMapCell(const int x, const int y, const GLOBAL::CELL_TYPE &cell)
{
    m_map[x][y] = cell;
}

GLOBAL::CELL_TYPE MapManager::mapCell(int x, int y) const
{
    return m_map[x][y];
}

void MapManager::setMapSize(const int new_size)
{
    m_map.clear();
    m_map.resize(new_size);
}

void MapManager::updateMapSketch(const int current_level)
{
    m_mapSketch.load("://res/sketch_world1-1.png");
}

QRgb MapManager::getMapSketchPixel(const int x, const int y) const
{
    return m_mapSketch.pixel(x, y);
}

void MapManager::convertFromSketch(int currentLevel)
{
    unsigned short map_height;

    updateMapSketch(currentLevel);
    setMapSize(getMapSketchWidth());

    //3 layers: blocks, entities, and background tiles.
    map_height = floor(getMapSketchHeight() / 3.f);

    for (unsigned short a = 0; a < getMapSketchWidth(); a++)
    {
        for (unsigned short b = 0; b < 2 * map_height; b++)
        {
            QRgb pixel = getMapSketchPixel(a, b);

            if (b < map_height)
            {
                setMapCell(a, b, GLOBAL::CELL_TYPE::Empty);
                if(MapManager::colorToCellMap.contains(pixel))
                {
                    setMapCell(a, b, MapManager::colorToCellMap[pixel]);
                }
            }
            else
            {
                if(MapManager::colorToEnemy.contains(pixel))
                {
                    Enemy::CreateEnemy(Enemy::Type::Goomba, QPointF(a*GLOBAL::TILE_SIZE.width(), (b - map_height)*GLOBAL::TILE_SIZE.height() ));
                }
                if(MapManager::colorToKoopa.contains(pixel)){
                    //MEC 11-22-2024 | Adding Koopa into the world when found in sketch_world1-1.png.
                    Enemy::CreateKoopa(Enemy::TypeKoopa::Koopa, QPointF(a*GLOBAL::TILE_SIZE.width(), (b - map_height) * GLOBAL::TILE_SIZE.height() ));
                }

               /* if(MapManager::colorToShell.contains(pixel)){
                    //MEC 11/28/2024 | Adding Shell into the world when found in sketch_world1-1.png
                    Enemy::CreateShell(Enemy::TypeShell::KoopaShell, QPointF(a*GLOBAL::TILE_SIZE.width(), (b-map_height) * GLOBAL::TILE_SIZE.height() ));
                }*/

                /* 2024-11-24 MHS: makes king goomba appear in world */
                if(MapManager::colorToKingGoomba.contains(pixel))
                {
                    Enemy::CreateEnemyKingGoomba(Enemy::TypeKingGoomba::kingGoomba, QPointF(a*GLOBAL::TILE_SIZE.width(), (b - map_height)*GLOBAL::TILE_SIZE.height() ));
                }

                //2024-12-08 TJG: Adds hammer into the world when found in sketch_world1-1.png
                if(MapManager::colorToHammer.contains(pixel))
                {
                    Enemy::CreateEnemyHammer(Enemy::TypeHammer::hammer, QPointF(a*GLOBAL::TILE_SIZE.width(), (b-map_height) * GLOBAL::TILE_SIZE.height() ));
                }
                /* 2024-12-6 MHS: makes bowser appear in world */
               /* if(MapManager::colorToBowser.contains(pixel))
                {
                    Enemy::CreateBowser(Enemy::TypeBowser::Bowser, QPointF(a*GLOBAL::TILE_SIZE.width(), (b - map_height)*GLOBAL::TILE_SIZE.height() ));
                }*/
            }
        }
    }

    //Create Static blocks
    for(int x = 0; x < m_map.size(); ++x)
    {
        for(int y = 0; y < int(m_map.at(0).size()); ++y)
        {
            if(cellToPointOfSpriteMap.contains(m_map[x][y]))
            {
                Block::CreateBlock(m_map[x][y], QPointF(x * GLOBAL::TILE_SIZE.width(), y * GLOBAL::TILE_SIZE.height()));
            }
        }
    }

}
/*
QPointF MapManager::getLastPipePosition() const
{
    /* 2024-12-02 TJG: Added function to return last PIPE_LAST position */
// for (int x = m_map.size() - 1; x >= 0; --x)
// for (int x = 0; x < m_map.size(); ++x)  different way to do it maybe -MEC
/*  {
        //for (int y = m_map.at(x).size() - 1; y >= 0; --y)
       // for(int y = 0; y < int(m_map.at(x).size()); ++y)  same goes for this -MEC
        {
            if (m_map[x][y] == GLOBAL::CELL_TYPE::PIPE_LAST)
            {
                return QPointF(x * GLOBAL::TILE_SIZE.width(), y * GLOBAL::TILE_SIZE.height());
            }
        }
    }
    return QPointF(0, 0); // Default fallback if PIPE_LAST is not found
}
*/
void MapManager::printMap()
{
    qDebug() << "Width: " << m_map.size();
    int height = m_map.at(0).size();
    qDebug() << "Height: " << height;
    for(int x = 0; x < m_map.size(); ++x)
    {
        QString str = "";
        for(int y = 0; y < height; ++y)
        {
            str += "(" + QString::number(x) + " , " + QString::number(x) + " ) => " + GLOBAL::cellTypeToString(m_map[x][y]);
        }
        qDebug() << str;
    }

}
