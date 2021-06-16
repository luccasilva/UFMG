#include "Stack.h"
#include "Queue.h"
#include "Robot.h"
#include "Base.h"
#include "Map.h"

Robot robots[50];
Base base;

void identifyCommand(std::string currentCommand,Map map){

    int robotNumber;
    std::string original = currentCommand;
    std::stringstream strStream(original);
    std::string intermediate;

    //Ordens de Execução
    if (currentCommand.substr(0,6)=="ATIVAR"){
        robotNumber = std::stoi(currentCommand.substr(7,currentCommand.size()));
        robots[robotNumber].Activate(robotNumber);
    }
    else if (currentCommand.substr(0,8)=="EXECUTAR"){
        robotNumber = std::stoi(currentCommand.substr(9,currentCommand.size()));
        robots[robotNumber].Execute(robotNumber,map);
    }
    else if (currentCommand.substr(0,9)=="RELATORIO"){
        robotNumber = std::stoi(currentCommand.substr(10,currentCommand.size()));
        robots[robotNumber].Report();
    }
    else if (currentCommand.substr(0,8)=="RETORNAR"){
        robotNumber = std::stoi(currentCommand.substr(9,currentCommand.size()));
        base.setKillResources(robots[robotNumber].getKill(),robots[robotNumber].getResources());
        robots[robotNumber].Return(robotNumber);
    }

    //Ordens de Comando
    else if (currentCommand.substr(0,5)=="MOVER"){
        getline(strStream, intermediate, ' ');
        getline(strStream, intermediate, ' ');
        robotNumber = std::stoi(intermediate);
        robots[robotNumber].setCommonCommand(currentCommand);
    }
    else if (currentCommand.substr(0,7)=="COLETAR"){
        robotNumber = std::stoi(currentCommand.substr(8,currentCommand.size()));
        robots[robotNumber].setCommonCommand("COLETAR");
    }
    else if (currentCommand.substr(0,8)=="ELIMINAR"){
        robotNumber = std::stoi(currentCommand.substr(9,currentCommand.size()));
        robots[robotNumber].setCommonCommand("ELIMINAR");
    }

    //Ordens de Comando com Prioridade
    else if (currentCommand.substr(0,6)=="*MOVER"){
        getline(strStream, intermediate, ' ');
        getline(strStream, intermediate, ' ');
        robotNumber = std::stoi(intermediate);
        robots[robotNumber].setPriorityCommand(currentCommand);
    }
    else if (currentCommand.substr(0,8)=="*COLETAR"){
        robotNumber = std::stoi(currentCommand.substr(9,currentCommand.size()));
        robots[robotNumber].setPriorityCommand("COLETAR");
    }
    else if (currentCommand.substr(0,9)=="*ELIMINAR"){
        robotNumber = std::stoi(currentCommand.substr(10,currentCommand.size()));
        robots[robotNumber].setPriorityCommand("ELIMINAR");
    }
}

int getHeight(std::string info) {
    int h = std::stoi(info.substr(0, info.find(" ")));
    return h;
}

int getWidth(std::string info) {
    info = info.substr(info.find(" ") + 1, info.size());
    int w = std::stoi(info);
    return w;
}

void readCommands(Map map, std::ifstream &commands){
    std::string strCommand;

    while (std::getline(commands, strCommand)) {
        identifyCommand(strCommand,map);
    }
    commands.close();
}

int main(int argc, char const *argv[]) {

    std::ifstream mapFile(argv[1]);
    std::string mapInfo;
    getline(mapFile, mapInfo);
    int rows = getHeight(mapInfo);
    int cols = getWidth(mapInfo);

    Map map {rows,cols};
    map.readMap(mapFile,rows,cols);
    mapFile.close();

    std::ifstream commands(argv[2]);
    readCommands(map,commands);

    base.endExploration();

    for (int i = 0; i < 50; i++)
        robots[i].~Robot();
    map.deleteMap(rows);
    base.~Base();
    
return 0;
}