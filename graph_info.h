#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

struct Graph_Info
{
public:
Graph_Info(){

}
Graph_Info(string _equation, sf::Vector2f _wd, sf::Vector2f ori, sf::Vector2f _scale, sf::Vector2f dom, int num): equation(_equation), windowDimensions(_wd), origin(ori), scale(_scale), domain(dom), numPts(num), range(dom) {

}
void panRight(){
    double diff = 0.2*(domain.y - domain.x);
    domain.x = domain.x+diff;
    domain.y = domain.y+diff;
}

void panLeft(){
    double diff = 0.2*(domain.y - domain.x);
    domain.x = domain.x-diff;
    domain.y = domain.y-diff;
}

void zoomOut(){
    domain.x *= 1.25;
    domain.y *= 1.25;
    range.x *= 1.25;
    range.y *= 1.25;
}

void zoomIn(){
    domain.x *= 0.8;
    domain.y *= 0.8;
    range.x *= 0.8;
    range.y *= 0.8;
}

void editEq(string a){
    equation = a;
}
string equation;
sf::Vector2f windowDimensions;
sf::Vector2f origin;
sf::Vector2f scale;
sf::Vector2f domain;
sf::Vector2f range;
int numPts;

}
;

#endif