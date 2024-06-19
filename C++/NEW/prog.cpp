#include <iostream>
#include <string>
#include <tuple>

int main(void){
    int k;
    int i;

    std::string Name;
    std::tuple <int, char> TpArray[2];

    i = 0;
    k = 0 ;

    std::cin >> std::get<char>(TpArray[k]);

    std::cin;
    
    return 0;
}