// Jordan Cruickshank
//28/10/2020
// Dice Game
//Project: create a dice game where 2 players compete to roll 20 in the fewset rolls possible (>20 results in void roll)
//cin: player name, roll command
//cout: current player, roll value, total points, roll number, winner 

#include <iostream>
#include <time.h> // used for generation of random number
using namespace std;

int main()
{
    int rollnum1 = 0, rollnum2 = 0, points1 = 0, points2 = 0, rollval, winnum, rlow, rhigh, rdif, radd; 
    char useranswer;
    string name1, name2, currentplayer;

    cout << "How many points would you like to play to?" << endl; // request point total required
    cin >> winnum; //winning points total

    cout << "What range would you like the dice to have? (e.g. 1 6)" << endl; //request range of dice
    cin >> rlow >> rhigh; // lowest and highest possible rolls

  
    rdif = rhigh - rlow + 1; // working out the range for random number generator
    radd = 0 + rlow; // working out how much needs to be added to range to output numbers within requested range
    

    cout << "Please enter name of player 1: "; //player 1 name allocation
    cin >> name1;

    cout << endl << "Please enter name of player 2: "; //player 2 name allocation
    cin >> name2;
    cout << " " << endl;

    srand(time(NULL)); // generating number 0/1 and allocating which player goes first as a result
    if (rand() % 2 == 0)
    {
        currentplayer = name1;
    }
    else
    {
        currentplayer = name2;
    }
    

    do
    {
        cout << "It is " << currentplayer << "'s turn to go, please press 'r' to roll" << endl; // alert user who is first to go and request action to execute code
        cin >> useranswer;
        if (currentplayer == name1) // execute if its player 1's turn
        {
            if (useranswer == 'r')
            {
                rollval = (rand() % rdif) + radd; // generate random dice roll
                points1 = points1 + rollval; // add roll value to current points total for player 1
                rollnum1 = rollnum1++; // increase roll number of player 1 by 1

                if (points1 < winnum) // if points are below the winning number
                {
                    cout << currentplayer << " rolled a " << rollval << ", you have " << points1 << " points and have rolled " << rollnum1 << " times. " << endl; //output the value of the roll, points total, number of rolls
                }
                if (points1 > winnum) // if points are above winning number
                {
                    points1 = points1 - rollval; // remove the value of the roll from points total
                    cout << currentplayer << " rolled a " << rollval << ", you still have " << points1 << " points and have rolled " << rollnum1 << " times. " << endl; // same but different
                    cout << endl;
                }

            }
            currentplayer = name2; // change the player from 1 to 2 and run similar code to give values to player 2
        }

        else // same applies to other player
        {
            if (useranswer == 'r')
            { 
                rollval = (rand() % rdif) + radd;
                points2 = points2 + rollval;
                rollnum2 = rollnum2++;

                if (points2 < winnum)
                {
                cout << currentplayer << " rolled a " << rollval << ", you have " << points2 << " points and have rolled " << rollnum2 << " times. " << endl;
                }
                if (points2 > winnum)
                {
                points2 = points2 - rollval;
                cout << currentplayer << " rolled a " << rollval << ", you still have " << points2 << " points and have rolled " << rollnum2 << " times. " << endl;
                cout << " " << endl;
                }
            }
            currentplayer = name1;
        }
        
    }
        while (points1 < winnum && points2 < winnum); // loop as long as no one has won yet
    if (points1 == winnum) // if player 1 has won
        cout << name1 << " rolled a " << rollval << ". The winner is " << name1 << " after " << rollnum1 << " rolls!" << endl; // alert winner of how many rolls it took and the roll value that won it
    if (points2 == winnum) //if player 2 won
        cout << name2 << " rolled a " << rollval << ". The winner is " << name2 << " after " << rollnum2 << " rolls!" << endl; //alert them of same info
    return 0;
}