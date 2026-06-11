#include <iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
using namespace std;

struct Profile
{
    char name[30];
    int score;
};

void guide()
{
    cout << "Welcome to 2048" << endl;
    cout << "For a better experience you should know how to play" << endl;
    cout << "For the first time you must enter your name and choose the size of the board then enter your move" << endl;
    cout << "Enter (a) for move left" << endl;
    cout << "Enter (s) for move down" << endl;
    cout << "Enter (d) for move right" << endl;
    cout << "Enter (w) for move up" << endl;
    cout << "Enter (m) for go back to the menu" << endl;
    cout << "Enter (u) for return to previous move" << endl;
    cout << "Enter (q) for finish the game" << endl;
    cout << "Enjoy the game" << endl;
}

void printBoard(int** board, int size)
{
    system("cls");

    string color;
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == 0)color = "\033[0;37;47m";
            else if (board[i][j] == 2)color = "\033[1;94;47m";
            else if (board[i][j] == 4)color = "\033[1;32;47m";
            else if (board[i][j] == 8)color = "\033[1;31;47m";
            else if (board[i][j] == 16)color = "\033[1;35;47m";
            else if (board[i][j] == 32)color = "\033[1;33;47m";
            else if (board[i][j] == 64)color = "\033[1;31;47m";
            else if (board[i][j] == 128)color = "\033[1;36;47m";
            else if (board[i][j] == 256)color = "\033[1;92;47m";
            else if (board[i][j] == 512)color = "\033[1;31;47m";
            else if (board[i][j] == 1024)color = "\033[1;91;47m";
            else if (board[i][j] == 2048)color = "\033[1;36;47m";
            else color = "\033[1;96;47m";

            cout << "|" << color << setw(5) << board[i][j] << "     " << "\033[0m";

        }
        cout << "|";
        cout << endl;
    }
}

void addUser(Profile Player[10], int& counter)
{
    cout << "Please enter your name" << endl;
    cin >> Player[counter].name;
    Player[counter].score = 0;
    counter++;
}
void sortProfile(Profile Player[10], int& counter)
{
    int i, j;
    Profile Temp;
    for (j = 0; j < counter - 1; j++)
    {
        for (i = 0; i < counter - j - 1; i++)
        {
            if (Player[i].score < Player[i + 1].score)
            {
                Temp = Player[i];
                Player[i] = Player[i + 1];
                Player[i + 1] = Temp;
            }
        }
    }
}
void selectUser(Profile Player[10], int& counter, int& count)
{
    int i;
    for (i = 0; i < counter; i++)
    {
        cout << i + 1 << "." << Player[i].name << "  score:" << Player[i].score << endl;
    }
    cin >> count;
    count = count - 1;
}

void showScore(Profile Player[10], int counter)
{
    int i;
    sortProfile(Player, counter);
    for (i = 0; i < counter; i++)
    {
        cout << "Name:" << Player[i].name << "  Score:" << Player[i].score << endl;
    }
}

void menu(Profile Player[], int& counter, int& count)
{
    int Number;
    while (true)
    {
        cout << "----Main Menu----" << endl;
        cout << "1.Add User" << endl;
        cout << "2.Select User" << endl;
        cout << "3.Show Score" << endl;
        cout << "4.How to play" << endl;
        cout << "5.Exit" << endl;
        cin >> Number;
        if (Number == 1)addUser(Player, counter);
        if (Number == 2)
        {
            if (counter == 0)
            {
                cout << "There is no user please add a user" << endl;
                continue;
            }
            selectUser(Player, counter, count);
        }
        if (Number == 3)showScore(Player, counter);
        if (Number == 4)guide();
        if (Number == 5)break;
    }
}

void randomNumber(int** board, int size)
{
    int i, j;
    bool empty = false;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == 0)empty = true;
        }
    }
    while (empty)
    {
        i = rand() % size;
        j = rand() % size;
        if (board[i][j] == 0)
        {
            if (rand() % 2 == 0)board[i][j] = 2;
            else board[i][j] = 4;
            break;
        }
    }
}

