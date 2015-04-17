#include "mywindow.h"

myWindow::myWindow(QWidget *parent) : QMainWindow(parent) //в конструкторе создаем интерфейс программы
{
    setWindowTitle("Тестовая программа");
    setFixedSize(800,500);

    mainWidget = new QWidget(this);
    rightWidget = new QWidget(mainWidget);
    graphWidget = new QWidget(mainWidget);
    leftWidget = new QWidget(graphWidget);

    mainWidget->setGeometry(0, 0, 800, 500);
    graphWidget->setGeometry(0, 0, 400, 500);
    rightWidget->setGeometry(400, 0, 400, 500);
    leftWidget->setGeometry(0, 400, 400, 100);

    QColor myColor(248, 248, 250, 250);

    QPalette pal1;
    pal1.setColor(backgroundRole(), Qt::white);
    setPalette(pal1);

    QPalette pal2;
    pal2.setColor(rightWidget->backgroundRole(), myColor);
    rightWidget->setPalette(pal2);
    rightWidget->setAutoFillBackground(true);

    QPalette pal3;
    pal3.setColor(graphWidget->backgroundRole(), Qt::yellow);
    graphWidget->setPalette(pal3);
    graphWidget->setAutoFillBackground(false);

    QPalette pal4;
    pal4.setColor(leftWidget->backgroundRole(), myColor);
    leftWidget->setPalette(pal4);
    leftWidget->setAutoFillBackground(true);

    K1 = new QLabel("K1, град.");
    V1 = new QLabel("V1, м/с");
    D = new QLabel("D, м");
    T = new QLabel("T, сек.");
    QVBoxLayout *vbl_1 = new QVBoxLayout();
    vbl_1->addWidget(K1);
    vbl_1->addWidget(V1);
    vbl_1->addWidget(D);
    vbl_1->addWidget(T);
    regExp.setPattern("^[0-9]*[.]{1}[0-9]*$");  //шаблон ввода только чисел с плавающей точкой
    check.setRegExp(regExp);
    line_K1 = new QLineEdit();
    line_K1->setValidator(&check);
    line_V1 = new QLineEdit();
    line_V1->setValidator(&check);
    line_D = new QLineEdit();
    line_D->setValidator(&check);
    line_T = new QLineEdit();
    line_T->setValidator(&checkInt);
    QVBoxLayout *vbl_2 = new QVBoxLayout();
    vbl_2->addWidget(line_K1);
    vbl_2->addWidget(line_V1);
    vbl_2->addWidget(line_D);
    vbl_2->addWidget(line_T);

    QHBoxLayout *hbl_inputData = new QHBoxLayout();
    hbl_inputData->addLayout(vbl_1);
    hbl_inputData->addLayout(vbl_2);
    hbl_inputData->setMargin(50);

    mashtab = new QLabel("Масштаб отображения, км");
    mnozhitel = new QLabel("Множитель времени");
    QVBoxLayout *vbl_7 = new QVBoxLayout();
    vbl_7->addWidget(mashtab);
    vbl_7->addWidget(mnozhitel);
    slider_mash = new QSlider(Qt::Horizontal);
    slider_mash->setRange(1,1000);
    slider_mnozh = new QSlider(Qt::Horizontal);
    slider_mnozh->setRange(1,100);
    QVBoxLayout *vbl_8 = new QVBoxLayout();
    vbl_8->addWidget(slider_mash);
    vbl_8->addWidget(slider_mnozh);
    spinbox_mash = new QSpinBox();
    spinbox_mash->setRange(1,1000);
    QHBoxLayout *hbl_1 = new QHBoxLayout();
    hbl_1->addWidget(spinbox_mash);
    spinbox_mnozh = new QSpinBox();
    spinbox_mnozh->setRange(1,100);
    QVBoxLayout *vbl_9 = new QVBoxLayout();
    vbl_9->addLayout(hbl_1);
    vbl_9->addWidget(spinbox_mnozh);
    connect(slider_mash,SIGNAL(valueChanged(int)),spinbox_mash,SLOT(setValue(int)));
    connect(slider_mash,SIGNAL(valueChanged(int)),this,SLOT(mashtabSlot()));
    connect(spinbox_mash,SIGNAL(valueChanged(int)),slider_mash,SLOT(setValue(int)));
    connect(spinbox_mash,SIGNAL(valueChanged(int)),this,SLOT(mashtabSlot()));
    connect(slider_mnozh,SIGNAL(valueChanged(int)),spinbox_mnozh,SLOT(setValue(int)));
    connect(spinbox_mnozh,SIGNAL(valueChanged(int)),slider_mnozh,SLOT(setValue(int)));

    QHBoxLayout *hbl_mashtab = new QHBoxLayout();
    hbl_mashtab->addLayout(vbl_7);
    hbl_mashtab->addLayout(vbl_8);
    hbl_mashtab->addLayout(vbl_9);

    QFont answerFont("Times", 15, QFont::Bold, false);
    KO_answer = new QLabel("K0 = ");
    KO_answer->setFont(answerFont);
    VO_answer = new QLabel("V0 = ");
    VO_answer->setFont(answerFont);
    QVBoxLayout *hbl_answer = new QVBoxLayout();
    hbl_answer->addWidget(VO_answer);
    hbl_answer->addWidget(KO_answer);
    hbl_answer->setAlignment(Qt::AlignCenter);
    hbl_answer->setSpacing(10);
    labelInputData = new QLabel("Ввод данных:",rightWidget);
    labelInputData->setGeometry(150, 20, 200, 20);
    QFont inputFont("Times", 15, QFont::Bold, true);
    labelInputData->setFont(inputFont);
    QVBoxLayout *vbl_right = new QVBoxLayout(rightWidget);
    vbl_right->addLayout(hbl_inputData);
    vbl_right->addLayout(hbl_mashtab);
    vbl_right->addLayout(hbl_answer);

    QFont buttonFont("Times", 13, QFont::Normal, false);
    btn_calculate = new QPushButton("Рассчитать");
    btn_calculate->setFont(buttonFont);
    btn_visual = new QPushButton("Проигрывание");
    btn_visual->setFont(buttonFont);
    btn_clear = new QPushButton("Очистить");
    btn_clear->setFont(buttonFont);
    QHBoxLayout *hbl_button = new QHBoxLayout(leftWidget);
    hbl_button->addWidget(btn_calculate);
    hbl_button->addWidget(btn_visual);
    hbl_button->addWidget(btn_clear);

    drawPointTarget = false;      //заглушки
    drawPointControl = false;
    drawResult = false;       //заглука для изображения графика
    visualBool = false;      //заглука для визуализации
    mashtabScale = 1;
    mashtabTranslate = 0;
    spinBoxValueMashtab=1;   //значение спинбокса влияющего на масштаб
    countTime = 0;
    R = 0;

    connect(btn_clear,SIGNAL(clicked()),this,SLOT(clear()));
    connect(btn_calculate,SIGNAL(clicked()),this,SLOT(calculate()));
    connect(btn_visual,SIGNAL(clicked()),this,SLOT(pushButtonVisual()));

    timer = new QTimer(this);
    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(visual()));
    connect(this,SIGNAL(callVisual()),this, SLOT(visual()));
}

