#include "Robot.h"

Robot::Robot(){
  this->Active=false;
  this->Resources=0;
  this->Kill=0;
  this->pos_x=0;
  this->pos_y=0;
}

Robot::~Robot(){
    this->PriorityList.~Stack();
    this->CommandList.~Queue();
    this->History.~Queue();
    this->Active=false;
    this->Resources=0;
    this->Kill=0;
    this->pos_x=0;
    this->pos_y=0;
}

void Robot::Activate(int robotNumber){
    if (this->isActive()){
        std::cout << "BASE: ROBO "<< robotNumber <<" JA ESTA EM MISSAO" << std::endl;
        return;
    }
    else{
    this->Active=true;
    std::cout << "BASE: ROBO "<< robotNumber <<" SAIU EM MISSAO" << std::endl;
    return;
    }
}

void Robot::Execute(int robotNumber, Map map){
    if (!this->isActive()){
        std::cout << "BASE: ROBO "<< robotNumber <<" NAO ESTA EM MISSAO" << std::endl;
        return;
    }
    else{
        std::string currentCommand;

        while (!this->PriorityList.stackIsEmpty()){
            currentCommand = this->popPriorityCommand();

            if(currentCommand == "COLETAR")
                collectNow(robotNumber,map);

            else if(currentCommand == "ELIMINAR")
                killNow(robotNumber,map);

            else if(currentCommand.substr(0,6)=="*MOVER"){
                std::string original = currentCommand;
                std::stringstream strStream(original);
                std::string intermediate;

                getline(strStream, intermediate, '(');
                getline(strStream, intermediate, ',');
                int moveX = std::stoi(intermediate);
                getline(strStream, intermediate, ')');
                int moveY = std::stoi(intermediate);
                
                moveNow(robotNumber,map,moveX,moveY);
            }    
        }

        while (!this->CommandList.queueIsEmpty()){
            currentCommand = this->deQueueCommand();

            if(currentCommand == "COLETAR")
                collectNow(robotNumber,map);

            else if(currentCommand == "ELIMINAR")
                killNow(robotNumber,map);

            else if(currentCommand.substr(0,5)=="MOVER"){
                std::string original = currentCommand;
                std::stringstream strStream(original);
                std::string intermediate;

                getline(strStream, intermediate, '(');
                getline(strStream, intermediate, ',');
                int moveX = std::stoi(intermediate);
                getline(strStream, intermediate, ')');
                int moveY = std::stoi(intermediate);
                
                moveNow(robotNumber,map,moveX,moveY);
            }
        }
    }
}

void Robot::killNow(int robotNumber,Map map){
    std::string historyCom;
    if(map.checkPlace(this->pos_x,this->pos_y)=='H'){
        historyCom = "ROBO " + std::to_string(robotNumber) + ": ALIEN ELIMINADO EM ("+std::to_string(pos_x)+","+std::to_string(pos_y)+")";
        this->setHistory(historyCom);
        map.updatePlace('.',this->pos_x,this->pos_y);
        this->Kill++;
    }
    else{
        historyCom = "ROBO " + std::to_string(robotNumber) + ": IMPOSSIVEL ELIMINAR ALIEN EM ("+std::to_string(pos_x)+","+std::to_string(pos_y)+")";
        this->setHistory(historyCom);
    }
}

void Robot::collectNow(int robotNumber,Map map){
    std::string historyCom;
    if(map.checkPlace(this->pos_x,this->pos_y)=='R'){
        historyCom = "ROBO " + std::to_string(robotNumber) + ": RECURSOS COLETADOS EM ("+std::to_string(pos_x)+","+std::to_string(pos_y)+")";
        this->setHistory(historyCom);
        map.updatePlace('.',this->pos_x,this->pos_y);
        this->Resources++;
    }
    else{
        historyCom = "ROBO " + std::to_string(robotNumber) + ": IMPOSSIVEL COLETAR RECURSOS EM ("+std::to_string(pos_x)+","+std::to_string(pos_y)+")";
        this->setHistory(historyCom);
    }
}

void Robot::moveNow(int robotNumber,Map map,int moveX,int moveY){

    std::string historyCom;
    if(map.checkPlace(moveX,moveY)=='O'){
        historyCom = "ROBO " + std::to_string(robotNumber) + ": IMPOSSIVEL MOVER PARA ("+std::to_string(moveX)+","+std::to_string(moveY)+")";
        this->setHistory(historyCom);
        return;
    }
    else{
        this->pos_x = moveX;
        this->pos_y = moveY;
        historyCom = "ROBO " + std::to_string(robotNumber) + ": MOVEU PARA ("+std::to_string(pos_x)+","+std::to_string(pos_y)+")";
        this->setHistory(historyCom);
        return;
    }
}

void Robot::Report(){
    while (!this->History.queueIsEmpty()){
        std::cout << History.deQueue() << std::endl;
    }
}   

void Robot::Return(int robotNumber){
    if (!this->isActive()){
        std::cout << "BASE: ROBO "<< robotNumber <<" NAO ESTA EM MISSAO" << std::endl;
        return;
    }
    else{
        std::cout << "BASE: ROBO "<< robotNumber <<" RETORNOU ALIENS "<< this->getKill() <<" RECURSOS "<< this->getResources() << std::endl;
        this->History.cleanQueue();
        this->Kill = 0;
        this->Resources = 0;
        this->pos_x = 0;
        this->pos_y = 0;
        this->Active = false;
        return;
    }
}

void Robot::setKill(){
    this->Kill++;
}

int Robot::getKill(){
    return this->Kill;
}

void Robot::setResources(){
    this->Resources++;
}

int Robot::getResources(){
    return this->Resources;
}

bool Robot::isActive(){
    return this->Active;
}

void Robot::setCommonCommand(std::string command){
    this->CommandList.toQueue(command);
}

void Robot::setHistory(std::string command){
    this->History.toQueue(command);
}

void Robot::setPriorityCommand(std::string command){
    this->PriorityList.pushStack(command);
}

std::string Robot::deQueueCommand(){
    return this->CommandList.deQueue();
}

std::string Robot::popPriorityCommand(){
    return this->PriorityList.popStack();
}