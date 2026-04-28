#ifndef MOCK_TRANSACTION_HPP
#define MOCK_TRANSACTION_HPP

#include "Transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
    MockTransaction() : Transaction() {}
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

#endif
