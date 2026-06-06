#pragma once
#include "Account.h"

class Transaction {
public:
    Transaction();
    ~Transaction();
    bool Make(Account& from, Account& to, int sum);
    int fee() const;
    void set_fee(int fee);
private:
    int fee_;
};
