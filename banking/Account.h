#pragma once
#include <stdexcept>

class Account {
public:
    Account(int id, int balance);
    virtual ~Account();
    int id() const;
    virtual int GetBalance() const;
    virtual void ChangeBalance(int diff);
    virtual void Lock();
    virtual void Unlock();
private:
    int id_;
    int balance_;
    bool locked_;
};
