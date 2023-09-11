#ifndef PLOT_H
#define PLOT_H
#include "queue/MyQueue.h"
#include "graph_info.h"
#include "token/token.h"
#include "rpn/rpn.h"
#include "shunting_yard/shunting_yard.h"
#include <SFML/Graphics.hpp>
#include "token/leftparen.h"
#include "token/rightparen.h"
#include <vector>
using namespace std;

class Plot
{
public:
    Plot();
    Plot(Graph_Info* graph_info);
    void set_info(Graph_Info* graph_info);
    vector<sf::Vector2f> operator()();
    void Tokenize();
    void scalePoints(vector<sf::Vector2f>& vec);

private:
Queue<Token*> postFix;
Graph_Info* info;
}
;

#endif