void compressLeft(int** board, int size)
{
    int i, j, k, temp[8][8] = { 0 };

    for (i = 0; i < size; i++)
    {
        k = 0;
        for (j = 0; j < size; j++)
        {
            if (board[i][j] != 0)
            {
                temp[i][k] = board[i][j];
                k++;
            }
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = temp[i][j];
        }
    }
}
void mergLeft(int** board, int size, int& score)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1])
            {
                board[i][j] += board[i][j + 1];
                score += board[i][j];
                board[i][j + 1] = 0;
            }
        }
    }
}
void moveLeft(int** board, int size, int& score)
{
    compressLeft(board, size);
    mergLeft(board, size, score);
    compressLeft(board, size);
}
void compressRight(int** board, int size)
{
    int i, j, k, temp[8][8] = { 0 };

    for (i = 0; i < size; i++)
    {
        k = size - 1;
        for (j = size - 1; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                temp[i][k] = board[i][j];
                k--;
            }

        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = temp[i][j];
        }
    }
}
void mergRight(int** board, int size, int& score)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = size - 2; j >= 0; j--)
        {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1])
            {
                board[i][j + 1] += board[i][j];
                score += board[i][j + 1];
                board[i][j] = 0;
            }
        }
    }
}
void moveRight(int** board, int size, int& score)
{
    compressRight(board, size);
    mergRight(board, size, score);
    compressRight(board, size);
}
void compressUp(int** board, int size)
{
    int i, j, k, temp[8][8] = { 0 };

    for (j = 0; j < size; j++)
    {
        k = 0;
        for (i = 0; i < size; i++)
        {
            if (board[i][j] != 0)
            {
                temp[k][j] = board[i][j];
                k++;
            }
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = temp[i][j];
        }
    }

}
void mergUp(int** board, int size, int& score)
{
    int i, j;
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < size - 1; i++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j])
            {
                board[i][j] += board[i + 1][j];
                score += board[i][j];
                board[i + 1][j] = 0;

            }
        }
    }
}
void moveUp(int** board, int size, int& score)
{
    compressUp(board, size);
    mergUp(board, size, score);
    compressUp(board, size);


}
void compressDown(int** board, int size)
{
    int i, j, k, temp[8][8] = { 0 };


    for (j = 0; j < size; j++)
    {
        k = size - 1;
        for (i = size - 1; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                temp[k][j] = board[i][j];
                k--;
            }
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = temp[i][j];
        }
    }
}
void mergDown(int** board, int size, int& score)
{
    int i, j;
    for (j = 0; j < size; j++)
    {
        for (i = size - 2; i >= 0; i--)
        {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j])
            {
                board[i + 1][j] += board[i][j];
                score += board[i + 1][j];
                board[i][j] = 0;
            }
        }
    }

}
void moveDown(int** board, int size, int& score)
{
    compressDown(board, size);
    mergDown(board, size, score);
    compressDown(board, size);
}
bool win(int** board, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == 2048)return true;
        }
    }
    return false;
}
bool lose(int** board, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == 0)return false;
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                return false;
            }
        }
    }
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < size - 1; i++)
        {
            if (board[i][j] == board[i + 1][j])
            {
                return false;
            }
        }
    }
    return true;


}
void copyBoard(int** board, int size, Profile Player[10], int& count, int previousBoard[8][8], int& previousScore)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            previousBoard[i][j] = board[i][j];
        }
    }
    previousScore = Player[count].score;
}
void undo(int previousBoard[8][8], int& previousScore, int** board, int size, Profile Player[10], int& count)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = previousBoard[i][j];

        }
    }
    Player[count].score = previousScore;
}
int main()
{
    srand(time(0));
    Profile Player[10];
    int i, j, counter = 0, num_board, size, ** board, previousBoard[8][8], previousScore, count = 0;
    bool different = false, finish = false, canUndo = false, quit = false;
    char answer[10], move;

    menu(Player, counter, count);

    cout << "Please choose your board" << endl;
    cout << "1.Board 2*2" << endl;
    cout << "2.Board 4*4" << endl;
    cout << "3.Board 6*6" << endl;
    cout << "4.Board 8*8" << endl;

    cin >> num_board;
    if (num_board == 1)size = 2;
    else if (num_board == 2)size = 4;
    else if (num_board == 3)size = 6;
    else if (num_board == 4)size = 8;

    board = new int* [size];
    for (i = 0; i < size; i++)
    {
        board[i] = new int[size];
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = 0;
        }
    }

    randomNumber(board, size);
    randomNumber(board, size);

    while (true)
    {
        printBoard(board, size);
        cin >> move;

        if (move == 'a' || move == 'd' || move == 'w' || move == 's')
        {
            copyBoard(board, size, Player, count, previousBoard, previousScore);
        }

        if (move == 'a') moveLeft(board, size, Player[count].score);
        if (move == 'd') moveRight(board, size, Player[count].score);
        if (move == 'w') moveUp(board, size, Player[count].score);
        if (move == 's') moveDown(board, size, Player[count].score);
        if (move == 'm')menu(Player, counter, count);
        if (move == 'q')
        {
            quit = true;
            break;
        }
        if (move == 'u')
        {
            if (canUndo) undo(previousBoard, previousScore, board, size, Player, count);
            canUndo = false;
        }

        if (move == 'a' || move == 'd' || move == 'w' || move == 's')
        {
            different = false;
            canUndo = true;
            for (i = 0; i < size; i++)
            {
                for (j = 0; j < size; j++)
                {
                    if (previousBoard[i][j] != board[i][j])different = true;
                }
            }
            if (different)randomNumber(board, size);
        }
        if (win(board, size))
        {
            if (!finish)
            {
                cout << "Congratulation you won" << endl;
                finish = true;
                cout << "Do you want to continue?(say yes or no)" << endl;
                cin >> answer;
                if (strcmp(answer, "no") == 0)break;
            }
        }

        if (lose(board, size))
        {
            cout << "Game over";
            break;
        }
    }
    for (i = 0; i < size; i++)
    {
        delete[]board[i];
    }
    delete[]board;
    if (quit)main();

}