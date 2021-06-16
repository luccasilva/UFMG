#include <iostream>

int main(){
    long value1=200000;
    long value2;
    long *ptr;
    ptr = &value1;
    //imprima o valor do objeto apontado por long_ptr
    std::cout << *ptr;
    std::cout << " ";
    value2 = *ptr;
    //Imprima o valor de value2
    std::cout << value2;
    std::cout << " ";
    //Imprima o endereço de value1
    std::cout << &value1;
    std::cout << " ";
    //Imprima o endereço armazenado em long_ptr
    std::cout << ptr;
    std::cout << " ";
    
    unsigned int values[5];
    for (int i = 0; i < 5; i++) {
        values[i] = 2 + (i * 2);
    }

    unsigned int *vptr; 
    
    //Imprima a comparação entre o endereço de value1 com o endereço armazenado em long_ptr
    if(&value1 == ptr){
        std::cout << 1 << " ";
      }
    else std::cout << 0 << " ";

    //imprimir os elementos do array values usando notação de array subscrito.
    for (int i = 0; i < 5; i++) {
    std::cout << values[i] << " ";
    }
    
    unsigned int *v_ptr;
    vptr = &values[0];

    //imprimir os elementos do array values usando notação de array ponteiro/deslocamento.

    for (int i = 0; i < 5; i++) {
    std::cout << *vptr << " ";
    vptr++;
    }
    
    //imprimir os elementos do array values usando notação de array ponteiro/deslocamento com o nome de array como o ponteiro.
    for (int i = 0; i < 5; i++) {
    std::cout << *(values + i) << " ";
    }
    
    //imprimir os elementos do array values utilizando subscritos no ponteiro para o array.
    vptr = &values[0];
    
    for (int i = 0; i < 5; i++) {
    std::cout << vptr[i] << " ";
    }
    
    //imprimir o quinto elemento de values utilizando a notação de subscrito de array,
    std::cout << values[4] << " ";
    
    std::cout << *(values + 4) << " ";
    std::cout << vptr[4] << " ";
    std::cout << *(vptr + 4) << " ";
 
    
    //imprimir a comparação entre o valor armazenado em (v_ptr-4) e values[0]
    
    std::cout << vptr + 3 << " ";
    std::cout << *(vptr + 3) << " ";
    
    vptr = &values[4];
    std::cout << vptr - 4 << " ";
    std::cout << *(vptr - 4) << " ";
    
    return 0;
    
}