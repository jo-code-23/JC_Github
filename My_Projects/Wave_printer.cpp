// Jordan Cruickshank
// 12/11/2020
// Assignment 2 part 1
// Project: 1. write a function that will print a wave of user defined dimensions 
// cin: wave: character, height, amount, speed, pattern, repeat?
// cout: wave(s) of users choice until useer ends program

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//libraries
#include <iostream>
#include <time.h> // required for delay of waves

using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//functions used 

void print_wave_line(char prin_char, int rownum); //function that prints one line of characters
void print_wave_ripple(int wave_height, char prin_char, int wave_trough, const int ms); //function that prints one whole wave one line at a time with a user specified time delay
void error_catch(int & input_num, int min, int max); //function that catches errors in input and re-requests inputs until valid
void wave_creator_3000(int& wave_trough, int& wave_height, int& wave_num, int& ans_speed, int wave_num_min, int wave_num_max, int wave_height_min, int wave_height_max, int speed_min, int speed_max, int& delay, char& prin_char, char& ans_pattern, int& repeat_ans, int choice_min, int choice_max); //main function that requests parameters and feeds info to execute_wave() function
void execute_wave(int& wave_trough, int wave_height, int& wave_num, int wave_num_min, int wave_num_max, int wave_height_min, int wave_height_max, int& delay, char& prin_char, char& ans_pattern, int& repeat_ans, int choice_min, int choice_max); //prints wave of a user defined pattern with predefined values

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//main 

