#include "systray.h"
#include <QMenu>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

SysTray::SysTray(QWidget *parent) : QWidget(parent)
{
    createWindowLayout();
    createSysTray();
}

SysTray::~SysTray()
{
}

void SysTray::createWindowLayout()
{
    setWindowTitle("Screensaver");

    vLayout = new QVBoxLayout(this);

    QLabel *lbl = new QLabel(this);
    lbl->setText(tr("How many face do you want to generate?"));

    lineEdit = new QLineEdit(this);

    btn = new QPushButton(this);
    btn->setText(tr("OK"));
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btn);

    vLayout->addWidget(lbl);
    vLayout->addWidget(lineEdit);
    vLayout->addLayout(hLayout);

    setLayout(vLayout);

    connect(btn, &QPushButton::clicked, [this](){ createSplashScr(lineEdit->text().toInt());/* this->hide();*/ });
}

void SysTray::createSysTray()
{
    sysTray = new QSystemTrayIcon(QIcon(":/icons/smile.png"), this);
    sysTray->show();

    QMenu *menu = new QMenu(this);

    QAction *quitAct = new QAction(tr("Quit"), menu);

    menu->addAction(quitAct);
    sysTray->setContextMenu(menu);

    connect(quitAct, &QAction::triggered, [this](){ this->close(); });
}

void SysTray::createSplashScr(int num)
{
    for(int i = 0; i < num; ++i) {
        SplashScreen *splashScreen = new SplashScreen(this);
        splashVec.push_back(splashScreen);

        connect(splashScreen, &SplashScreen::reachingBorder, this, &SysTray::clone);
    }
}

void SysTray::clone(int posX, int posY)
{
    SplashScreen *splashScreen = new SplashScreen(this, posX, posY);
    splashVec.push_back(splashScreen);
    connect(splashScreen, &SplashScreen::reachingBorder, this, &SysTray::clone);
}
