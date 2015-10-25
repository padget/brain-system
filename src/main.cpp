/*
 * main.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: bmathieu
 */

//#include "test/utest/utest.hpp"
#include "test/Socket.hpp"
#include <iostream>

#define TEST_PORT 80
#define TEST_IP "192.168.1.11"

//using namespace brain;
using namespace std;

int testOpenServerSocket() {
    int nbError = 0;
    int domain = AF_INET;
    int type = SOCK_STREAM;
    Socket::initSystem();
    Socket* socket = new Socket(domain, type, true);

    std::cout << "Socket : " << socket->getSocket() << std::endl;

    try {
        std::cout << "Binding..." << std::endl;
        socket->srvBind(TEST_PORT);

        std::cout << "Listening..." << std::endl;
        socket->srvListening(10);
        std::cout << "Accepting (blocking function)..." << std::endl;
        socket->srvAccept();

        while(true) {
            std::cout<<"Accepted\n";
            socket->srvAccept();
            char c[1000];
            socket->bthRecv(c, 1000);
            std::cout << " " << c;
        }
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        nbError = 1;
    }

    socket->bthClose();
    delete socket;
    Socket::cleanSystem();
    system("pause");
    return nbError;
}

int testOpenClientSocket() {
    int nbError = 0;

    int domain = AF_INET;
    int type = SOCK_STREAM;

    Socket::initSystem();
    while(true) {
        Socket* socket = new Socket(domain, type, false);

        std::string addr = TEST_IP;
        socket->cltConnect(addr, TEST_PORT);

        try {
            static std::string str;
            std::cin >> str;
            socket->bthSend(str.c_str(), sizeof(char)*str.size() + sizeof('\0'));
        } catch(std::exception& ex) {
            std::cout << ex.what() << std::endl;
            nbError = 1;
        }

        socket->bthClose();
        delete socket;
    }

    Socket::cleanSystem();
    return nbError;
}

int testSrvReceiveInformation() {
    int nbError = 0;

    return nbError;
}



int main()
{
    testOpenServerSocket();
    //testOpenClientSocket();
    /* test::test_suite < test::meta_test,
         test::system_test,
         test::smart_ptr_test,
         test::scanner_test,
         test::parser_test,
         test::tree_maker_test > ()();
         */

    return 0;
}
