#include "Socket.hpp"

#if defined (WIN32)
WSADATA Socket::wsadata;
#endif

#include <iostream>

Socket::~Socket()
{
}

Socket::Socket() : sock(0)
{
}

Socket::Socket(int domain, int type,  bool isServer, int protocol): sock(0), csock(0), isServer(isServer), domain(domain)
{
    this->sock = socket(domain, type, protocol);
}

Socket::Socket(const Socket& other): sock(other.sock), csock(other.csock), isServer(other.isServer), domain(other.domain)
{
}

Socket& Socket::operator=(const Socket& other)
{
    if(this != &other)
    {
        this->sock = other.sock;
        this->csock = other.csock;
        this->domain = other.domain;
        this->isServer = other.isServer;
    }

    return *this;
}

void Socket::srvBind(unsigned short port, unsigned long type) throw(BindException)
{
    if(this->isServer)
    {
        SOCKADDR_IN sin;

        sin.sin_addr.s_addr = htonl(type);
        sin.sin_family = this->domain;
        sin.sin_port = htons(port);

        if(bind(this->sock, (SOCKADDR*)&sin, sizeof(sin)) != 0)
        {
            throw BindException();
        }
    }
}

void Socket::srvListening(int backlog) throw(ListenException)
{
    if(this->isServer)
    {
        if(listen(this->sock, backlog) != 0)
        {
            throw ListenException();
        }
    }
}

void Socket::srvAccept() throw(AcceptException)
{
    if(this->isServer)
    {
        SOCKADDR_IN csin;
        socklen_t taille = sizeof(csin);
        this->csock = accept(this->sock, (SOCKADDR*)&csin, &taille);
    }
}

void Socket::cltConnect(std::string& addr, unsigned short port)throw(ConnectException)
{
    if(!this->isServer)
    {
        SOCKADDR_IN sin;

        sin.sin_addr.s_addr = inet_addr(addr.c_str());
        sin.sin_family = this->domain;
        sin.sin_port = htons(port);

        if(connect(this->sock, (SOCKADDR*)&sin, sizeof(sin)) != 0)
        {
            throw ConnectException();
        }
    }
}

void Socket::bthSend(const char* buffer, unsigned bufferSize)
{
    if(this->isServer)
    {
        send(this->csock, buffer, bufferSize, 0);
    }
    else
    {
        send(this->sock, buffer, bufferSize, 0);
    }
}

void Socket::bthRecv(char* buffer, unsigned bufferSize)
{
    if(this->isServer)
    {
        recv(this->csock, buffer, bufferSize, 0);
    }
    else
    {
        recv(this->sock, buffer, bufferSize, 0);
    }
}

void Socket::bthShutdown(int how)
{
    shutdown(this->sock, how);
}

int Socket::bthClose()
{
    return closesocket(sock);
}

int Socket::initSystem()
{
#if defined (WIN32)
    WSADATA WSAData;
    return WSAStartup(MAKEWORD(2, 2), &WSAData);
#else
    return 0;
#endif
}

int Socket::cleanSystem()
{
#if defined (WIN32)
    return WSACleanup();
#else
    return 0;
#endif
}

SOCKET  Socket::getSocket()
{
    return this->sock;
}

const char* SocketException::what() const throw()
{
    return "Il y a un problème avec la socket. Vérifier son paramêtrage.";
}

const char* BindException::what() const throw()
{
    return "Il y a un problème avec le binding de la socket serveur. Vérifier que le port est valide ou disponible";
}

const char* ListenException::what() const throw()
{
    return "Il y a un problème avec le listening de la socket";
}

const char* ConnectException::what() const throw()
{
    return "Il y un problème avec la connection de la socket cliente";
}

const char* AcceptException::what() const throw()
{
    return "Il y a un problème avec la fonction accept de la socket serveur";
}
