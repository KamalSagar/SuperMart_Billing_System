#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>  // For formatting output
using namespace std;

class Bill
{
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(const string& item)
    {
        Item = item;
    }

    void setRate(int rate)
    {
        Rate = rate;
    }

    void setQuant(int quant)
    {
        Quantity = quant;
    }

    string getItem() const
    {
        return Item;
    }

    int getRate() const
    {
        return Rate;
    }

    int getQuant() const
    {
        return Quantity;
    }
};

void addItem(Bill& b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("D:/Bill.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
            }
            out.close();
            cout << "\tItem Added Successfully" << endl;
            Sleep(2000);
        }

        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(2000);
        }
    }
}

void updateItem()
{
    system("cls");
    string item;
    cout << "\tEnter Item Name to Update: ";
    cin >> item;

    ifstream in("D:/Bill.txt");
    ofstream out("D:/Bill Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss;
        ss << line;
        string itemName;
        int itemRate, itemQuant;
        char delimiter;
        ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

        if (item == itemName)
        {
            found = true;
            int newRate, newQuant;
            cout << "\tEnter New Rate: ";
            cin >> newRate;
            cout << "\tEnter New Quantity: ";
            cin >> newQuant;

            out << itemName << " : " << newRate << " : " << newQuant << endl;
            cout << "\tItem Updated Successfully!" << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    if (!found)
    {
        cout << "\tItem Not Found!" << endl;
    }

    out.close();
    in.close();
    remove("D:/Bill.txt");
    rename("D:/Bill Temp.txt", "D:/Bill.txt");
    Sleep(2000);
}

void applyDiscount(double& totalBill)
{
    double discount;
    cout << "\tEnter Discount Percentage: ";
    cin >> discount;
    totalBill -= (totalBill * discount / 100);
    cout << "\tDiscount Applied Successfully!" << endl;
    Sleep(2000);
}

void printBill()
{
    system("cls");
    double totalBill = 0;
    bool close = false;
    while (!close)
    {
        system("cls");
        int choice;
        cout << "\t1. Add Bill" << endl;
        cout << "\t2. Apply Discount" << endl;
        cout << "\t3. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("D:/Bill.txt");
            ofstream out("D:/Bill Temp.txt");

            string line;
            bool found = false;

            while (getline(in, line))
            {
                stringstream ss;
                ss << line;
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName)
                {
                    found = true;
                    if (quant <= itemQuant)
                    {
                        double amount = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << setw(5) << itemName << setw(6) << itemRate << setw(10) << quant << setw(8) << amount << endl;
                        int newQuant = itemQuant - quant;
                        totalBill += amount;

                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    }
                    else
                    {
                        cout << "\tSorry, Insufficient Quantity!" << endl;
                    }
                }
                else
                {
                    out << line << endl;
                }
            }

            if (!found)
            {
                cout << "\tItem Not Available!" << endl;
            }

            out.close();
            in.close();
            remove("D:/Bill.txt");
            rename("D:/Bill Temp.txt", "D:/Bill.txt");
        }
        else if (choice == 2)
        {
            applyDiscount(totalBill);
        }
        else if (choice == 3)
        {
            close = true;
            cout << "\tCalculating Total Bill..." << endl;
        }
        Sleep(2000);
    }
    system("cls");
    cout << endl << "\t Total Bill ----------------- : " << totalBill << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(3000);
}

void generateReceipt(double totalBill)
{
    system("cls");
    string customerName;
    cout << "\tEnter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);

    ofstream receipt("D:/Receipt.txt");
    receipt << "----- Super Mart -----" << endl;
    receipt << "Customer: " << customerName << endl;
    receipt << "Total Bill: " << totalBill << endl;
    receipt << "Thank you for shopping with us!" << endl;
    receipt.close();

    cout << "\tReceipt Generated Successfully!" << endl;
    Sleep(2000);
}

int main()
{
    Bill b;

    bool exit = false;
    while (!exit)
    {
        system("cls");
        int val;

        cout << "\tWelcome To Super Mart Billing System" << endl;
        cout << "\t************************************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Update Item" << endl;
        cout << "\t3. Print Bill" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");
            addItem(b);
        }
        else if (val == 2)
        {
            updateItem();
        }
        else if (val == 3)
        {
            printBill();
            generateReceipt(0);  // Total bill is passed for receipt generation
        }
        else if (val == 4)
        {
            system("cls");
            exit = true;
            cout << "\tGoodbye!" << endl;
            Sleep(2000);
        }
    }
    return 0;
}
