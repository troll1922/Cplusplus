#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QMainWindow>

class example : public QMainWindow
{
    Q_OBJECT

public:
    example(QWidget *parent = 0);
    ~example();
};

#endif // MARS_EXAMPLE_H
