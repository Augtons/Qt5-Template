#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QTranslator>

#include "mainwindow.h"

const QString LOCALES[] = { LOCALES_NAME_ARRAY };

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load(QLocale(LOCALES[0]), LOCALE_PREFIX, "_", "./");
    app.installTranslator(&translator);

    MainWindow mv;

    mv.show();

    return QApplication::exec();
}
