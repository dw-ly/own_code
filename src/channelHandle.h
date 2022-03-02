#include <amqpcpp.h>
#include <amqpcpp/libevent.h>
AMQP::Address address("amqp://dwly@47.106.133.127/vhost");
class CChannelHandle : public AMQP::TcpChannel
{
    void onAttached(AMQP::TcpConnection *connection);
    void onConnected(AMQP::TcpConnection *connection);
    void onReady(AMQP::TcpConnection *connection);
    void onError(AMQP::TcpConnection *connection, const char *message);
    void onClosed(AMQP::TcpConnection *connection);
    void onDetached(AMQP::TcpConnection *connection);
};