#ifndef MYWINDOW_H
#define MYWINDOW_H

#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QSpinBox>
#include<QSlider>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QMainWindow>
#include<math.h>
#include<QTransform>
#include<QMessageBox>
#include<QRegExp>
#include<QRegExpValidator>
#include<QIntValidator>
#include<QTimer>
#include<QMouseEvent>
#include<QPainter>
#define PI 3.14159265

class myWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *mainWidget, *rightWidget, *leftWidget, *graphWidget;
    QLabel *labelInputData, *K1, *V1, *D, *T, *mashtab, *mnozhitel, *KO_answer, *VO_answer;
    QLineEdit *line_K1, *line_V1, *line_D, *line_T;
    QPushButton *btn_calculate, *btn_visual, *btn_clear;
    QSpinBox *spinbox_mash, *spinbox_mnozh;
    QSlider *slider_mash, *slider_mnozh;
    bool controlBool, targetBool, drawPointTarget, drawPointControl, drawResult, visualBool;
    QPoint targetPoint1, controlPoint1, targetPoint2, controlPoint2, targetPointEnd1, targetPointEnd2, controlPointEnd1, targetPointMove, controlPointMove;  //точки относительные и абсолютные
    double R, mashtabScale, mashtabTranslate, spinBoxValueMashtab;
    QTimer *timer;
    int countTime, spinBoxValueTime, timeUser;
    bool checkInputData();
    QRegExpValidator check;
    QIntValidator checkInt;
    QRegExp regExp;
public:
    myWindow(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
public slots:
    void clear();            //очистка графика
    void calculate();        //произведение расчета
    void mashtabSlot();      //масштабирование графика
    void pushButtonVisual();
    void visual();          //визуализация на графике
signals:
    void callVisual();
};

#endif // MYWINDOW_H

