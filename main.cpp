#include "cub.h"
#include "tetrahedron.h"
#include "sphere.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Cub w;
    Tetrahedron t;
    Sphere s;

    w.show();
    t.show();
    s.show();

    return a.exec();
}
