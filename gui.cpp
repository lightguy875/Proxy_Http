#include "gui.h"
#include "ui_gui.h"
#include <stdlib.h>
#include <QString>
#include <QPalette>

const QString COMMAND_P("-p");

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    int numArg = QCoreApplication::arguments().size();

    if( numArg == 3 )
    {
        QString cmd, port_num;
        cmd = QCoreApplication::arguments().at(1);
        port_num = QCoreApplication::arguments().at(2);

        if( cmd.compare(COMMAND_P,Qt::CaseInsensitive) == 0 )
        {
            in_port_t p = port_num.toInt( );
            proxyThread = new proxy( p );
        }
        else
        {
            // Ignore os argumentos
            proxyThread = new proxy();
        }
    }
    else
    {
        proxyThread = new proxy( );
    }

    if(!proxyThread->isRunning())
        proxyThread->start();
    ui->setupUi(this);
}

GUI::~GUI()
{
    proxyThread->exit();
    delete ui;
}
