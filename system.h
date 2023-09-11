#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "graph.h"
// #include "graph_info.h"

using namespace std;
class System
{
public:
    System();
    System(Graph_Info* graph_info);
    void set_info(Graph_Info* graph_info);
    void Step(int command, Graph_Info* graph_info);
    void Draw(sf::RenderWindow& window);
private:
//    vector<Particle> system;
    Graph graph;
    Graph_Info* info;
};

#endif // SYSTEM_H
