#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class Car
{
    public:
    string brand;
    string model;
    int year;
    int originalprice = 10000;
    int currentprice = 10000;
    bool isOwned = false;

    Car(const std::string &mk, const std::string &md, int yr) 
        : brand(mk), model(md), year(yr), originalprice(10000), currentprice(10000), isOwned(false) {}

    string getcar()
    {
        return to_string(year) + " " + brand + " " + model;
    }

    bool buycar(double &usermon)
    {
        if (isOwned == false && usermon >= currentprice)
        {
            isOwned = true;
            usermon -= currentprice;
            redcurp();
            return true;
        }
        else
        {
            return false;
        }
    }
    bool sellcar(double &usermon)
    {
        if (isOwned == true)
        {
            isOwned = false;
            usermon += currentprice;
            redcurp();
            return true;
        }
        else
        {
            return false;
        }  
    }
    private:
    void redcurp()
    {
        currentprice -= 0.10 * originalprice;
        if (currentprice < 0)
        {
            currentprice = 0;
        }
        
    }
};

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    double userMoney = 100000.0;

    Car car1("Lamborghini", "Aventador", 2015);
    Car car2("Ferrari", "sf90", 2020);
    Car car3("Mclaren", "p1", 2018);

    for (int i = 1; i < 11; i++)
    {
        cout << "\n---Transaction " << i << " ---\n";
        int carIndex = rand() % 3;
        int action = rand() % 2;
        bool suc = false;
        if (carIndex == 0)
        {
            if (action == 0)
            {
                suc = car1.buycar(userMoney);
                if (suc)
                {
                    cout << "Bought " << car1.getcar() << "\n";
                }
                else
                {
                    cout << "Couldn't buy " << car1.getcar() << " (already owned or insufficient funds)" <<"\n";
                }
                
            }
            else if (action == 1)
            {
                suc = car1.sellcar(userMoney);
                if(suc)
                {
                    cout << "Sold " << car1.getcar() << "\n";
                }
                else
                {
                    cout << "Couldn't sell " << car1.getcar() << " (Vehicle not owned) \n";
                }
            }
        }
        else if (carIndex == 1)
        {
            if (action == 0)
            {
                suc = car2.buycar(userMoney);
                if (suc)
                {
                    cout << "Bought " << car2.getcar() << "\n";
                }
                else
                {
                    cout << "Couldn't buy " << car2.getcar() << " (already owned or insufficient funds)" <<"\n";
                }
                
            }
            else if (action == 1)
            {
                suc = car2.sellcar(userMoney);
                if(suc)
                {
                    cout << "Sold " << car2.getcar() << "\n";
                }
                else
                {
                    cout << "Couldn't sell " << car2.getcar() << " (Vehicle not owned) \n";
                }
            }
        }
        else if (carIndex == 2)
        {
            if (action == 0)
            {
                suc = car3.buycar(userMoney);
                if (suc)
                {
                    cout << "Bought " << car3.getcar() << "\n";
                }
                else
                {
                    cout << "Couldn't buy " << car3.getcar() << " (already owned or insufficient funds)" <<"\n";
                }
                
            }
            else if (action == 1)
            {
                suc = car3.sellcar(userMoney);
                if(suc)
                {
                    cout << "Sold " << car3.getcar() << "\n";
                }
                else
                {
                    cout << "Couldn't sell " << car3.getcar() << " (Vehicle not owned) \n";
                }
            }
        }
        cout << "User Money: $" << userMoney << "\n";  
    }
    cout << "\n\n--- Final Report After 10 Transactons ---\n";
    cout << "User Money: $" << userMoney << "\n";

    cout << "\nCar1: " << car1.getcar() << "\n";
    cout << "Original Price: $" << car1.originalprice << "\n";
    cout << "Current price: $" << car1.currentprice << "\n";
    cout << "Is Owned: " << (car1.isOwned ? "Yes" : "No") << "\n";

    cout << "\nCar1: " << car2.getcar() << "\n";
    cout << "Original Price: $" << car2.originalprice << "\n";
    cout << "Current price: $" << car2.currentprice << "\n";
    cout << "Is Owned: " << (car2.isOwned ? "Yes" : "No") << "\n";

    cout << "\nCar3: " << car3.getcar() << "\n";
    cout << "Original Price: $" << car3.originalprice << "\n";
    cout << "Current price: $" << car3.currentprice << "\n";
    cout << "Is Owned: " << (car3.isOwned ? "Yes" : "No") << "\n";
}