void myWindow::mousePressEvent(QMouseEvent *e)       //записываем позиции точек по нажатию кнопок мыши контрольного и целевого объекта
{
    if ((e->button()==Qt::LeftButton) && (!drawPointTarget))
    {
        targetPoint1 = e->pos();
        targetPoint1.setX(((e->x())*spinBoxValueMashtab)-((200-((400/spinBoxValueMashtab)/2)))*spinBoxValueMashtab); //точки относительно масштаба
        targetPoint1.setY(((e->y())*spinBoxValueMashtab)-((200-((400/spinBoxValueMashtab)/2)))*spinBoxValueMashtab); //точки относительно масштаба
        drawPointTarget = true;
        update();
    }
    else if ((e->button()==Qt::RightButton) && (!drawPointControl))
    {
        controlPoint1 = e->pos();
        controlPoint1.setX(((e->x())*spinBoxValueMashtab)-((200-((400/spinBoxValueMashtab)/2)))*spinBoxValueMashtab); //точки относительно масштаба
        controlPoint1.setY(((e->y())*spinBoxValueMashtab)-((200-((400/spinBoxValueMashtab)/2)))*spinBoxValueMashtab); //точки относительно масштаба
        drawPointControl = true;
        update();
    }
}

void myWindow::paintEvent(QPaintEvent *e)   //отображение и визуализация
{
    QPainter p(this);
    p.setClipRect(0,0,400,400);      //задаем область отображения
    p.drawLine(200, 10, 200, 390);   //отображаем оси
    p.drawLine(10, 200, 390, 200);
    QPoint buf[3];
    buf[0]=QPoint(195,20); buf[1]=QPoint(200,7); buf[2]=QPoint(205,20);
    p.drawPolyline(buf,3);
    buf[0]=QPoint(380,195); buf[1]=QPoint(395,200); buf[2]=QPoint(380,205);
    p.drawPolyline(buf,3);
    p.drawText(210, 20, "y");
    p.drawText(380, 190, "x");
    p.drawText(205, 195, "0.0");
    {
          p.drawLine(50, 10, 50, 390);          //отображаем сетку X
          p.drawLine(100, 10, 100, 390);
          p.drawLine(150, 10, 150, 390);
          p.drawLine(250, 10, 250, 390);
          p.drawLine(300, 10, 300, 390);
          p.drawLine(350, 10, 350, 390);

          p.drawLine(10, 50, 390, 50);          //отображаем сетку Y
          p.drawLine(10, 100, 390, 100);
          p.drawLine(10, 150, 390, 150);
          p.drawLine(10, 250, 390, 250);
          p.drawLine(10, 300, 390, 300);
          p.drawLine(10, 350, 390, 350);
          QString str;
          p.drawText(55, 215, str.setNum(spinBoxValueMashtab*-3));
          p.drawText(105, 215, str.setNum(spinBoxValueMashtab*-2));
          p.drawText(155, 215, str.setNum(spinBoxValueMashtab*-1));
          p.drawText(255, 215, str.setNum(spinBoxValueMashtab*1));
          p.drawText(305, 215, str.setNum(spinBoxValueMashtab*2));
          p.drawText(355, 215, str.setNum(spinBoxValueMashtab*3));
          p.drawText(205, 45, str.setNum(spinBoxValueMashtab*3));
          p.drawText(205, 95, str.setNum(spinBoxValueMashtab*2));
          p.drawText(205, 145, str.setNum(spinBoxValueMashtab*1));
          p.drawText(205, 245, str.setNum(spinBoxValueMashtab*-1));
          p.drawText(205, 295, str.setNum(spinBoxValueMashtab*-2));
          p.drawText(205, 345, str.setNum(spinBoxValueMashtab*-3));
    }

    QString str(line_D->text());          //переводим заданную дистанцию D в число
    R = str.toDouble()/20;                  //масштабируем радиус целевого объекта
    int TWO = 2, FIVE = 5;
    if (mashtabScale!=1) {                                   //масштабируем
            p.translate(mashtabTranslate, mashtabTranslate);
            p.scale(mashtabScale,mashtabScale);
            QString str = spinbox_mash->text();
            int i = str.toInt();
            TWO = 2 * i;
            FIVE = 5 * i;
    }
    if (drawPointTarget) {
        p.setPen(QPen(QBrush(Qt::red),FIVE));
        p.drawPoint(targetPoint1);                    //отрисовываем целевую точку
        targetPoint2.setX(targetPoint1.x()-200);     //пересчитываем координаты относительно центра
        targetPoint2.setY((targetPoint1.y()-200)*(-1));
        QString str2, x, y;
        str2 = " x=" + x.setNum((targetPoint2.x()/50.0),'f',2) + " y=" + y.setNum((targetPoint2.y()/50.0),'f',2);
        p.drawText(targetPoint1, str2);               //отражаем на графике начальные координаты целевого объекта
        p.setPen(QPen(QBrush(Qt::red),TWO));
        p.drawEllipse(targetPoint1,R,R);              //отрисовываем диаметр целевого объекта в начале
    }
    if (drawPointControl) {
        p.setPen(QPen(QBrush(Qt::black),FIVE));
        p.drawPoint(controlPoint1);                  //отрисовываем контрольную точку

        controlPoint2.setX((controlPoint1.x()-200));   //пересчитываем координаты относительно центра
        controlPoint2.setY((controlPoint1.y()-200)*(-1));
        QString str, x, y;
        str = " x=" + x.setNum((controlPoint2.x()/50.0),'f',2) + " y=" + y.setNum((controlPoint2.y()/50.0),'f',2);
        p.drawText(controlPoint1, str);             //отражаем на графике начальные координаты управляемого объекта
    }
    if (drawResult && !visualBool) {                //отрисовываем результат
        p.setPen(QPen(QBrush(Qt::red),TWO));
        p.drawLine(targetPoint1, targetPointEnd1);   //отрисовываем пройденный путь целевого объекта
        p.setPen(QPen(QBrush(Qt::black),TWO));
        p.drawLine(controlPoint1, controlPointEnd1); //отрисовываем пройденный путь управляемого объекта
        p.setPen(QPen(QBrush(Qt::green),TWO));
        p.drawEllipse(targetPointEnd1,R,R);          //отрисовываем диаметр целевого объекта в конце
        p.setPen(QPen(QBrush(Qt::green),FIVE));
        p.drawPoint(targetPointEnd1);               //отрисовываем конечную точку целевого объекта
    }
    if (visualBool && !drawResult) {                 //визуализация результата
        p.setPen(QPen(QBrush(Qt::red),TWO));
        p.drawLine(targetPoint1, targetPointMove);  //отрисовываем пройденный путь целевого объекта в движении

        p.setPen(QPen(QBrush(Qt::black),TWO));
        p.drawLine(controlPoint1, controlPointMove);  //отрисовываем пройденный путь управляемого объекта в движении

        p.setPen(QPen(QBrush(Qt::green),TWO));
        p.drawEllipse(targetPointMove,R,R);           //отрисовываем Диамтер целевого объекта в движении

        p.setPen(QPen(QBrush(Qt::green),FIVE));
        p.drawPoint(targetPointMove);                //отрисовываем точку управляемого объекта в движении
    }
}

