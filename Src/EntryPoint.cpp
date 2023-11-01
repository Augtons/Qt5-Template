#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QTranslator>

#include "mainwindow.h"

// 这个数组的内容来自 CMakeLists.txt 中对于支持的语言的设置
const char *supportedLocales[] = { LOCALES_NAME_ARRAY };

// 入口 main 函数
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 获取默认 QLocale 对象
    QLocale defaultLocale = []() -> QString {
        QString systemLocale = QLocale::system().name();
        for (const char* local : supportedLocales) {
            if (systemLocale == local) {
                return systemLocale;
            }
        }
        return supportedLocales[0];
    }();

    // 设置 Translator 对象
    QTranslator translator;
    translator.load(defaultLocale, LOCALE_PREFIX, "_", "./");
    app.installTranslator(&translator);

    // 运行主窗口
    MainWindow mv;
    mv.setWindowIcon(QIcon(":/Qt_48x48.ico"));
    mv.show();

    return QApplication::exec();
}
