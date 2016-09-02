#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

//CHECKED
//checks if 2048 was reached in the code
//If so, then the game should end (YOU WON!)
bool _2048(vector< vector<int> >& puzzle)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(puzzle.at(i).at(j) == 2048)
            {
                return true;
            }
        }
    }
    return false;
}


//CHECKED
bool has0s(vector< vector<int> >& puzzle)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {   
            if(puzzle.at(i).at(j) == 0)
            {
                return true;
            }
        }
    }
    return false;
}


//CHECKED
//Revise---May want to do a column by column vrsion
bool verticalAdj(vector< vector<int> >& puzzle)
{
    for(int j = 0; j < 4; j++)
    {
        for(int i = 0; i < 3; i++)
        {
            if(puzzle.at(i).at(j) != 0)
            {
                for(int k = i + 1; k < 4; k++)
                {
                    if(puzzle.at(k).at(j) == 0)
                    {
                        continue;
                    }
                    else if(puzzle.at(k).at(j) != puzzle.at(i).at(j))
                    {
                        break;
                    }
                    else if(puzzle.at(k).at(j) == puzzle.at(i).at(j))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
    //***Checks each column for matching numbers 
    //Each run through i means a run through a column
    //Checks for adjacents by runs between pairs, ignoring 0s---until it reaches the end of a column
}


//CHECKED
//Revise---May want to do a row by row version
bool horizontalAdj(vector< vector<int> >& puzzle)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(puzzle.at(i).at(j) != 0)
            {
                for(int k = j + 1; k < 4; k++)
                {
                    if(puzzle.at(i).at(k) == 0)
                    {
                        continue;
                    }
                    else if(puzzle.at(i).at(k) != puzzle.at(i).at(j))
                    {
                        break;
                    }
                    else if(puzzle.at(i).at(k) == puzzle.at(i).at(j))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


//checks if you can keep moving
//If not, the game should end (YOU LOST!)
//What if you get 2048 & no adjacent? Then you WON!

//CHECKED
bool adjacent(vector< vector<int> >& puzzle)
{
    return (verticalAdj(puzzle) || horizontalAdj(puzzle));
}


/////////////////////////////////////////////////////////////////////////////////////////




//slide everything up
void upSlide(vector< vector<int> >& puzzle)
{
    for(int j = 0; j < 4; j++)
    {
        for(int i = 0; i < 4; i++)
        {
            bool filled0 = false;
            if(puzzle.at(i).at(j) == 0)
            {
                for(int k = i+1; k < 4; k++)
                {
                    if(filled0 && puzzle.at(k).at(j) != 0)
                    {
                        if(puzzle.at(i).at(j) == puzzle.at(k).at(j))
                        { 
                            puzzle.at(i).at(j) += puzzle.at(k).at(j);
                            puzzle.at(k).at(j) = 0;
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else if(puzzle.at(k).at(j) != 0)
                    {
                        puzzle.at(i).at(j) = puzzle.at(k).at(j);
                        puzzle.at(k).at(j) = 0;
                        filled0 = true;
                    }
                }
            }
            else
            {
                for(int k = i + 1; k < 4; k++)
                {
                    if(puzzle.at(i).at(j) == puzzle.at(k).at(j))
                    {
                        puzzle.at(i).at(j) += puzzle.at(k).at(j);
                        puzzle.at(k).at(j) = 0;
                        break;
                    }
                    else if(puzzle.at(k).at(j) != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}

void downSlide(vector< vector<int> >& puzzle)
{
    //you go through the columns from the bottom to up
    for(int j = 0; j < 4; j++)
    {
        for(int i = 3; i > 0; i--)
        {
            if(puzzle.at(i).at(j) == 0)
            //case 1: if the pointer points to a 0
            {
                bool filled0 = false;
                for(int k = i - 1; k >= 0; k--)
                {
                    if(filled0 && puzzle.at(k).at(j) != 0)
                    {
                        if(puzzle.at(i).at(j) == puzzle.at(k).at(j))
                        {
                            puzzle.at(i).at(j) += puzzle.at(k).at(j);
                            puzzle.at(k).at(j) = 0;
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }

                    else if(puzzle.at(k).at(j) != 0)
                    {
                        puzzle.at(i).at(j) = puzzle.at(k).at(j);
                        puzzle.at(k).at(j) = 0;
                        filled0 = true;
                        //break;
                        //display(puzzle);
                    }
                }
            }
            else
            {
                for(int k = i-1; k >= 0; k--)
                {
                    if(puzzle.at(i).at(j) == puzzle.at(k).at(j))
                    {
                        puzzle.at(i).at(j) += puzzle.at(k).at(j);
                        puzzle.at(k).at(j) = 0;
                        break;
                    }
                    //Check later
                    else if(puzzle.at(k).at(j) != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}


void leftSlide(vector< vector<int> >& puzzle)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(puzzle.at(i).at(j) == 0)
            {
                bool filled0 = false;
                for(int k = j + 1; k < 4; k++)
                {
                    if(puzzle.at(i).at(k) != 0)
                    {
                        puzzle.at(i).at(j) = puzzle.at(i).at(k);
                        puzzle.at(i).at(k) = 0;
                        filled0 = true;
                        break;
                    }
                    else if(filled0 && puzzle.at(i).at(j) == puzzle.at(i).at(k))
                    {
                        puzzle.at(i).at(j) += puzzle.at(i).at(k);
                        puzzle.at(i).at(k) = 0;
                        break;
                    }
                }
            }
            else
            {
                for(int k = j + 1; k < 4; k++)
                {
                    if(puzzle.at(i).at(j) == puzzle.at(i).at(k))
                    {
                        puzzle.at(i).at(j) += puzzle.at(i).at(k);
                        puzzle.at(i).at(k) = 0;
                        break;
                    }
                    else if(puzzle.at(i).at(k) != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}
void rightSlide(vector< vector<int> >& puzzle)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 3; j >= 0; j--)
        {
            if(puzzle.at(i).at(j) == 0)
            {
                bool filled0 = false;
                for(int k = j - 1; k >= 0; k--)
                {
                    if(puzzle.at(i).at(k) != 0 && !filled0)
                    {
                        puzzle.at(i).at(j) = puzzle.at(i).at(k);
                        puzzle.at(i).at(k) = 0;
                        filled0 = true;
                    }
                    else if(puzzle.at(i).at(k) == puzzle.at(i).at(j) && filled0)
                    {
                        puzzle.at(i).at(j) += puzzle.at(i).at(k);
                        puzzle.at(i).at(k) = 0;
                        break;
                    }
                }
            }
            else
            {
                for(int k = j - 1; k >= 0; k--)
                {
                    if(puzzle.at(i).at(j) == puzzle.at(i).at(k))
                    {
                        puzzle.at(i).at(j) += puzzle.at(i).at(k);
                        puzzle.at(i).at(k) = 0;
                        break;
                    }
                    else if(puzzle.at(i).at(k) != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////



bool checkSame(vector< vector<int> > puzzle, string& choice)
{
    vector< vector<int> > puzzleCopy(4, vector<int>(4));
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            puzzleCopy.at(i).at(j) = puzzle.at(i).at(j);
        }
    }
    if(choice == "up" || choice == "Up")
    {
        upSlide(puzzle);
    }
    else if(choice == "down" || choice == "Down")
    {
        downSlide(puzzle);
    }
    else if(choice == "left" || choice == "Left")
    {
        leftSlide(puzzle);
    }
    else if(choice == "right" || choice == "Right")
    {
        rightSlide(puzzle);
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(puzzle.at(i).at(j) != puzzleCopy.at(i).at(j))
            {
                return false;
            }
        }
    }
    return true;

}


///////////////////////////////////////////////////////////////

//Displays the puzzle
//CHECKED
void display(vector< vector<int> >& puzzle)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << puzzle.at(i).at(j) << " ";
        }
        cout << endl;
    }
}


//Choose, and go in the direction chosen
void choose(vector< vector<int> >& puzzle, bool& willGenerate)
{
    string choice = "";
    cout << "Up, down, left, or right?" << endl;
    if(cin >> choice)
    {
        /*
        switch(cin)
        {
            case "up":
            case "Up":
                upSlide(puzzle);
                break;
            
            case "down":
            case "Down":
                downSlide(puzzle);
                break;
            case "left":
            case "Left":
                leftSlide(puzzle);
                break;
            case "right":
            case "Right":
                rightSlide(puzzle);
                break;
            
            case "quit": case "Quit": case "stop": case "Stop":
                return;
            default:
                cout << "Which direction?" << endl;
                break;
            
        }
        */
        willGenerate = !checkSame(puzzle, choice);
        //What happens if you put a reference into a pass by value parameter?
        if(choice == "up" || choice == "Up")
        {
            upSlide(puzzle);
        }
        else if(choice == "down" || choice == "Down")
        {
            downSlide(puzzle);
        }
        else if(choice == "left" || choice == "Left")
        {
            leftSlide(puzzle);
        }
        else if(choice == "right" || choice == "Right")
        {
            rightSlide(puzzle);
        }
        else if(choice == "Quit" || choice == "quit" || choice == "Stop" || choice == "stop")
        {
            cout << "See you later, Slide Master!" << endl;
            return;
        }
        else
        {
            cout << "Which direction?" << endl;
        }
    }
}

//generates a number on an empty slot

void generateNum(vector< vector<int> >& puzzle)
{
    if(has0s(puzzle))
    {
        srand(time(0));
        int posI = rand() % 4;
        int posJ = rand() % 4;
        while(puzzle.at(posI).at(posJ) != 0)
        {
            posI = rand() % 4;
            posJ = rand() % 4;
        }
        puzzle.at(posI).at(posJ) = 2;
    }
    else
    {
        return;
    }
    //picks a random place
    //if it is 0, then place a 2
    //if it isn't, then redo
    //Do all of while checking that the puzzle has 0s left
}


int main()
{
    //create puzzle
    vector< vector<int> > puzzle(4, vector<int>(4));
    //randomly spawn a 2 in the puzzle
    srand(time(0));
    puzzle.at(rand() % 4).at(rand() % 4) = 2;
    
    //give choice of up, down, left, or right
    //slide anywhere
        //when you slide, check if there are any adjacent same numbers
    //verify if the direction you moved caused anything,
    //if it did, invoke the spawn function (that creates a 2, or 4) in the row/column that you first moved from
    //the program will end when all of the cells are filled (without any *adjacent* same numbers)
    display(puzzle);
    bool ended = false;
    bool willGenerate = false;
    string choice = "";
    while(!ended)
    {
        choose(puzzle, willGenerate);
        if(willGenerate)
        {
            generateNum(puzzle);
        }
        display(puzzle);
        if(_2048(puzzle))
        {
            cout << "You won!" << endl;
            return 0;
        }
        else if(!(has0s(puzzle) || adjacent(puzzle)))
        {
            ended = true;
            cout << "Looks like you lost, game over!" << endl;
        }
    }

    return 0;
}
