#include "can_net.h"
#include "debug.h"

#include <QDebug>
#include <QString>

Can_net::Can_net( const QString _dev_name,QObject *parent) : QObject(parent)
{
    m_dev_name = _dev_name;
    int fd = socket( PF_CAN, SOCK_RAW, CAN_RAW);
    if( fd < 0 ){
        Debug::log( _DEBUG_ERROR,"<%s> Fail to creat socket" NONE ,m_dev_name.toLatin1().data());
    }
    m_fd = fd;
    strcpy( m_ifname ,"can0");
    strcpy( m_ifreq.ifr_name ,"can0");
    ioctl(m_fd, SIOCGIFINDEX, &m_ifreq);
    m_canAddr.can_family  = PF_CAN;
    m_canAddr.can_ifindex = m_ifreq.ifr_ifindex;

    memset(&tx_frame,0x00,sizeof(struct can_frame));

    if( bind ( m_fd ,(struct sockaddr*)&m_canAddr ,sizeof(m_canAddr) ) == -1 ){
        Debug::log( _DEBUG_ERROR,"<%s> Fail to BIND socket" NONE ,m_dev_name.toLatin1().data());
        close( m_fd );
    }
    Debug::log( _DEBUG_DETAIL,"<%s> Creat socket" NONE ,m_dev_name.toLatin1().data(),fd);

    m_notifier = new QSocketNotifier( m_fd, QSocketNotifier::Read, this);
    connect (m_notifier, SIGNAL(activated(int)), this, SLOT(slot_receive_frame()));

    tim_transmit = new QTimer();
    tim_transmit->setInterval(1000);
    connect (tim_transmit, SIGNAL( timeout() ), this, SLOT(slot_transmit()));
    tim_transmit->start();
}

Can_net::~Can_net()
{
}



void Can_net::slot_receive_frame()
{
    struct can_frame frame;
    if ( read( m_fd, &frame,sizeof(struct can_frame)) > 0 ){
        int id = frame.can_id & ~0x80000000;
        Debug::log( _DEBUG_DETAIL,"<%s> Rx %08x" NONE ,m_dev_name.toLatin1().data(),id);
    }
    return;
}

void Can_net::
slot_transmit()
{
    tx_frame.can_id = 0x1234 ;
    tx_frame.can_dlc = 8;
    memset(tx_frame.data,0x00,8);
    int ret = write( m_fd,&tx_frame,sizeof(struct can_frame));
    if ( ret < 0 ){
        Debug::log( _DEBUG_ERROR,"<%s> Fail to Tx" NONE ,m_dev_name.toLatin1().data());
    } else {
        Debug::log( _DEBUG_DETAIL,"<%s> Tx %08x" NONE ,m_dev_name.toLatin1().data(),tx_frame.can_id);
    }
    return ;
}
