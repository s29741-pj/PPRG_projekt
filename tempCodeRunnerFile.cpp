#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <windows.h>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <ios>
#include <conio.h>
#include <future>
using namespace std;

struct mazeData
{

    // stores whole grid
    vector<string> maze;
    // vectors with separate paths to exit point
    vector<int> path_one{
        24,
        46,
        68,
        90,
        91,
        92,
        114,
        136,
        134,
        135,
        156,
        178,
        179,
        201,
        223,
        224,
        225,
        226,
        160,
        182,
        204,
        95,
        117,
        139,
        161,
        96,
        97,
        75,
        76,
        77,
        99,
        121,
        143,
        141,
        142,
        163,
        185,
        186,
        208,
        230,
        231,
        232,
        233,
        189,
        211,
        124,
        146,
        168,
        190,
        79,
        101,
        123,
        80,
        81,
        82,
        104,
        126,
        148,
        149,
        171,
        193,
        192,
        214,
        236,
        237,
        238,
        239,
        107,
        129,
        151,
        173,
        195,
        217,
        108,
    };
    vector<int> path_two{
        141,
        163,
        142,
        143,
        165,
        185,
        187,
        209,
        205,
        206,
        207,
        208,
        181,
        182,
        183,
        200,
        201,
        202,
        203,
        112,
        134,
        156,
        178,
        91,
        113,
        70,
        92,
        71,
        72,
        94,
        95,
        96,
        74,
        75,
        76,
        98,
        99,
        100,
        101,
        123,
        145,
        146,
        147,
        81,
        103,
        125,
        82,
        83,
        84,
        106,
        128,
        129,
        151,
        173,
        195,
        217,
        215,
        216,
        237,
        259,
    };
    vector<int> path_three{
        220,
        221,
        177,
        199,
        178,
        179,
        180,
        136,
        158,
        69,
        91,
        113,
        135,
        70,
        71,
        93,
        94,
        95,
        117,
        118,
        119,
        141,
        163,
        185,
        207,
        208,
        209,
        231,
        232,
        233,
        234,
        235,
        191,
        213,
        189,
        190,
        101,
        123,
        145,
        167,
        102,
        103,
        104,
        126,
        148,
        149,
        150,
        84,
        106,
        128,
        85,
        86,
    };

    // stores numbers of fiedls on which player can move
    vector<int> moveMap{
        45,
        46,
        47,
        48,
        49,
        50,
        51,
        52,
        53,
        54,
        55,
        56,
        57,
        58,
        59,
        60,
        61,
        62,
        63,
        64,
        67,
        68,
        69,
        70,
        71,
        72,
        73,
        74,
        75,
        76,
        77,
        78,
        79,
        80,
        81,
        82,
        83,
        84,
        85,
        86,
        89,
        90,
        91,
        92,
        93,
        94,
        95,
        96,
        97,
        98,
        99,
        100,
        101,
        102,
        103,
        104,
        105,
        106,
        107,
        108,
        111,
        112,
        113,
        114,
        115,
        116,
        117,
        118,
        119,
        120,
        121,
        122,
        123,
        124,
        125,
        126,
        127,
        128,
        129,
        130,
        133,
        134,
        135,
        136,
        137,
        138,
        139,
        140,
        141,
        142,
        143,
        144,
        145,
        146,
        147,
        148,
        149,
        150,
        151,
        152,
        155,
        156,
        157,
        158,
        159,
        160,
        161,
        162,
        163,
        164,
        165,
        166,
        167,
        168,
        169,
        170,
        171,
        172,
        173,
        174,
        177,
        178,
        179,
        180,
        181,
        182,
        183,
        184,
        185,
        186,
        187,
        188,
        189,
        190,
        191,
        192,
        193,
        194,
        195,
        196,
        199,
        200,
        201,
        202,
        203,
        204,
        205,
        206,
        207,
        208,
        209,
        210,
        211,
        212,
        213,
        214,
        215,
        216,
        217,
        218,
        221,
        222,
        223,
        224,
        225,
        226,
        227,
        228,
        229,
        230,
        231,
        232,
        233,
        234,
        235,
        236,
        237,
        238,
        239,
        240,
        243,
        244,
        245,
        246,
        247,
        248,
        249,
        250,
        251,
        252,
        253,
        254,
        255,
        256,
        257,
        258,
        259,
        260,
        261,
        262,
    };

    void printMaze(vector<string> maze)
    {
        cout << endl;
        for (int i = 0; i < maze.size(); i++)
        {
            if (i % 22 == 0)
            {
                cout << endl;
            }
            cout << maze[i];
        }
        cout << endl
             << endl;
    }
};

// *global variables
struct mazeData mazeFields;
struct mazeData numTab;
vector<int> nextEmptyCells;
int activePath = 0;
int activeDirection = 0;
int activeCell = 0;
int key;
int currentPosition = 0;
int lastPosition = 0;
bool canMove = false;

