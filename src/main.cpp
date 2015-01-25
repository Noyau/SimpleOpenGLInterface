#include <QApplication>

#include "glwidget.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GLWidget g;
    g.resize(800, 600);
    g.show();

    return app.exec();
}
