#include "plot.h"
#include "constants.h"

Plot :: Plot(){

}
Plot :: Plot(Graph_Info* graph_info): info(graph_info){

    Tokenize();//takes graph info's equation and turns the str into tokens
}
void Plot :: set_info(Graph_Info* graph_info){
    info = graph_info;
    
}

void Plot:: Tokenize(){
    string str = info->equation;//sets str to the equation and makes holder strings for each type of token
    string inthold = "";
    string puncthold = "";
    string funchold = "";
    string temp;
    for (int i = 0; i < str.length(); i++){
        char a = toupper(str[i]);//takes the first character of the string in uppercase
        if (a == ' '){//ignores spaces

        }
        
        else{
            if(isdigit(a)){//if digit add to hold                   //logic behind tokenizer: add tokens to respective holds, in each
                    inthold+=a;                                     //if statement check if other holds are empty and if they aren't then
                    if(funchold != ""){                             //push them to the queue, this allows things like double digits and 
                        postFix.push(new Function(funchold));       //trig functinos to be accounted for
                        funchold = "";
                    }
                }
            else if (ispunct(a)){
                if (inthold != "")
                    postFix.push(new Integer(stoi(inthold)));//pushes whatever is in int hold as an integer
                inthold = "";//resets inthold
                if(funchold != ""){
                        postFix.push(new Function(funchold));//pushes whatever is in func hold as a function 
                        funchold = "";//resets funchold
                    }
                puncthold += a;
                if(puncthold == "("){//checks for different parenthesis
                    postFix.push(new LeftParen());
                }
                    
                else if(puncthold == ")"){
                    postFix.push(new RightParen());
                }
                    
                else
                    postFix.push(new Operator(puncthold));//adds operator since there are no 2 char opeartors
                puncthold = "";//resets puncthold
            }
            else{
                if (inthold != "")//same as above
                    postFix.push(new Integer(stoi(inthold)));
                inthold = "";
                
                if(a == 'X'){//if X then push funchold if it isnt empty
                    if (funchold != "")
                    postFix.push(new Function(funchold));
                    funchold = "";
                }
                funchold+= a;//add a
                if(a == 'X' && i != 0)//checks for the missing * operator in 2x for ex
                    if (isdigit(str[i-1])){
                        postFix.push(new Operator("*"));
                    }
                        
            }
            
    }
            
    }
    if (inthold != "")//pushes int to the queue if not empty
        postFix.push(new Integer(stoi(inthold)));
    else if(funchold != ""){//pushes func to the queue if not empty
        postFix.push(new Function(funchold));
    }
}

vector<sf::Vector2f> Plot :: operator()(){//graph points
    ShuntingYard sy;
    postFix = sy.postfix(postFix);//gets the postFix version of the queue of tokens Tokenizer generated
    RPN rpn(postFix);//made a RPN object with postFix as the queue
    vector<sf::Vector2f> points;//vector for the points
    double left = info->domain.x;//left domain 
    double right = info ->domain.y;//right domain
    double diff = (right-left)/(info->numPts-1);//gets the distance between each point 
    double res ;
    for (int i = 0; i < info->numPts; i++){//loops through each x variable and generates the y using rpn then pushes the point to the points vector
        res = rpn(left);
        points.push_back(sf::Vector2f(left, res));
        left += diff;//increments the x according to diff
    }

    return points;
}


void Plot :: scalePoints(vector<sf::Vector2f>& vec){
    double x;
    double y;
    double scale = ((WORK_PANEL)/(info->domain.y - info->domain.x));//the scale between graph coords and x coords
    //double scale = 100;
    for (int i = 0; i < vec.size(); i++){//loops through every single graph coord
        vec[i].x = (vec[i].x - info->domain.x )* scale;//math to convert graph to screen cords
        vec[i].y= SCREEN_HEIGHT - ((vec[i].y -info->range.x) * scale);
    }
}