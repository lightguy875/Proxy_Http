#ifndef PROXY_H
#define PROXY_H

#include <QSize>
#include <QThread>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT_DEFAULT    8228
#define MAXPENDING      5
#define BUFSIZE         4096

class proxy : public QThread
{
    Q_OBJECT

public:
    proxy( in_port_t p=PORT_DEFAULT, QObject* parent = 0 );
    //~proxy();
protected:
    void run() override;

private:
    in_port_t listenPort;
    void dataFromClient(int* sockid);
};

#endif // PROXY_H