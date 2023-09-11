#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
#include "graph_info.h"
#include <fstream>
class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
private:
    ofstream outputStream;
    ifstream inputStream;
    ofstream outputPos;
    ifstream inputPos;
    Graph_Info* info;                   //graph info pointer
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    sf::RectangleShape ZoomIn;          //zoom buttons
    sf::RectangleShape ZoomOut;
    System system;                      //container for all the animated objects
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    sf::Text myTextLabel1;              //text to draw on main screen
    sf::Text ClearHistoryText;
    sf::Text ClearScreenText;
    bool mouseIn;                       //mouse is in the screen
    Sidebar sidebar;                    //rectangular message 
    sf::RectangleShape Textbox;          //textbox shape
    sf::RectangleShape ClearHistoryBox;  
    sf::RectangleShape ClearScreenBox;
    sf::RectangleShape AnswerBox;
    sf::CircleShape circleQ;
    sf::Text questionMark;               
    sf::Text questionAnswer;
    sf::Text TextboxText;               //textbox text
    string userInput;                   //string to hold textbox text
    int historyPos;                     //math val for graph history
    bool status;
    bool justClicked;
    bool question;
};


#endif // GAME_H

