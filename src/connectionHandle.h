#include <amqpcpp.h>
#include <amqpcpp/libevent.h>
class CConnectionHandle : public AMQP::LibEventHandler
{
    void onAttached(AMQP::TcpConnection *connection) override;
    void onConnected(AMQP::TcpConnection *connection) override;
    void onReady(AMQP::TcpConnection *connection) override;
    void onError(AMQP::TcpConnection *connection, const char *message) override;
    void onClosed(AMQP::TcpConnection *connection) override;
    void onDetached(AMQP::TcpConnection *connection) override;
};