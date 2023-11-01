#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include "gtest/gtest.h"

int argc = 0;
auto app = QApplication(argc, nullptr);

TEST(MainTest, AboutQt) {
    QApplication::aboutQt();
}

TEST(Main, MessageBox) {
    QMessageBox::information(nullptr, "Hello World", "Hello World");
}
