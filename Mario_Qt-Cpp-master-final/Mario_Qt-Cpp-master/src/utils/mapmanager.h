#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <QRgb>
#include <QImage>
#include <QPixmap>
#include "global.h"

class GameScene;
class MapManager
{
public:
    static const QMap<QRgb, GLOBAL::CELL_TYPE> colorToCellMap;
    static const QMap<GLOBAL::CELL_TYPE, QPoint> cellToPointOfSpriteMap;
    static const QMap<QRgb, QString> colorToEnemy;
    static const QMap<QRgb, QString>  colorToKoopa; //initializes the rgb to Koopa
    static const QMap<QRgb, QString> colorToShell; //MEC 11/28/2024 | initializes the rgb to Shell
    static const QMap<QRgb, QString> colorToKingGoomba; /* 2024-11-24 MHS: initializes it so you can call it on .cpp file */
    static const QMap<QRgb, QString> colorToBowser; /* 2024-12-6 MHS: initializes it so you can call it on .cpp file */
    static const QMap<QRgb, QString> colorToHammer; /* 2024-12-08 TJG: initializes rgb to hammer */
    MapManager();

    int getMapSketchHeight() const;
    int getMapSketchWidth() const;
    int getMapWidth() const;

    void drawBackground(int cameraX, GameScene& scene);
    void drawForeground(int cameraX, GameScene& scene);
    void setMapCell(const int x, const int y, const GLOBAL::CELL_TYPE& cell);
    GLOBAL::CELL_TYPE mapCell(int x, int y) const;
    void setMapSize(const int new_size);
    void updateMapSketch(const int current_level);

    QRgb getMapSketchPixel(const int x, const int y) const;
    void convertFromSketch(int currentLevel);
    void printMap();

     //QPointF getLastPipePosition() const; /* 2024-12-02 TJG: Corrected return type to QPointF */
private:
    QImage m_mapSketch;

    QPixmap m_cellSprite;

    QPixmap m_mapTexture;

    GLOBAL::Map m_map;
    static const QMap<QRgb, QPoint> colorToPointOfSpriteMap;

  //  void drawScore();
   // QPixmap m_allNumbersPixmap;
};
#endif // MAPMANAGER_H
