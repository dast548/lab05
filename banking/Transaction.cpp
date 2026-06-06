#include "Transaction.h"

Transaction::Transaction() : fee_(1) {}
Transaction::~Transaction() {}
int Transaction::fee() const { return fee_; }
void Transaction::set_fee(int fee) { fee_ = fee; }

bool Transaction::Make(Account& from, Account& to, int sum) {
    if (sum < 0) throw std::invalid_argument("Sum can not be negative");
    if (sum <= fee_) throw std::logic_error("Sum must be greater than fee");
    if (&from == &to) throw std::logic_error("Accounts must be different");
    from.Lock();
    to.Lock();
    to.ChangeBalance(sum);
    if (from.GetBalance() < sum + fee_) {
        from.ChangeBalance(-sum);
        from.Unlock();
        to.Unlock();
        return false;
    }
    from.ChangeBalance(-(sum + fee_));
    from.Unlock();
    to.Unlock();
    return true;
}
