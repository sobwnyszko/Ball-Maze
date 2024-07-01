/*!
 * \file
 * \brief plik main.cpp, uruchomienie aplikacji
 */
#include "inc/mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(400, 600);
    w.show();
    return a.exec();
}
