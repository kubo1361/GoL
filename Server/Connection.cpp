//
// Created by Eternal on 29/12/2020.
//

#include "Connection.h"

Connection::Connection() {
    this->clientAddressLength = sizeof(clientAddress);
    bzero(&this->clientAddress, this->clientAddressLength);
}

Connection::~Connection() {

}