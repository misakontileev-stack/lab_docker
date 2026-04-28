#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "mocks/MockAccount.hpp"
#include "mocks/MockTransaction.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::AtLeast;

// Тест: попытка перевода на тот же счёт -> исключение
TEST(TransactionTest, SameAccountThrows) {
    MockAccount acc(1, 1000);
    Transaction tx;
    EXPECT_THROW(tx.Make(acc, acc, 200), std::logic_error);
}

// Тест: отрицательная сумма -> исключение
TEST(TransactionTest, NegativeSumThrows) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tx;
    EXPECT_THROW(tx.Make(from, to, -100), std::invalid_argument);
}

// Тест: сумма меньше 100 -> исключение
TEST(TransactionTest, SumTooSmallThrows) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tx;
    EXPECT_THROW(tx.Make(from, to, 50), std::logic_error);
}

// Тест: комиссия слишком большая -> возврат false
TEST(TransactionTest, FeeTooLargeReturnsFalse) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tx;
    tx.set_fee(100);  
    EXPECT_FALSE(tx.Make(from, to, 150));
}

// Успешный перевод (через моки)
TEST(TransactionTest, SuccessfulTransfer) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    // Ожидаем блокировку обоих счетов
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    // Ожидаем вызов Credit(to, sum) -> to.ChangeBalance(sum)
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    // Ожидаем Debit(from, sum+fee) -> from.ChangeBalance(-(sum+fee))
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);  // сумма 200 + fee 1 = 201
    // Разблокировка через деструктор Guard
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);
    Transaction tx;
    tx.set_fee(1);
    EXPECT_TRUE(tx.Make(from, to, 200));
}

// Недостаточно средств на from
TEST(TransactionTest, InsufficientFunds) {
    MockAccount from(1, 100);
    MockAccount to(2, 500);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(150)).Times(1);   // Credit
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(100));
    EXPECT_CALL(to, ChangeBalance(-150)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    Transaction tx;
    tx.set_fee(1);
    EXPECT_FALSE(tx.Make(from, to, 150));
}

// Проверка, что SaveToDataBase вызывается
TEST(TransactionTest, SaveToDataBaseIsCalled) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    MockTransaction tx;   

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);
    EXPECT_CALL(tx, SaveToDataBase(_, _, 200)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    tx.set_fee(1);
    EXPECT_TRUE(tx.Make(from, to, 200));
}
