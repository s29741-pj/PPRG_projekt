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
using namespace std;

// Program wypisuje na ekran labirynt o rozmiarze 10x20, który składa się z następujących elementów:
// • # - ściana, nie można na nią wejść,
// • ‘ ‘ – spacja - korytarz, można po nim chodzić,
// • $ - punkt startowy,
// • @ - punkt docelowy.
// (Wygląd labiryntu jest dowolny, ważne, żeby znalazły się w nim powyższe elementy).
// Program ma pozwolić użytkownikowi na poruszanie się graczem (oznaczonym w dowolny sposób) przy pomocy klawiszy:

// • w - krok w górę.
// • s - krok w dół,
// • a - krok w lewo,
// • d - krok w prawo,

// algorytm Kruskala

// !30.12 stop, checkField to be checked why stops execution
// generate maze
// draw maze
// print maze
// * move
// get direction
// check if move is possible
// make move/refresh console/print with changes
// get direction
// end when ^ reaches @
// * end, congrats

struct mazeData
{
    vector<string> maze;

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
        for (int iter = 0; iter < maze.size(); iter++)
        {
            if (iter % 22 == 0)
            {
                cout << endl;
                // cout << maze[iter];
            }
            cout << maze[iter];
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
int currentPosition = 0;
int lastPosition = 0;

// !iter >= 44 && iter < 264 range for # sign
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

int randomNumber(int range)
{
    srand((unsigned)time(NULL));
    int random = rand() % range;
    return random;
}

void gapsGen(int iterations)
{
    bool sideSwitch = true;

    for (int iter = 0; iter < iterations; iter++)
    {
        nextEmptyCells = randCellNumberVector(30);

        for (int iter = 0; iter < nextEmptyCells.size(); iter++)
        {
            // cout << " switch: " << sideSwitch;
            switch (sideSwitch)
            {
            case 1:
                if (nextEmptyCells[iter] + 2 < mazeFields.maze.size())
                {
                    if (mazeFields.maze.at(nextEmptyCells[iter] + 2) == " ")
                    {
                        // cout << maze.at(nextEmptyCells[iter]+2) << " + ";
                        mazeFields.maze.at(nextEmptyCells[iter] + 1) = " ";
                    }
                }
                if (nextEmptyCells[iter] - 20 > 0)
                {
                    if (mazeFields.maze.at(nextEmptyCells[iter] - 44) == " ")
                    {
                        // cout << maze.at(nextEmptyCells[iter]+2) << " + ";
                        mazeFields.maze.at(nextEmptyCells[iter] - 22) = " ";
                    }
                }
                break;

            case 0:
                if (nextEmptyCells[iter] - 2 > 0)
                {
                    if (mazeFields.maze.at(nextEmptyCells[iter] - 2) == " ")
                    {
                        mazeFields.maze.at(nextEmptyCells[iter] - 1) = " ";
                    }
                }

                if (nextEmptyCells[iter] + 20 < mazeFields.maze.size())
                {
                    if (mazeFields.maze.at(nextEmptyCells[iter] + 44) == " ")
                    {
                        // cout << maze.at(nextEmptyCells[iter]+2) << " + ";
                        mazeFields.maze.at(nextEmptyCells[iter] + 22) = " ";
                    }
                }
                break;
            }

            sideSwitch = !sideSwitch;
        }
    }

    // mazeFields.printMaze(mazeFields.maze);
}

void mazeInit()
{
    vector<int> initialEmptyCells = randCellNumberVector(10);

    // !iter >= 44 && iter < 264 range for # sign

    //* initialize matrix
    for (int iter = 0; iter < 310; iter++)
    {
        if (iter < 22)
            mazeFields.maze.push_back("-");
        if (iter >= 22 && iter < 44)
            mazeFields.maze.push_back(" ");
        if (iter >= 44 && iter < 264)
            mazeFields.maze.push_back("#");
        if (iter >= 266 && iter < 288)
            mazeFields.maze.push_back(" ");
        if (iter >= 288)
            mazeFields.maze.push_back("-");
    }

    // mazeFields.printMaze(mazeFields.maze);

    for (int iter = 44; iter < 244; iter += 22)
        mazeFields.maze.at(iter) = "|";

    for (int iter = 65; iter < 265; iter += 22)
        mazeFields.maze.at(iter) = "|";

    // mazeFields.printMaze(mazeFields.maze);

    for (int iter = 0; iter < initialEmptyCells.size(); iter++)
        mazeFields.maze.at(initialEmptyCells[iter]) = " ";

    // mazeFields.printMaze(mazeFields.maze);
}

void pathDrawer()
{
    activePath = randomNumber(3);

    if (activePath == 0)
    {
        for (int iter = 0; iter < mazeFields.path_one.size(); iter++)
        {
            if (iter == 0)
                mazeFields.maze.at(mazeFields.path_one[iter]) = "$";
            else if (iter == mazeFields.path_one.size() - 1)
                mazeFields.maze.at(mazeFields.path_one[iter]) = "@";
            else
                mazeFields.maze.at(mazeFields.path_one[iter]) = " ";
        }
        // mazeFields.printMaze(mazeFields.maze);
    };

    if (activePath == 1)
    {
        for (int iter = 0; iter < mazeFields.path_two.size(); iter++)
        {
            if (iter == 0)
                mazeFields.maze.at(mazeFields.path_two[iter]) = "$";
            else if (iter == mazeFields.path_two.size() - 1)
                mazeFields.maze.at(mazeFields.path_two[iter]) = "@";
            else
                mazeFields.maze.at(mazeFields.path_two[iter]) = " ";
        }
        // mazeFields.printMaze(mazeFields.maze);
    };

    if (activePath == 2)
    {
        for (int iter = 0; iter < mazeFields.path_three.size(); iter++)
        {
            if (iter == 0)
                mazeFields.maze.at(mazeFields.path_three[iter]) = "$";
            else if (iter == mazeFields.path_three.size() - 1)
                mazeFields.maze.at(mazeFields.path_three[iter]) = "@";
            else
                mazeFields.maze.at(mazeFields.path_three[iter]) = " ";
        }
        // mazeFields.printMaze(mazeFields.maze);
    };
}

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

    mazeFields.printMaze(mazeFields.maze);
};

// void insideField() {
//     for (int check = 0; check < mazeFields.moveMap.size(); check++){
//         cout << mazeFields.maze.at(mazeFields.moveMap[check]);
//     }
// };

// key: 'w' kod: 119
// key: 's' kod: 115
// key: 'a' kod: 97
// key: 'd' kod: 100

// top iter+22
// down iter-22
// left iter-1
// right iter+1

void getDirection()
{
    int key;
    cout << "Where to? ";
    key = getch();

    cout << key;
    switch (key)
    {
    case 119:
        currentPosition = currentPosition + 22;
        break;
    case 115:
        currentPosition = currentPosition - 22;
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

void makeMove(int currentPosition)
{
    cout << "Launch move";
    system("cls");
    mazeFields.maze.at(lastPosition) = " ";
    mazeFields.maze.at(currentPosition) = "^";
    mazeFields.printMaze(mazeFields.maze);
    lastPosition = currentPosition;
};



void checkField(int fieldNum)
{
    cout << "Launch";
    bool canMove = false;

    for (int check = 0; check < mazeFields.moveMap.size(); check++)
    {

        if (fieldNum == mazeFields.moveMap[check] && mazeFields.maze.at(fieldNum) != "#" && mazeFields.maze.at(fieldNum) != "$")
        {
            // cout << mazeFields.maze.at(fieldNum) << " ";
            activeCell = fieldNum;
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
        makeMove(currentPosition);
    }
    else
    {
        getDirection();
    }

};

void playerMove()
{
    do
    {
        getDirection();
        checkField(currentPosition);

    } while (mazeFields.maze.at(activeCell) == "@");
}

void mazeBuilder()
{
    mazeInit();
    gapsGen(1);
    pathDrawer();
    placePlayer();
}

int main()
{
    mazeBuilder();
    playerMove();

    return 0;
}
