#ifndef SOCKET_HPP

/**
 * \file Socket.hpp
 * \brief Gestion socket
 * \author Benjamin MATHIEU
 * \version 0.9
 * \date 17 avril 2012
 *
 *  Cette librairie générique permet de porter le système des sockets en C vers le C++.
 * Il manque encore un grand nombre de fonctionnalités mais les principales et les plus
 * utilisées sont déjà présentes.
 *
 */

#include <exception>

#define WIN32

#if defined (WIN32)
#include <winsock2.h>
typedef int socklen_t;
#elif defined (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#endif

#include <string>


class SocketException : public std::exception
{
    public:
        virtual const char* what() const throw();
};

class BindException : public SocketException
{
    public:
        virtual const char* what() const throw();
};

class ConnectException : public SocketException
{
    public:
        virtual const char* what() const throw();
};

class ListenException : public SocketException
{
    public:
        virtual const char* what() const throw();
};

class AcceptException : public SocketException
{
    public:
        virtual const char* what() const throw();
};


class Socket
{
        SOCKET sock;
        SOCKET csock;
        bool isServer;
        int domain;
#if defined (WIN32)
        static WSADATA wsadata;
#endif

    public:
        /**
        * \brief Destructeur
        *
        * Destructeur de la classe Socket
        */
        virtual ~Socket();

        /**
        * \brief Constructeur
        *
        * Constructeur par défaut de la classe Socket.
        */
        Socket();

        /**
        * \brief Constructeur
        *
        * Constructeur de la classe Socket
        *
        * \param domain les valeurs possibles sont :AF_UNSPEC, AF_UNIX (pour les communications locales), AF_INET (pour le protocole TCP/IP), AF_IMPLINK, AF_PUP, AF_CHAOS, AF_IPX,
        * AF_NS,AF_ISO,AF_OSI, AF_ISO, AF_ECMA, AF_DATAKIT, AF_CCITT, AF_SNA, AF_DECnet, AF_DLI, AF_LAT, AF_HYLINK, AF_APPLETALK,
        * AF_NETBIOS, AF_VOICEVIEW, AF_FIREFOX, AF_UNKNOWN1, AF_BAN, AF_ATM, AF_INET6, AF_CLUSTER, AF_12844, AF_IRDA, AF_NETDES,
        *
        * \param type indique le type de service, il peut avoir les valeurs suivantes : SOCK_STREAM (si on utilise le protocole TCP/IP),
        * SOCK_DGRAM (si on utilise le protocole UDP/IP),SOCK_RAW, SOCK_RDM, SOCK_SEQPACKET
        *
        * \param protocol pour l'instant à laisser à 0 (valeur par défaut de l'argument);
        */
        Socket(int domain, int type, bool isServer, int protocol = 0);

        /**
        * \brief Constructeur de copie
        *
        * Constructeur de copie de la classe Socket
        */
        Socket(const Socket& other);

        /**
        * \brief Opérateur =
        *
        * Opérateur = de la classe Socket
        */
        Socket& operator=(const Socket& other);

        //Serveur
        /**
        * \brief Lie une socket à un port logiciel de la machine hote de l'application.
        *
        * Lie une socket un port logiciel de la machine hôte de l'application. Le binding de la
        * socket est la première opération à effectuer après sa construction. Une socket non reliée
        * à un port, ne pourra pas communiquer avec le monde extérieur ou même interne de la
        * machine, Ce serait un canal de communication sans émetteur et donc sans information
        * utile pour quelques destinataires que ce soient !
        *
        * \param port est le numéro/identifiant du port machine relié à la socket. Les ports privés sont
        * compris entre 0 et 1023 et les suivants sont publiques (jusque 65535).
        */
        void srvBind(unsigned short port, unsigned long type = INADDR_ANY) throw(BindException);

        /**
        * \brief Permet de dire à la socket qu'elle doit maintenant lancer l'écoute.
        *
        * Permet de dire à la socket qu'elle doit maintenant lancer l'écoute sur le port
        * défini avec la fonction bind. Son utilisation vient donc après un appel à la fonction
        * bind. Autrement, elle ne pourrait aucunement écouter.
        */
        void srvListening(int backlog = 1) throw(ListenException);

        /**
        * \brief Attend qu'une socket cliente vienne demander une communication avec la socket serveur
        */
        void srvAccept() throw(AcceptException);

        //Client
        /**
        * \brief Demande la connection avec une autre socket dite serveur
        */
        void cltConnect(std::string& addr, unsigned short port) throw(ConnectException);

        //send/recv
        /**
        * \brief Envoie les informations contenue dans un tableau de char
        */
        void bthSend(const char* buffer, unsigned bufferSize);

        /**
        * \brief Reçois les informations d'une socket et les mets dans le buffer
        */
        void bthRecv(char* buffer, unsigned bufferSize);

        //shutdown
        /**
        * \brief Permet de bloquer l'envoie/réception d'information.
        */
        void bthShutdown(int how);

        /**
        * \brief Ferme définitivement la socket.
        */
        int bthClose();

        /**
        * \brief A lancer une fois pour toute au début d'un programme utilisant des sockets
        */
        static int initSystem();

        /**
        * \brief A lancer une fois pour toute à la fin d'un programme utilisant des sockets
        */
        static int cleanSystem();

        SOCKET  getSocket();
};
#endif // SOCKET_HPP
