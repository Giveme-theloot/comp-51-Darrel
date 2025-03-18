#include <iostream>
int main()
{
int temperature;
double budget;
int weathercode;
std::cout << "Greetings please enter the temperature (In degrees Farenheit)" << std::endl;
std::cin >> temperature;
std::cout << "Please enter your budget in dollars (we don't judge 😘 )" << std::endl;
std::cin >> budget;
std::cout << "Now enter the weather using a number the options are listed below" <<
std::endl;
std::cout << "1 = Sunny" << std::endl;
std::cout << "2 = Rainy" << std::endl;
std::cout << "3 = Cloudy" << std::endl;
std::cin >> weathercode;
if((weathercode == 1) && (temperature > 75))
{
if(budget > 20)
{
std::cout << "Go to the beach";
}
else
{
std::cout << "Have a picnic";
}
}
if(weathercode == 2)
{
if(budget > 15)
{
std::cout << "Go to a museum";
}
else
{
std::cout << "Watch TV at home";
}
}
if((weathercode == 3) || (temperature < 60))
{
std::cout << "Visit a coffee shop";
}
}