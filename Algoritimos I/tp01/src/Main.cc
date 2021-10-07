#include "HealthCenter.h"
#include "Person.h"
#include "Sort.h"

int main() {
    healthCenter *HCvec;
    person *Pvec;
    
    std::string dataInfo;
    std::cin >> dataInfo;
    int healthCenterQuantity = std::stoi(dataInfo);
    HCvec = new healthCenter[healthCenterQuantity];

    int in;

    /* ------- LEITURA DOS POSTOS ------- */

    for (int i = 0; i < healthCenterQuantity; i++){
        HCvec[i].setNumber(i);
        std::cin >> dataInfo;
        in = std::stoi(dataInfo);
        HCvec[i].setTotalCapacity(in);
        HCvec[i].setCapacity(in);

        std::cin >> dataInfo;
        in = std::stoi(dataInfo);
        HCvec[i].setXcord(in);

        std::cin >> dataInfo;
        in = std::stoi(dataInfo);
        HCvec[i].setYcord(in);
    }

    /* ------- LEITURA DAS PESSOAS ------- */

    std::cin >> dataInfo;
    int peopleQuantity = std::stoi(dataInfo);
    Pvec = new person[peopleQuantity];

    for (int i = 0; i < peopleQuantity; i++){
        Pvec[i].setNumber(i);

        std::cin >> dataInfo;
        in = std::stoi(dataInfo);
        Pvec[i].setAge(in);

        std::cin >> dataInfo;
        in = std::stoi(dataInfo);
        Pvec[i].setXcord(in);

        std::cin >> dataInfo;
        in = std::stoi(dataInfo);
        Pvec[i].setYcord(in);
    }

    /* ------- ORDENAÇÃO DAS PESSOAS POR IDADE ------- */

    mergeSort2(Pvec,peopleQuantity);

    /* ------- ORDENAÇÃO DOS POSTOS POR DISTANCIA ------- */

    for (int i = 0; i < peopleQuantity; i++){
        quickSort(HCvec,healthCenterQuantity,Pvec[i]);
    
    /* ------- CASAMENTO ------- */

        for (int x = 0; x < healthCenterQuantity; x++){
            if (HCvec[x].getCapacity()>0 && Pvec[i].getHC()==-1){
                HCvec[x].setAlocation(Pvec[i].getNumber(),HCvec[x].getTotalCapacity()-HCvec[x].getCapacity());
                Pvec[i].setHC(HCvec[x].getNumber());
            }
        }
    }

    /* ------- ORDENAÇÃO DOS POSTOS POR ID ------- */

    mergeSort(HCvec,healthCenterQuantity);

    /* ------- SAIDA ------- */

    for (int i = 0; i < healthCenterQuantity; i++){
        if (HCvec[i].getCapacity() != HCvec[i].getTotalCapacity()){
            std::cout << HCvec[i].getNumber() << std::endl;
            for (int x = 0; x < (HCvec[i].getTotalCapacity()-HCvec[i].getCapacity()); x++){
                std::cout << HCvec[i].deQueuePriority(x) << " ";
        }
        std::cout << std::endl;
        }
    }

return 0;
}