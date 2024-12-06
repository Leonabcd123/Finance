#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

void showMoney();
void addMoney(int lineNum, double money);
void clearMemory();

int main(){

  int choice;
  bool running = true;
  double money;

  std::cout << "Welcome To Your Finance Manager!\n";

  while (running)
  {
    std::cout << "What Would You Like To Do?\n";
    std::cout << "1. Show Money\n";
    std::cout << "2. Add Income\n";
    std::cout << "3. Add Expense\n";
    std::cout << "4. Clear Memory\n";
    std::cout << "5. Quit\n";
    std::cin >> choice;

    if (std::cin.fail() || std::cin.peek() != '\n')
    {

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid Input.\n";
      continue;
    }

    switch (choice)
    {

    case 1:
      showMoney();
      break;
    
    case 2:
      std::cout << "Enter Your Income:\n";
      std::cin >> money;
      addMoney(1, money);
      break;
    
    case 3:
      std::cout << "Enter Your Income:\n";
      std::cin >> money;
      addMoney(2, money);
      break;

    case 4:
      clearMemory();
      break;

    case 5:
      running = false;
      break;

    default:
      std::cout << "Invalid Input.\n";
      break;
    }

  }

  return 0;
}

void showMoney()
{

  std::ifstream fileIn("money.txt");

  if (!fileIn.is_open()){

    std::cerr << "Failed To Open File.\n";
    return;
  }

  std::string line;
  int lineNumber = 0;
  double income = 0;
  double expenses = 0;

  while (std::getline(fileIn, line))
  {

    if (lineNumber == 0){

      if (line.empty())
      {

        income = 0;
        std::cout << "Income: " << 0 << '$' << '\n';

      }

      else
      {

        income = std::stod(line);
        std::cout << "Income: " << line << '$' << '\n';

      }
    }

    else if (lineNumber == 1)
    {

      if (line.empty())
      {

        expenses = 0;
        std::cout << "Expenses: " << 0 << '$' << '\n';

      }

      else
      {

        expenses = std::stod(line);
        std::cout << "Expenses: " << line << '$' << '\n';

      }
    }

    lineNumber++;
  }

  if (income > expenses)
  {

    std::cout << "You're Making " << income - expenses << "$ Per Month.\n";

  }

  else if (income < expenses)
  {

    std::cout << "You're Losing " << expenses - income << "$ Per Month.\n";

  }

  else
  {

    std::cout << "You're Not Making Any Money.\n";

  }

  fileIn.close();
}

void addMoney(int lineNum, double money){
  
  std::ifstream fileIn("money.txt");
  std::ofstream fileOut("temp.txt");

  if (!fileIn.is_open() || !fileOut.is_open()){

    std::cerr << "File Could Not Be Opened.\n";
    return;

  }

  std::string line;
  int lineNumber = 0;

  while (std::getline(fileIn, line))
  {

    lineNumber++;

    if (lineNumber == lineNum)
    {
      if (!line.empty())
      {

        fileOut << money + std::stod(line) << '\n';

      }

      else
      {

        fileOut << money << '\n';

      }
    }

    else
    {

      fileOut << line << '\n';

    } 
  }

  fileIn.close();
  fileOut.close();

  std::remove("money.txt");
  std::rename("temp.txt", "money.txt");
}

void clearMemory()
{

  std::ofstream fileOut("money.txt");

  if (!fileOut.is_open()){

    std::cerr << "File Could Not Be Opened.\n";
    return;
  }

  fileOut << "\n\n";

  fileOut.close();
}