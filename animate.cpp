#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"
#include <string>


animate::animate():sidebar(WORK_PANEL, SIDE_BAR)

{   
    inputStream.open("results.txt");
    sidebar.fillHistory(inputStream);
    outputStream.open("results.txt");
    sidebar[0] = "Equation History";
    inputPos.open("historypos.txt");
    string a = "";
    if(!inputPos.fail())
        getline(inputPos,a);
    else
        a = "2";
    historyPos = stoi(a);
    outputPos.open("historypos.txt");
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.
    info = new Graph_Info("",sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT), sf::Vector2f(0, 0), sf::Vector2f(1,1), sf::Vector2f(-100,100), 10000);

    //System will be implemented to manage a vector of objects to be animate
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will
    system = System(info);
    window.setFramerateLimit(60);

    status = false;
    mouseIn = true;
    justClicked = false;
    question = false;



    // mousePoint = sf::CircleShape();
    // mousePoint.setRadius(5.0);
    // mousePoint.setFillColor(sf::Color::Red);

    cout<<"Geme CTOR. preparing to load the font."<<endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    

    myTextLabel = sf::Text("Zoom In", font);//zoom in textlabel
    myTextLabel.setCharacterSize(30);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::White);
    myTextLabel.setPosition(sf::Vector2f(WORK_PANEL+75, SCREEN_HEIGHT-65));

    myTextLabel1 = sf::Text("Zoom Out", font);//zoomout text label
    myTextLabel1.setCharacterSize(30);
    myTextLabel1.setStyle(sf::Text::Bold);
    myTextLabel1.setFillColor(sf::Color::White);
    myTextLabel1.setPosition(sf::Vector2f(WORK_PANEL+68, SCREEN_HEIGHT-125));

    ClearHistoryText = sf::Text("Clear History", font);//zoomout text label
    ClearHistoryText.setCharacterSize(25);
    ClearHistoryText.setStyle(sf::Text::Bold);
    ClearHistoryText.setFillColor(sf::Color::White);
    ClearHistoryText.setPosition(sf::Vector2f(WORK_PANEL+58, SCREEN_HEIGHT-184));

    ClearScreenText = sf::Text("Clear Screen", font);//zoomout text label
    ClearScreenText.setCharacterSize(25);
    ClearScreenText.setStyle(sf::Text::Bold);
    ClearScreenText.setFillColor(sf::Color::White);
    ClearScreenText.setPosition(sf::Vector2f(WORK_PANEL+60, SCREEN_HEIGHT-244));

    ZoomIn.setFillColor(sf::Color::Black);//zoom in rectangle button
    ZoomIn.setOutlineColor(sf::Color::Black);
    ZoomIn.setPosition(sf::Vector2f(WORK_PANEL + 35, SCREEN_HEIGHT-70));
    ZoomIn.setSize(sf::Vector2f(200,50));

    ClearHistoryBox.setFillColor(sf::Color::Black);//zoom in rectangle button
    ClearHistoryBox.setOutlineColor(sf::Color::Black);
    ClearHistoryBox.setPosition(sf::Vector2f(WORK_PANEL + 35, SCREEN_HEIGHT-190));
    ClearHistoryBox.setSize(sf::Vector2f(200,50));

    AnswerBox.setFillColor(sf::Color::White);//background for question mark button
    AnswerBox.setOutlineColor(sf::Color::Black);
    AnswerBox.setPosition(sf::Vector2f(WORK_PANEL*0.125, SCREEN_HEIGHT*0.25));
    AnswerBox.setSize(sf::Vector2f(840,560));

    questionAnswer = sf::Text("Use Left and Right arrows to pan\nPress F to make textbox appear/disappear\nClick Enter Key to Zoom In and Shift+Enter to Zoom Out\nClick Clear History to erase past equations\nClick On Equations on the side to bring them back up\nClick Question Mark to make this go away", font);//zoomout text label
    questionAnswer.setCharacterSize(30);//text for the info box
    questionAnswer.setStyle(sf::Text::Bold);
    questionAnswer.setFillColor(sf::Color::Black);
    questionAnswer.setPosition(sf::Vector2f(WORK_PANEL*0.125, SCREEN_HEIGHT*0.25));

    circleQ = sf::CircleShape(20);//question mark circle
    circleQ.setFillColor(sf::Color::White);
    circleQ.setPosition(sf::Vector2f(20,SCREEN_HEIGHT-50));

    questionMark = sf::Text("?", font);//Question Mark Text
    questionMark.setCharacterSize(30);
    questionMark.setStyle(sf::Text::Bold);
    questionMark.setFillColor(sf::Color::Black);
    questionMark.setPosition(sf::Vector2f(30, SCREEN_HEIGHT-50));


    ClearScreenBox.setFillColor(sf::Color::Black);//zoom in rectangle button
    ClearScreenBox.setOutlineColor(sf::Color::Black);
    ClearScreenBox.setPosition(sf::Vector2f(WORK_PANEL + 35, SCREEN_HEIGHT-250));
    ClearScreenBox.setSize(sf::Vector2f(200,50));

    ZoomOut.setFillColor(sf::Color::Black);//zoomout rectangle button
    ZoomOut.setOutlineColor(sf::Color::Black);
    ZoomOut.setPosition(sf::Vector2f(WORK_PANEL + 35, SCREEN_HEIGHT-130));
    ZoomOut.setSize(sf::Vector2f(200,50));

    Textbox.setFillColor(sf::Color::White);//textbox rectangle
    Textbox.setOutlineColor(sf::Color::Black);
    Textbox.setPosition(sf::Vector2f(WORK_PANEL-450, SCREEN_HEIGHT-70));
    Textbox.setSize(sf::Vector2f(400,50));

    TextboxText = sf::Text("", font);//textbox text
    TextboxText.setCharacterSize(30);
    TextboxText.setStyle(sf::Text::Bold);
    TextboxText.setFillColor(sf::Color::Black);
    TextboxText.setPosition(sf::Vector2f(WORK_PANEL-430, SCREEN_HEIGHT-70));

    


    cout<<"animate instantiated successfully."<<endl;
}

