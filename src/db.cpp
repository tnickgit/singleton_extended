//db.cpp

#include "db.h"

Database* Database::instance = nullptr;



void Database::connect()
{
    connected = "true";
}

void Database::disconnect()
{
    connected = "false";
}

bool Database::isConnected()
{
    return connected == "true";
}   

void* Database::operator new(size_t size)
{
    std::cout << "overloaded new ";
    void* ptr = malloc(size);
    if (!ptr) { throw std::bad_alloc(); }
    return ptr;
}

void Database::operator delete(void* ptr)
{
    std::cout << "overloaded delete ";
    free(ptr);
}

string Database::get_username() const
{
    return username;
}

void Database::set_username(const string newUN)
{
    this->username = newUN;
}

string Database::get_password() const
{
    return password;
}

void Database::set_password(const string newUN)
{
    this->password = newUN;
}

void Database::resetInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

bool Database::isTimeout()
{
    return (std::time(nullptr) - last_activity) > TIMEOUT;
}

void Database::refreshConnection()
{
    this->last_activity = std::time(nullptr);
}

void Database::inactivityDisconnect() 
{
    if (isTimeout())
    {
        disconnect();
    }
}