// generate random numbers vector in given size
vector<int> randCellNumberVector(int iterations)
{
    sleep(1);
    nextEmptyCells.clear();
    srand((unsigned)time(NULL));
    for (int i = 0; i < iterations; i++)
    {
        nextEmptyCells.push_back(44 + (rand() % 220));
    }

    // *vector content check
    // for(int i = 0; i < iterations; i++){
    //     cout << nextEmptyCells[i] << endl;
    // }
    // cout << endl;

    return nextEmptyCells;
}
// return single random number
int randomNumber(int range)
{
    srand((unsigned)time(NULL));
    int random = rand() % range;
    return random;
}

// generate fake corridors in manner approx. to of Kruskal algorithm
void gapsGen(int iterations)
{
    bool sideSwitch = true;

    for (int i = 0; i < iterations; i++)
    {
        nextEmptyCells = randCellNumberVector(15);

        for (int i = 0; i < nextEmptyCells.size(); i++)
        {
            // cout << " switch: " << sideSwitch;
            switch (sideSwitch)
            {
            case 1:
                if (nextEmptyCells[i] + 2 < mazeFields.maze.size() && mazeFields.maze.at(nextEmptyCells[i]) != "|")
                {
                    if (mazeFields.maze.at(nextEmptyCells[i] + 2) == " ")
                    {
                        mazeFields.maze.at(nextEmptyCells[i] + 1) = " ";
                    }
                }
                if (nextEmptyCells[i] - 20 > 0)
                {
                    if (mazeFields.maze.at(nextEmptyCells[i] - 44) == " ")
                    {
                        mazeFields.maze.at(nextEmptyCells[i] - 22) = " ";
                    }
                }
                break;

            case 0:
                if (nextEmptyCells[i] - 2 > 0 && mazeFields.maze.at(nextEmptyCells[i]) != "|")
                {
                    if (mazeFields.maze.at(nextEmptyCells[i] - 2) == " ")
                    {
                        mazeFields.maze.at(nextEmptyCells[i] - 1) = " ";
                    }
                }

                if (nextEmptyCells[i] + 20 < mazeFields.maze.size())
                {
                    if (mazeFields.maze.at(nextEmptyCells[i] + 44) == " ")
                    {
                        mazeFields.maze.at(nextEmptyCells[i] + 22) = " ";
                    }
                }
                break;
            }

            sideSwitch = !sideSwitch;
        }
    }
}
// initializes maze with initial empty fields used after by gapsGen()
void mazeInit()
{
    mazeFields.maze.clear();
    vector<int> initialEmptyCells = randCellNumberVector(15);

    // initialize matrix
    // iter >= 44 && iter < 264 range for # sign
    for (int i = 0; i < 310; i++)
    {
        if (i < 22)
            mazeFields.maze.push_back("-");
        if (i >= 22 && i < 44)
            mazeFields.maze.push_back(" ");
        if (i >= 44 && i < 264)
            mazeFields.maze.push_back("#");
        if (i >= 266 && i < 288)
            mazeFields.maze.push_back(" ");
        if (i >= 288)
            mazeFields.maze.push_back("-");
    }

    for (int i = 44; i < 244; i += 22)
        mazeFields.maze.at(i) = "|";

    for (int i = 65; i < 265; i += 22)
        mazeFields.maze.at(i) = "|";

    for (int i = 0; i < initialEmptyCells.size(); i++)
        if (mazeFields.maze.at(initialEmptyCells[i]) != "|")
            mazeFields.maze.at(initialEmptyCells[i]) = " ";
}
// draws path to exit point in maze build by mazeInit() and transformed by gapsGen()
void pathDrawer()
{
    activePath = randomNumber(3);

    if (activePath == 0)
    {
        for (int i = 0; i < mazeFields.path_one.size(); i++)
        {
            if (i == 0)
                mazeFields.maze.at(mazeFields.path_one[i]) = "$";
            else if (i == mazeFields.path_one.size() - 1)
                mazeFields.maze.at(mazeFields.path_one[i]) = "@";
            else
                mazeFields.maze.at(mazeFields.path_one[i]) = " ";
        }
    };

    if (activePath == 1)
    {
        for (int i = 0; i < mazeFields.path_two.size(); i++)
        {
            if (i == 0)
                mazeFields.maze.at(mazeFields.path_two[i]) = "$";
            else if (i == mazeFields.path_two.size() - 1)
                mazeFields.maze.at(mazeFields.path_two[i]) = "@";
            else
                mazeFields.maze.at(mazeFields.path_two[i]) = " ";
        }
    };

    if (activePath == 2)
    {
        for (int i = 0; i < mazeFields.path_three.size(); i++)
        {
            if (i == 0)
                mazeFields.maze.at(mazeFields.path_three[i]) = "$";
            else if (i == mazeFields.path_three.size() - 1)
                mazeFields.maze.at(mazeFields.path_three[i]) = "@";
            else
                mazeFields.maze.at(mazeFields.path_three[i]) = " ";
        }
    };
}
// places symbols of player in maze in dependency of path shuffled by pathDrawer()
void placePlayer()
{
    if (activePath == 0)
    {
        mazeFields.maze.at(mazeFields.path_one[1]) = "^";
        lastPosition = mazeFields.path_one[1];
        currentPosition = mazeFields.path_one[1];
    }

    if (activePath == 1)
    {
        mazeFields.maze.at(mazeFields.path_two[1]) = "^";
        lastPosition = mazeFields.path_two[1];
        currentPosition = mazeFields.path_two[1];
    }

    if (activePath == 2)
    {
        mazeFields.maze.at(mazeFields.path_three[1]) = "^";
        lastPosition = mazeFields.path_three[1];
        currentPosition = mazeFields.path_three[1];
    }
};