void animate::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    
    system.Draw(window);
    if (mouseIn){
        window.draw(mousePoint);
    }
    
    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    window.draw(ZoomIn);//drawing all buttons and texts 
    window.draw(myTextLabel);

    window.draw(ZoomOut);
    window.draw(myTextLabel1);
    if (status){//checks if textbox is toggled
        window.draw(Textbox);
        window.draw(TextboxText);
    }
    
    window.draw(ClearHistoryBox);
    window.draw(ClearHistoryText);
    window.draw(ClearScreenBox);
    window.draw(ClearScreenText);
    window.draw(circleQ);
    window.draw(questionMark);
    if(question){//checks if question mark is toggled
        window.draw(AnswerBox);
        window.draw(questionAnswer);
    }
    
    
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update(){
    //cause changes to the data for the next frame

    system.Step(command, info);
    command = 0;
}
void animate::render(){
       window.clear();
       Draw();
       window.display();
}



void animate::processEvents()
{   
    int bottomLim = 55;//top of each equation button box
    int topLim = 110;//bottom of each equation button box
    int hisLim = 2;//tracker for the amt of equations
    int index = 1;//index of the sidebar
   sf::Event event;
   float mouseX, mouseY;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
           // window closed
           case sf::Event::Closed:
               window.close();
               sidebar.writeHistory(outputStream);//writes to equation history to file and index, closes all streams
               outputPos << historyPos << endl;
               inputPos.close();
               outputPos.close();
               inputStream.close();
               outputStream.close();
               break;
           // key pressed
           case sf::Event::TextEntered:
                if(status){
                if(justClicked){
                    userInput == "";
                    justClicked = false;
                }
                else{
                if (isprint(event.text.unicode))//adds the characters to the userInput string
                    userInput += event.text.unicode; 
                }                  
                }
                break;
           case sf::Event::KeyPressed:
               switch(event.key.code){
                case sf::Keyboard::BackSpace://backspace function for textbox
                    if(status){
                        if (!userInput.empty())
                        userInput.pop_back();
                    }
                    break;
                case sf::Keyboard::Left://pan left
                   command = 4;
                   break;
               case sf::Keyboard::Right://pan right
                   command = 6;
                   break;
               case sf::Keyboard::Escape://close window
                   window.close();
                   sidebar.writeHistory(outputStream);//writes to equation history to file and index, closes all streams
                   cout << historyPos << endl;
                   outputPos << historyPos << endl;
                   inputPos.close();
                    outputPos.close();
                    inputStream.close();
                    outputStream.close();
                case sf::Keyboard::Enter://register the text in textbox to the equation
                    if(status){
                    info->equation = userInput;
                    sidebar[historyPos] = userInput;
                    historyPos+=2;
                    userInput = "";
                    
                    }
                    else{
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))//zooms in and out if shift is pressed
                        info->zoomOut();
                        else
                        info ->zoomIn();
                    }
                    
                    break;
                case sf::Keyboard::F://textbox toggle
                    status = !status;
                    justClicked = true;
                    //userInput = "";
                    
                break;
               }

               break;
           case sf::Event::MouseButtonReleased:   
                        if(sf::Mouse::getPosition(window).x >= 1155 && sf::Mouse::getPosition(window).x <= 1355){//checks mouse position when click happens
                            if(sf::Mouse::getPosition(window).y>=1050 && sf::Mouse::getPosition(window).y<= 1100){//sees if its zoom in
                                command = 10;
                            }
                            else if(sf::Mouse::getPosition(window).y>=990 && sf::Mouse::getPosition(window).y<= 1040){//sees if its zoom out
                                command = 11; 
                            }
                            else if(sf::Mouse::getPosition(window).y>=930 && sf::Mouse::getPosition(window).y <= 980){
                                sidebar.clearHistory();
                                bottomLim = 55;
                                topLim = 110;
                                hisLim = 2;
                                index = 1;
                                historyPos = 1;
                            }
                            else if(sf::Mouse::getPosition(window).y >=870 && sf::Mouse::getPosition(window).y <= 920){
                                info->equation = "0";
                                //window.clear();
                            }
                        }
                        if(sf::Mouse::getPosition(window).x >= WORK_PANEL){//sees if mouse is in the sidebar area
                            double pos = sf::Mouse::getPosition(window).y;//gets y position of mouse
                            for (int i = 0; i < historyPos/2; i++){//loop with math to check which button is being pressed and if its valid
                                if ((pos > bottomLim && pos <= topLim) && (historyPos >= hisLim)){
                                    info->equation = sidebar[index];
                                    break;
                                }
                                    bottomLim += 55;
                                    topLim += 55;
                                    hisLim += 2;
                                    index += 2;
                                
                            }
                            }
                        if(sf::Mouse::getPosition(window).x >= 20 && sf::Mouse::getPosition(window).x <=60){
                            //cout << "HI" << endl;
                            if(sf::Mouse::getPosition(window).y <=SCREEN_HEIGHT-20 && sf::Mouse::getPosition(window).y >= SCREEN_HEIGHT - 55){//questionmark button
                            if(question == false){
                                question = true;
                                //cout << "1" << endl;
                            }
                            else{
                                question = false;
                                //cout << "2" << endl;
                            }
                        }
                        }
                   
                   break;

               default:
                   break;
           }
       }
       if(status)
       TextboxText.setString(userInput);//sets textbox to what the usertyped, allowing users to see what they typed

}
void animate::run()
{
   while (window.isOpen())
   {
       processEvents();
       update();
       render(); //clear/draw/display
   }
   cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

