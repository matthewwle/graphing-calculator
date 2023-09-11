#include "system.h"

#include <iostream>

#include "constants.h"
System::System(){

}
System::System(Graph_Info* graph_info): graph(graph_info)
{
    info = graph_info;
    
}

void System :: set_info(Graph_Info* graph_info){
    info = graph_info;
}

void System::Step(int command, Graph_Info* graph_info){//different commands for different function
    if (command == 4){
        info->panLeft();
    }
    else if (command == 6){
        info->panRight();
    }
    else if (command == 10){
        graph.zoomIn();
    }
    else if (command == 11){
        graph.zoomOut();
    }
    
    graph.update(*info);//updates graph info at end
}


void System::Draw(sf::RenderWindow& window){
    graph.draw(window);
}
