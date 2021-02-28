#ifndef CAN_NET_H
#define CAN_NET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/time.h>
#include <time.h>
#include <libgen.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdbool.h>
#include <netdb.h>
#include <linux/uinput.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include <QObject>
#include <QSocketNotifier>
#include <QTimer>

class Can_net : public QObject
{
    Q_OBJECT
public:
    Can_net( const QString _dev_name , QObject *parent=0);
    ~Can_net();
    int                     m_can_x;
    int                     m_fd;
    int                     m_id_filted;
    char                    m_ifname[20];
    struct  ifreq           m_ifreq;
    struct  sockaddr_can    m_canAddr;
    QSocketNotifier*        m_notifier;
signals:

public slots:
    void slot_receive_frame();
    void slot_transmit();
private:
    QTimer* tim_transmit;
    QString m_dev_name;
//    int receive(struct can_frame* const frame);
    struct can_frame    tx_frame;

};

#endif // CAN_NET_H
