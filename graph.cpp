#include "graph.h"
#include "constants.h"

Graph :: Graph(){//blank default ctor

}
Graph :: Graph(Graph_Info* graph_info):info(graph_info),plotter(graph_info){//sets graphinfo ptr to argument and makes the plotter object with arg
    
}

void Graph :: set_info(Graph_Info* graph_info){//updates the plotter and graph ptr's graph info
info = graph_info;
plotter.set_info(graph_info);
}


void Graph :: draw(sf::RenderWindow& window){
circle = sf::CircleShape(2);//setting the detials of teh circle, size, color, etc)
circle.setFillColor(sf::Color::White);
circle.setPosition(sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2));
for (int i = 0; i < SCREEN_HEIGHT; i++){//y axis
    circle.setPosition(0-info->domain.x * ((WORK_PANEL)/(info->domain.y - info->domain.x)), i);
    window.draw(circle);
}
for (int i = 0; i < WORK_PANEL; i++){//x axis simple since no vertical panning
    circle.setPosition(i,SCREEN_HEIGHT/2);
    window.draw(circle);
}

for (const auto& pos : screenPoints)//loops through all the points in screenPoints and graphs them
    {
        circle.setPosition(pos);
        // Draw the circle.
        window.draw(circle);
    }

}
void Graph :: update(Graph_Info _info){

if(info->equation == ""){//if the equation is nothing then dont make the points
    
}
else{
    Plot a(info);//create the plot onject with graph info
    screenPoints = a();//generate the points
    a.scalePoints(screenPoints);//scale them from graph coords to screen coords
}
}

void Graph :: zoomIn(){
    info->zoomIn();//zooms in
}

void Graph :: zoomOut(){
    info->zoomOut();//zooms out
}
