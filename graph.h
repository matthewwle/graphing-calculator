#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include "graph_info.h"
#include "plot.h"
#include <SFML/Graphics.hpp>

using namespace std;
    
class Graph
{
public:
    Graph();
    Graph(Graph_Info* graph_info);
    void set_info(Graph_Info* graph_info);
    void draw(sf::RenderWindow& window);
    void update(Graph_Info _info);
    void zoomIn();
    void zoomOut();

private:
//    vector<Particle> system;
    sf::CircleShape circle;
    Graph_Info* info;;
    Plot plotter;
    vector<sf::Vector2f> screenPoints;
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    
};




#endif