// getDirection() player movment conversion schema
// key: 'w' code: 119 - top iter+22
// key: 's' code: 115 - down iter-22
// key: 'a' code: 97 - left iter-1
// key: 'd' code: 100 - right iter+1

void getDirection()
{
    system("cls");
    mazeFields.printMaze(mazeFields.maze);
    key = getch();

    switch (key)
    {
    case 119:
        currentPosition = currentPosition - 22;
        break;
    case 115:
        currentPosition = currentPosition + 22;
        break;
    case 97:
        currentPosition = currentPosition - 1;
        break;
    case 100:
        currentPosition = currentPosition + 1;
        break;

    default:
        getDirection();
        break;
    }
};
// prints changes of player position
void makeMove()
{
    system("cls");
    mazeFields.maze.at(lastPosition) = " ";
    mazeFields.maze.at(currentPosition) = "^";
    mazeFields.printMaze(mazeFields.maze);
    lastPosition = currentPosition;
};
// checks if player move is possible, if not player has to provide direction again
void checkField()
{
    for (int check = 0; check < mazeFields.moveMap.size(); check++)
    {

        if (currentPosition == mazeFields.moveMap[check] && mazeFields.maze.at(currentPosition) == "@")
        {
            cout << "Congratulations you've reached to the exit point!" << endl
                 << endl;
            activeCell = currentPosition;
            break;
        }
        else if (currentPosition == mazeFields.moveMap[check] && mazeFields.maze.at(currentPosition) != "#" && mazeFields.maze.at(currentPosition) != "$" && mazeFields.maze.at(currentPosition) != "|")
        {
            canMove = true;
            break;
        }
        else
        {
            canMove = false;
        };
    };

    if (canMove == true)
    {
        makeMove();
    }
    else
    {
        switch (key)
        {
        case 119:
            currentPosition = currentPosition + 22;
            break;
        case 115:
            currentPosition = currentPosition - 22;
            break;
        case 97:
            currentPosition = currentPosition + 1;
            break;
        case 100:
            currentPosition = currentPosition - 1;
            break;
        }
    }
};
// control function of maze generation process
void mazeBuilder()
{
    future<void> f = async(launch::async, pathDrawer);
    mazeInit();
    gapsGen(2);
    f.wait();
    f.get();
    // pathDrawer();
    placePlayer();
}
// control function of whole game loop
void game()
{
    bool play = true;
    bool firstPlay = true;
    string input;

    while (play)
    {

        if (firstPlay == true)
        {
            cout << "  _____ _            __   __               " << endl;
            cout << " |_   _| |__   ___  |  \\ /  |  __ _ _______  " << endl;
            cout << "   | | | '_ \\ / _ \\ | |\\ /| | / _` |_  / _ \\ " << endl;
            cout << "   | | | | | |  __/ | |   | |  (_| |/ /  __/ " << endl;
            cout << "   |_| |_| |_|\\___| |_|   |_| \\__,_/___\\___| " << endl;
            cout << endl
                 << endl
                 << "Welcome to The Maze!" << endl
                 << endl;
            cout << "Your goal is to reach point marked as '@'\nStarting point is marked as '$'\nPlayer is marked as '^'" << endl
                 << endl;
            cout << "Movement:\n'w' - top\n's' - bottom\n'a' - left\n'd' - right" << endl;
            cout << "Would you like to play?\n(y/n) and press Enter" << endl;
        }
        else
        {
            cout << "Would you like to play again?\n(y/n) and press Enter" << endl;
        }

        cin >> input;
        if (input == "y" || input == "Y")
        {
            // sleep(2);
            mazeBuilder();
            mazeFields.maze.at(activeCell) = " ";
            while (mazeFields.maze.at(activeCell) != "@")
            {
                getDirection();
                checkField();
                firstPlay = false;
            }
        }
        else
        {
            play = false;
            cout << endl
                 << "Bye!";
        }
    }
}

int main()
{
    game();
    return 0;
}