int main()
{
    int wave_trough = 1, wave_height = 1, wave_num = 5, ans_speed = 2, wave_num_min = 1, wave_num_max = 100, wave_height_min = 1, wave_height_max = 100, speed_min = 1, speed_max = 3, delay = 100, repeat_ans = 1, choice_min = 1, choice_max = 3; //declared and defined for use in functions
    //wave_trough-lowest point of wave, wave_height-highest point of wave, wave_num-number of waves, ans_speed-user selected speed rating, all _min/_max-minimun/maximum range of integers. delay-milliseconds between line printing, repeat_ans-value that tells program what path to take
    char prin_char = 'x', ans_pattern = 'y'; //prin_char-uer chosen character, ans_pattern-value that tells program what path to take

    cout << "Hello and welcome to Wave Creator 3000!" << endl; //introduction welcome

    wave_creator_3000(wave_trough, wave_height, wave_num, ans_speed, wave_num_min, wave_num_max, wave_height_min, wave_height_max, speed_min, speed_max, delay, prin_char, ans_pattern, repeat_ans, choice_min, choice_max); //run main wave function

    while (repeat_ans != 3) //if ans is 3: end program
        if (repeat_ans == 1) //as function end with an option to repeat, loop and perform the wave with the already predefined metrics or request and create new wave
            execute_wave(wave_trough, wave_height, wave_num, wave_num_min, wave_num_max, wave_height_min, wave_height_max, delay, prin_char, ans_pattern, repeat_ans, choice_min, choice_max); //if user selects 1: same wave w/ possibl;y diffferent pattern if requested
        else
            wave_creator_3000(wave_trough, wave_height, wave_num, ans_speed, wave_num_min, wave_num_max, wave_height_min, wave_height_max, speed_min, speed_max, delay, prin_char, ans_pattern, repeat_ans, choice_min, choice_max); //if user selects 2: repeat main wave function w/ new values


    cout << "\n\n    /|  " << endl;
    cout << "   / |  " << endl;
    cout << "  /  |  " << endl;
    cout << "~~~~~~~~" << endl;
    cout << "  fin.  " << endl; //End of program message

    return 0;

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//function contents

void error_catch(int & input_num, int min, int max) { //cin value, min and max of desired range
    while (cin.fail() || (input_num < min || input_num > max)) { //conditions of undesired cin, looped until good


        if (cin.fail()) { //in event of non int
            cout << "ERROR45: You have not enetered a number. Please enter a number" << endl; //display error message and instruct user 
            cin.clear(); //clear cin 
            cin.ignore(23, '\n'); //ignore previous 23 inputs (23 more than enough)
            cin >> input_num; //update cin to be tested again
        }

        else if (input_num < min || input_num > max) { //in event of int of invalid value
            cout << "ERROR27: You have entered an invalid number. Please enter a number between " << min << " and " << max << endl; //display error message and instruct user 
            cin.clear(); //clear cin
            cin.ignore(23, '\n');  //ignore previous 23 inputs (23 more than enough)
            cin >> input_num; //update cin to be tested again
        }
    }
}

void print_wave_ripple(int wave_height, char prin_char, int wave_trough, const int ms) { //prints one whole wave. wave height = the desired max characters in a single line. wave_ trough = shortest no. characters in line **requires print_wave_line()**
    for (int j = 1; j < wave_height; j++) { //loop first half of wave (rise)
        clock_t goal = ms + clock(); 
        while (goal > clock()); //delay so when printed mimics wave
        print_wave_line(prin_char, wave_trough++); //call function to print each line and increase no. characters on line until 1 before peak (crest)
    }
    for (int i = wave_trough; i >= 1; i--) // loop for printing of 2nd half of wave (fall) starts at crest and falls to trough = 1
    {
            clock_t goal = ms + clock();
            while (goal > clock()); //delay so when printed mimics wave
        print_wave_line(prin_char, wave_trough--); 
    }

}

void print_wave_line(char prin_char, int charnum) { //prin_char = user defined character. char num = number of characters on any given line
    for (int i = 1; i <= charnum; i++) //loop until desired amount of characters are in one line
    {
        cout << prin_char; //output characters
    }
    cout << endl; //new line once loop satisfied
}

void execute_wave(int& wave_trough, int wave_height, int& wave_num, int wave_num_min, int wave_num_max, int wave_height_min, int wave_height_max, int& delay, char& prin_char, char& ans_pattern, int& repeat_ans, int choice_min, int choice_max) { 
    //prints all waves. recieves user inputs from wave_creator_3000. **required print_wave_ripple()**
    if (wave_num > 1) { //providing more than one wave to be printed

        cout << "\nThe waves can either increase in size or remain the same size throughout.\nWould you prefer them to increase in size? [y/n]" << endl; // user decideds wave patterns
        cin >> ans_pattern;
        while (ans_pattern != 'y' && ans_pattern != 'Y' && ans_pattern != 'n' && ans_pattern != 'N') { //while input is an invalid character
            cout << "ERROR32: Invalid Character. Please enter y or n" << endl; //display error, request new input
            cin >> ans_pattern; //new input
        }


        cout << endl; // line break


        if (ans_pattern == 'n' || ans_pattern == 'N') { // if user selects no
            for (int k = 1; k <= wave_num; k++) // repeat uptil desired number of waves
            {
                print_wave_ripple(wave_height, prin_char, wave_trough, delay); //prints single wave. same wave each time
            }
        }
        else if (ans_pattern == 'y' || ans_pattern == 'Y') { //if user selects yes
            wave_height = wave_height - wave_num + 1; //work out wave height of 1st wave (+1 as first half of wave it 1 less than crest)
            for (int k = 1; k <= wave_num; k++) // repeat uptil desired number of waves
            {
                print_wave_ripple(wave_height, prin_char, wave_trough, delay); //prints a single wave
                wave_height++; //increse the size of each wave by 1 
            }
        }  cout << endl; //line break


    }
    else

        print_wave_ripple(wave_height, prin_char, wave_trough, delay); //single printed wave

    cout << "\nPlease enter 1 to run the wave again with the same parameters\nPlease select 2 to create another wave\nPlease select 3 to end program" << endl; //ask user what they want next
    cin >> repeat_ans; 

    error_catch(repeat_ans, choice_min, choice_max); //make sure valid selection

}

void wave_creator_3000(int& wave_trough, int& wave_height, int& wave_num, int& ans_speed, int wave_num_min, int wave_num_max, int wave_height_min, int wave_height_max, int speed_min, int speed_max, int& delay, char& prin_char, char& ans_pattern, int& repeat_ans, int choice_min, int choice_max) {
    //requests user input and defines variables. to be called by main. **requires execute_wave() and error_catch()**
    cout << "\n\nPlease type the character you would like your waves to consist of and press Enter: " << endl; //define character that wave will consist of 
    cin >> prin_char;
    cout << "\nHow many waves would you like? " << endl; //define no. waves
    cin >> wave_num;

    error_catch(wave_num, wave_num_min, wave_num_max); //check for input errors and correct via user

    cout << "\nHow many characters would you like your largest wave's crest to consist of?" << endl; // define crest
    cin >> wave_height;

    error_catch(wave_height, wave_height_min, wave_height_max); //check for input errors and correct via user


    cout << "\nPlease select the speed setting for the wave: [1/2/3]" << endl; //define delay in code printing
    cin >> ans_speed;

    error_catch(ans_speed, speed_min, speed_max); //check for input errors and correct via user

    if (ans_speed == 1)
        delay = 170; //slowest speed setting 
    else if (ans_speed == 2)
        delay = 100; //medium speed setting 
    else if (ans_speed == 3)
        delay = 50; //fastest speed setting

    execute_wave(wave_trough, wave_height, wave_num, wave_num_min, wave_num_max, wave_height_min, wave_height_max, delay, prin_char, ans_pattern, repeat_ans, choice_min, choice_max); //using newly defined variables, call function that prints all waves
   
}