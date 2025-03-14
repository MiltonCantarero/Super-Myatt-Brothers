#include <QApplication>
#include <QIcon>
#include "view.h"

// #include "utils/mapmanager.h" // Include the header for MapManager

// MapManager mapManager; /* 2024-12-02 TJG: Define global mapManager object */

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    View v;
    v.setWindowTitle("Mario Qt/C++ World 1-1");
    v.show();

    return a.exec();
}
