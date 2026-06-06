#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include "Transaction.h"
#include "mock_account.h"

using ::testing::Return;

TEST(TransactionTest, FeeDefault) {
    Transaction t;
    EXPECT_EQ(t.fee(), 1);
}

TEST(TransactionTest, SetFee) {
    Transaction t;
    t.set_fee(10);
    EXPECT_EQ(t.fee(), 10);
}

TEST(TransactionTest, MakeThrowsWhenSameAccount) {
    Account acc(1, 1000);
    Transaction t;
    t.set_fee(10);
    EXPECT_THROW(t.Make(acc, acc, 100), std::logic_error);
}

TEST(TransactionTest, MakeThrowsWhenSumNegative) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction t;
    EXPECT_THROW(t.Make(from, to, -1), std::invalid_argument);
}

TEST(TransactionTest, MakeThrowsWhenSumLessThanFee) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction t;
    t.set_fee(10);
    EXPECT_THROW(t.Make(from, to, 5), std::logic_error);
}

TEST(TransactionTest, MakeSuccessful) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction t;
    t.set_fee(10);
    bool result = t.Make(from, to, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 890);
    EXPECT_EQ(to.GetBalance(), 600);
}
