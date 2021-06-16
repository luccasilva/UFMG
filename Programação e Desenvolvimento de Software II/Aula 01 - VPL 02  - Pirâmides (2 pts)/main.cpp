#include <iostream>

main(){
    int asteriscos;
    std::cin >> asteriscos;
    int coluna = 1;
    int linha = 0;
    while (coluna<asteriscos) {
        while (linha<coluna){
            std::cout << '*';
            linha++;
        }
        std::cout << std::endl;
        coluna++;
        linha = 0;
    }
    for (size_t i = 0; i < asteriscos; i++){
        std::cout << '*';
    }
    std::cout << std::endl;
    coluna = 1;
    linha = asteriscos;
    while (coluna<asteriscos) {
        while (linha>coluna){
            std::cout << '*';
            linha--;
        }
        std::cout << std::endl;
        coluna++;
        linha = asteriscos;
    }

}