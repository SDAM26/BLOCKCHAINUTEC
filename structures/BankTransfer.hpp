#pragma once
#include <iostream>

class BankTransfer {
public:
   std::string sender;
   std::string recipient;
   double amount;
   std::string date;

   BankTransfer();
   BankTransfer(std::string, std::string, double, std::string);
};

BankTransfer::BankTransfer()
    : sender{}, recipient{}, amount{}, date{}
{}

BankTransfer::BankTransfer(std::string sender, 
                           std::string recipient, 
                           double amount, 
                           std::string date)
    : sender{sender},recipient{recipient}, amount{amount}, date{date}
{}




