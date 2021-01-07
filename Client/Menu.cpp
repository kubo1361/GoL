//
// Created by janop on 5. 1. 2021.
//

#include "Menu.h"
Menu::Menu() {

}

Menu::~Menu() {

}

string Menu::start() {
    string rows;
    string cols;
    int startMethod;
    int x;
    int y;
    string count;
    string filename;
    string confirm;
    string living;

    cout << "Welcome to Game of Life" << endl;
    cout << "-----------------------" << endl;
    cout << "O - living cell" << endl;
    cout << ". - dead cell" << endl;
    cout << "-----------------------" << endl;
    cout << endl;


    do {
        cout << "Select a method for preparing starting conditions for your world: " << endl;
        cout << "1. Define living cells yourself" << endl;
        cout << "2. Random distribution of \"x\" living cells" << endl;
        cout << "3. Load configuration from a file" << endl;
        cout << "4. Load configuration from server" << endl;
        cin >> startMethod;
    } while (startMethod < 0 || startMethod > 4);


    if (startMethod == 1 || startMethod == 2) {
        cout << "Enter number of rows and cols for your game" << endl;
        cin >> rows >> cols;
        cout << "Game will start with the world of size: " << rows << "x" << cols << endl;
        cout << "Enter number starting cells: " << endl;
        cin >> count;


        if (startMethod == 1) {
            for (int i = 0; i < stoi(count); i++) {
                cout << "Cell (" << i + 1 << ") Enter the coordinates of cell: " << endl;
                cin >> x >> y;
                living += to_string(x) + ".";
                living += to_string(y) +",";

            }

            string message ="defineCells;"+ rows + ";" + cols + ";" + living;
            return message;
        } else {

            string message = "randomPattern;" +rows + ";" + cols + ";" + count;
            cout << message << endl;
            return message;
        }


    } else if(startMethod == 3){

        while (true) {
            cout << "Enter name of the file to read from: " << endl;
            cin >> filename;

            ifstream readfile(filename);
            if (readfile.is_open()) {
                string fileline, xx, yy;

                getline(readfile, fileline);
                stringstream ss(fileline);

                getline(ss, xx, ' ');
                getline(ss, yy, ' ');

                x= stoi(xx);
                y = stoi(yy);



                while (getline(readfile, fileline)) {
                    stringstream ss(fileline);

                    getline(ss, xx, ' ');
                    getline(ss, yy, ' ');

                    int x2 = stoi(xx);
                    int y2 = stoi(yy);

                    living += to_string(x2) + ".";
                    living += to_string(y2) +",";
                }

            } else {
                cout << "No such file, try again." << endl;
            }
            break;
        }
        string message ="defineCells;"+ rows + ";" + cols + ";" + living;
        return message;
    } else {
        return  "loadPatternNames";
    }

}