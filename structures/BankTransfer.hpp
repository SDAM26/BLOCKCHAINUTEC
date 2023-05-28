
#pragma once
#include <iostream>
#include <ctime>

class BankTransfer {
private:
    double amount;
    std::string sender;
    std::string receiver;
    std::time_t time_stamp;
    std::size_t id_block;
    
public:
    BankTransfer();
    BankTransfer(double amount, std::string sender, std::string receiver, std::time_t time_stamp);
    double getAmount() const;
    std::string getSender() const;
    std::string getReceiver() const;
    std::size_t getIdBlock() const;
    void setIdBlock(std::size_t index);

    friend std::ostream& operator<<(std::ostream& os, const BankTransfer& bankTransfer);
};

BankTransfer::BankTransfer()
    : amount(0.0), sender(""), receiver(""), time_stamp(time(nullptr)), id_block(0)
{}

BankTransfer::BankTransfer(double amount, std::string sender, std::string receiver, std::time_t time_stamp)
    : amount(amount), sender(sender), receiver(receiver), time_stamp(time_stamp), id_block(0)
{}

std::ostream& operator<<(std::ostream& os, const BankTransfer& bankTransfer) {
    os << "Amount: " << bankTransfer.amount << std::endl;
    os << "Sender: " << bankTransfer.sender << std::endl;
    os << "Receiver: " << bankTransfer.receiver << std::endl;
    os << "Time Stamp: " << bankTransfer.time_stamp << std::endl;
    os << "ID Block: " << bankTransfer.id_block << std::endl;
    return os;
}
