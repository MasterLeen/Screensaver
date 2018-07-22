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
    for(int i = 0; i < splashVec.size(); ++i) {
        delete splashVec[i];
    }
}

void SysTray::createWindowLayout()
{
    vLayout = new QVBoxLayout(this);

    QLabel *lbl = new QLabel(this);
    lbl->setText(tr("你想生成多少张笑脸？"));

    lineEdit = new QLineEdit(this);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(lineEdit, Qt::AlignCenter);

    btn = new QPushButton(this);
    btn->setText(tr("确定"));
    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(btn);

    vLayout->addWidget(lbl);
    vLayout->addLayout(hLayout);
    vLayout->addLayout(btnHLayout);

    setLayout(vLayout);

    connect(btn, &QPushButton::clicked, [this](){ createSplashScr(lineEdit->text().toInt()); this->hide(); });
}

void SysTray::createSysTray()
{
    sysTray = new QSystemTrayIcon(QIcon(":/icons/test.png"), this);
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
        SplashScreen *splashScreen = new SplashScreen();
        splashScreen->show();
        splashVec.push_back(splashScreen);
    }
}