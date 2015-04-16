#include <QApplication>
#include<QFont>
#include<mywindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont newFont("Times", 10, QFont::Bold, true);
    a.setFont(newFont);
    myWindow w;
    w.show();

    return a.exec();
}