void myWindow::clear()    //очищаем график
{
    timer->stop();
    drawPointTarget = false;
    drawPointControl = false;
    drawResult = false;
    visualBool = false;
    VO_answer->setText("V0 =");
    KO_answer->setText("K0 =");
    update();
}

void myWindow::calculate()              //рассчитываем все параметры и рисуем график
{
    if (!checkInputData()) return;
    timer->stop();
    if (drawPointTarget&&drawPointControl) drawResult = true;
    double K1, V1, S, K0, V0, S0;      //S - расстояние пройденное целевым объектом, К1 и V1 задаются пользователем
    QString str = line_K1->text();
    K1 = str.toDouble();               //курс конвертируем в число
    str = line_V1->text();
    V1 = str.toDouble();               //скорость конвертируем в число
    str = line_T->text();
    timeUser = str.toInt();            //время заданное пользователем конвертируем в число
    S = (V1*timeUser)/20;              //пройденный путь целевым объектом
    double lineX = cos(K1*PI/180)*S;   //проекция по оси Х - K1*PI/180-переводим градусы в радианы
    double lineY = sin(K1*PI/180)*S;   //проекция по оси Y
    targetPointEnd1.setX(targetPoint1.x()+lineX);   //координаты конечной точки по Х целевого объекта
    targetPointEnd1.setY(targetPoint1.y()+lineY);   //координаты конечной точки по Y целевого объекта

    QLine lineS0(targetPointEnd1,controlPoint1); //считаем конечную точку управляемого объекта и все оставшиеся данные
    int XlineS0 = lineS0.dx();        //проекция по оси Х
    int YlineS0 = lineS0.dy();        //проекция по оси Y
    S0 = (sqrt(pow(XlineS0,2) + pow(YlineS0,2)))-R;               //находим путь до столкновения управляемого объекта и целевого объекта
    V0 = (S0*20)/timeUser;                                        //находим скорость управляемого объекта
    if (drawPointTarget&&drawPointControl)
    VO_answer->setText("V0 = " + str.setNum(V0,'f',2) + " м/с");  //выводим полученную скорость управляемого объекта на экран

        K0 = atan2(YlineS0,XlineS0)*180/PI;          //находим курс управляемого объекта и расстояние до столкновения
        double K0_print = 0;
    if ((controlPoint1.x()>targetPointEnd1.x())&&(controlPoint1.y()>targetPointEnd1.y())) {
        K0_print = K0 - 180;                            //переводим курс управляемого объекта относительно оси Х по часовой стрелке
        double lineX = cos(K0*PI/180)*S0;                //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin(K0*PI/180)*S0;                //проекция по оси Y
        controlPointEnd1.setX(controlPoint1.x()-lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointEnd1.setY(controlPoint1.y()-lineY);   //координаты конечной точки по Y управляемого объекта
    }
    else if ((controlPoint1.x()<targetPointEnd1.x())&&(controlPoint1.y()>targetPointEnd1.y())){
        K0_print = K0 - 180;
        double lineX = cos((-K0_print)*PI/180)*S0;        //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin((-K0_print)*PI/180)*S0;        //проекция по оси Y
        controlPointEnd1.setX(controlPoint1.x()+lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointEnd1.setY(controlPoint1.y()-lineY);   //координаты конечной точки по Y управляемого объекта
    }
    else if ((controlPoint1.x()>targetPointEnd1.x())&&(controlPoint1.y()<targetPointEnd1.y())){
        K0_print = 180 + K0;
        double lineX = cos((-K0)*PI/180)*S0;        //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin((-K0)*PI/180)*S0;        //проекция по оси Y
        controlPointEnd1.setX(controlPoint1.x()-lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointEnd1.setY(controlPoint1.y()+lineY);   //координаты конечной точки по Y управляемого объекта
    }
    else if ((controlPoint1.x()<targetPointEnd1.x())&&(controlPoint1.y()<targetPointEnd1.y())){
        K0_print = 180 + K0;
        double lineX = cos(K0_print*PI/180)*S0;        //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin(K0_print*PI/180)*S0;        //проекция по оси Y
        controlPointEnd1.setX(controlPoint1.x()+lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointEnd1.setY(controlPoint1.y()+lineY);   //координаты конечной точки по Y управляемого объекта
    }
    if (drawPointTarget&&drawPointControl)
    KO_answer->setText("K0 = " + str.setNum(K0_print*1.0,'f',2) + " град."); //выводим полученный курс управляемого объекта на экран
    visualBool = false;
    update();
}

void myWindow::mashtabSlot()
{
    QString str = spinbox_mash->text();   //масштабируем в зависимости от спинбокса
    spinBoxValueMashtab = str.toInt();
    mashtabScale = 1/spinBoxValueMashtab;
    mashtabTranslate = 200-((400/spinBoxValueMashtab)/2);
    update();
}

void myWindow::pushButtonVisual()   //запускаем визуализацию
{
    if (!checkInputData()) return;
    if (drawPointTarget&&drawPointControl) visualBool = true;
    drawResult = false;
    emit callVisual();                 //вызываем слот myWindow::visual() когда нарисовам график
    targetPointMove = targetPoint1;
    controlPointMove = controlPoint1;
    countTime = 0;        //обнуляем счетчик визуализации, чтоб визуализация пошла занова
}

void myWindow::visual()                //визуализация на графике
{
    QString str2 = spinbox_mnozh->text();
    spinBoxValueTime = str2.toInt();          //считываем значение в спинбоксе

    timer->start(1000/spinBoxValueTime);       //запускаем таймер в зависимости от значения в спинбоксе

    double K1, V1, S;                  //S - расстояние пройденное целевым объектом, К1 и V1 задаются пользователем
    QString str = line_K1->text();
    K1 = str.toDouble();               //курс конвертируем в число
    str = line_V1->text();
    V1 = str.toDouble();               //скорость конвертируем в число
    str = line_T->text();
    timeUser = str.toInt();                //время конвертируем в число
    if (countTime<timeUser){
        S = (V1*(countTime+1))/20;     //пройденный путь целевым объектом за 1 секунду и т.д.
        double lineX = cos(K1*PI/180)*S;   //проекция по оси Х
        double lineY = sin(K1*PI/180)*S;   //проекция по оси Y
        targetPointMove.setX(targetPoint1.x()+lineX);  //прибавляем смещение на каждой итерации
        targetPointMove.setY(targetPoint1.y()+lineY);

        double K1, V1, S;      //S - расстояние пройденное целевым объектом, К1 и V1 задаются пользователем
        QString str = line_K1->text();
        K1 = str.toDouble();               //курс конвертируем в число
        str = line_V1->text();
        V1 = str.toDouble();               //скорость конвертируем в число
        str = line_T->text();
        timeUser = str.toInt();            //время заданное пользователем конвертируем в число
        S = (V1*timeUser)/20;              //пройденный путь целевым объектом
        double lineX_ = cos(K1*PI/180)*S;   //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY_ = sin(K1*PI/180)*S;   //проекция по оси Y
        targetPointEnd1.setX(targetPoint1.x()+lineX_);   //координаты конечной точки по Х целевого объекта
        targetPointEnd1.setY(targetPoint1.y()+lineY_);   //координаты конечной точки по Y целевого объекта

        QLine lineS0(targetPointEnd1,controlPoint1); //считаем конечную точку управляемого объекта и все оставшиеся данные
        int XlineS0 = lineS0.dx();                   //проекция по оси Х
        int YlineS0 = lineS0.dy();                   //проекция по оси Y
        double K0 = atan2(YlineS0,XlineS0)*180/PI;          //находим курс управляемого объекта
        double S0 = ((sqrt(pow(XlineS0,2) + pow(YlineS0,2)))-R);
        double V0 = (S0*20)/timeUser;                                        //находим скорость управляемого объекта
        if (drawPointTarget&&drawPointControl)
        VO_answer->setText("V0 = " + str.setNum(V0,'f',2) + " м/с");  //выводим скорость управляемого объекта на экран
        S0 = (V0*(countTime+1))/20;
        double K0_print = 0;
    if ((controlPoint1.x()>targetPointEnd1.x())&&(controlPoint1.y()>targetPointEnd1.y())) {
        K0_print = K0 - 180;                            //переводим курс управляемого объекта относительно оси Х по часовой стрелке
        double lineX = cos(K0*PI/180)*S0;                //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin(K0*PI/180)*S0;                //проекция по оси Y
        controlPointMove.setX(controlPoint1.x()-lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointMove.setY(controlPoint1.y()-lineY);   //координаты конечной точки по Y управляемого объекта
    }
    else if ((controlPoint1.x()<targetPointEnd1.x())&&(controlPoint1.y()>targetPointEnd1.y())){
        K0_print = K0 - 180;
        double lineX = cos((-K0_print)*PI/180)*S0;        //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin((-K0_print)*PI/180)*S0;        //проекция по оси Y
        controlPointMove.setX(controlPoint1.x()+lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointMove.setY(controlPoint1.y()-lineY);   //координаты конечной точки по Y управляемого объекта
    }
    else if ((controlPoint1.x()>targetPointEnd1.x())&&(controlPoint1.y()<targetPointEnd1.y())){
        K0_print = 180 + K0;
        double lineX = cos((-K0)*PI/180)*S0;        //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin((-K0)*PI/180)*S0;        //проекция по оси Y
        controlPointMove.setX(controlPoint1.x()-lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointMove.setY(controlPoint1.y()+lineY);   //координаты конечной точки по Y управляемого объекта

    }
    else if ((controlPoint1.x()<targetPointEnd1.x())&&(controlPoint1.y()<targetPointEnd1.y())){
        K0_print = 180 + K0;
        double lineX = cos(K0_print*PI/180)*S0;        //проекция по оси Х - K1*PI/180-переводим градусы в радианы
        double lineY = sin(K0_print*PI/180)*S0;        //проекция по оси Y
        controlPointMove.setX(controlPoint1.x()+lineX);   //координаты конечной точки по Х управляемого объекта
        controlPointMove.setY(controlPoint1.y()+lineY);   //координаты конечной точки по Y управляемого объекта
    }
    if (drawPointTarget&&drawPointControl)
    KO_answer->setText("K0 = " + str.setNum(K0_print*1.0,'f',2) + " град.");
        countTime++;       //счетчик визуализации
        update();

    } else {timer->stop(); countTime = 0;}
}


bool myWindow::checkInputData()         //проверяем ввел ли пользователь все данные для расчета
{
    QString strK1, strV1, strD, strT;
    strK1 = line_K1->text();
    strV1 = line_V1->text();
    strD = line_D->text();
    strT = line_T->text();
    if ((strK1.isEmpty()||strV1.isEmpty())||(strT.isEmpty()||strD.isEmpty())){
        QMessageBox msg;
        msg.information(this, "Информация", "Введите данные для расчета");
        return false;
    } else return true;
}

