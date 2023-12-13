#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <tuple>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;

const int boardSize = 8;

const string whitePawn = "\u2659";
const string blackPawn = "\u265F";
const string whiteKnight = "\u2658";
const string blackKnight = "\u265E";
const string whiteBishop = "\u2657";
const string blackBishop = "\u265D";
const string whiteRook = "\u2656";
const string blackRook = "\u265C";
const string whiteQueen = "\u2655";
const string blackQueen = "\u265B";
const string whiteKing = "\u2654";
const string blackKing = "\u265A";

const int pawnValue = 1;
const int knightValue = 3;
const int bishopValue = 3;
const int rookValue = 5;
const int queenValue = 9;

enum squareValue
{
    black,
    emptys,
    white,
    king
};

/*vector<vector<squareValue>> board =
    {
        {black, black, black, black, king, black, black, black},
        {black, black, black, black, black, black, black, black},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {white, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys}
    };

vector<vector<string>> defaultBoard =
    {
        {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {whitePawn, " ", " ", " ", " ", " ", " ", " "," "},
        {" ", " ", " ", " "," ", " ", " ", " "}
    };

*/
vector<vector<squareValue>> board =
    {
        {black, black, black, black, king, black, black, black},
        {black, black, black, black, black, black, black, black},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {white, white, white, white, white, white, white, white},
        {white, white, white, white, king, white, white, white}
    };

vector<vector<string>> defaultBoard =
    {
        {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook}
    };

void reposition(int i, int j, int k, int l, squareValue sV, string piece)
{
    board[i][j] = emptys;
    board[k][l] = sV;
    defaultBoard[i][j] = " ";
    defaultBoard[k][l] = piece;
}

bool pawnMove(int i, int j, int k, int l, squareValue sV)
{
    const int whiteStartingRow = 6;
    const int blackStartingRow = 1;
    const int moveDirectionWhite = -1;
    const int moveDirectionBlack = 1;
    const int doubleMoveRowThreshold = 1;

    int moveDirection;
    int startingRow;

    if (sV == white)
    {
        moveDirection = moveDirectionWhite;
        startingRow = whiteStartingRow;
    }
    else
    {
        moveDirection = moveDirectionBlack;
        startingRow = blackStartingRow;
    }

    if (defaultBoard[i][j] != (sV == white ? whitePawn : blackPawn))
    {
        // Invalid move
        return false;
    }

    if (board[k][l] == emptys)
    {
        if (k == i + moveDirection && l == j)
        {
            return true;
        }

        if (i == startingRow && k == i + 2 * moveDirection && l == j && board[i + moveDirection][j] == emptys)
        {
            return true;
        }
    }

    if (k == i + moveDirection && (l == j + 1 || l == j - 1) && board[k][l] == (sV == white ? black : white))
    {
        return true;
    }

    // Invalid move
    return false;
}

bool rookMove(int i, int j, int k, int l, squareValue sV)
{
    if (sV != black && sV != white)
    {
        // Invalid piece
        return false;
    }

    if (i == k)
    {
        int step = (l > j) ? 1 : -1;
        for (int x = j + step; x != l; x += step)
        {
            if (board[i][x] != emptys)
            {
                // Invalid move
                return false;
            }
        }
    }
    else if (j == l)
    {
        int step = (k > i) ? 1 : -1;
        for (int x = i + step; x != k; x += step)
        {
            if (board[x][j] != emptys)
            {
                // Invalid move
                return false;
            }
        }
    }
    else
    {
        // Invalid move
        return false;
    }

    if (board[k][l] != emptys && board[k][l] != sV)
    {
        return true;
    }
    else if (board[k][l] == emptys)
    {
        return true;
    }

    // Invalid move
    return false;
}

bool knightMove(int i, int j, int k, int l, squareValue sV)
{
    if (sV != black && sV != white)
    {
        // Invalid piece
        return false;
    }

    int delta_i = abs(k - i);
    int delta_j = abs(l - j);

    if ((delta_i == 2 and delta_j == 1) or (delta_i == 1 and delta_j == 2))
    {
        if (board[k][l] != emptys && board[k][l] != sV)
        {
            // Invalid move
            return false;
        }
        else if (board[k][l] == emptys)
        {
            // Valid move
            return true;
        }
        else
        {
            // Invalid move
            return false;
        }
    }
    // Invalid move
    return false;
}

bool bishopMove(int i, int j, int k, int l, squareValue sV)
{
    if (sV != black && sV != white)
    {
        // Invalid piece
        return false;
    }

    int delta_i = abs(k - i);
    int delta_j = abs(l - j);

    if (delta_i == delta_j)
    {
        int step_i = (k > i) ? 1 : -1;
        int step_j = (l > j) ? 1 : -1;

        for (int x = i + step_i, y = j + step_j; x != k && y != l; x += step_i, y += step_j)
        {
            if (board[x][y] != emptys)
            {
                // Invalid move
                return false;
            }
        }

        if (board[k][l] != emptys && board[k][l] != sV)
        {
            // Invalid move
            return false;
        }
        else if (board[k][l] == emptys)
        {
            // Valid move
            return true;
        }
        else
        {
            // Invalid move
            return false;
        }
    }
    // Invalid move
    return false;
}

bool queenMove(int i, int j, int k, int l, squareValue sV)
{
    if (sV != black && sV != white)
    {
        // Invalid piece
        return false;
    }

    int delta_i = abs(k - i);
    int delta_j = abs(l - j);

    if ((delta_i == delta_j) || (delta_i == 0 && delta_j != 0) || (delta_i != 0 && delta_j == 0))
    {
        int step_i = (k > i) ? 1 : ((k < i) ? -1 : 0);
        int step_j = (l > j) ? 1 : ((l < j) ? -1 : 0);

        for (int x = i + step_i, y = j + step_j; x != k || y != l; x += step_i, y += step_j)
        {
            if (board[x][y] != emptys)
            {
                // Invalid move
                return false;
            }
        }

        if (board[k][l] != emptys && board[k][l] != sV)
        {
            // Invalid move
            return false;
        }
        else if (board[k][l] == emptys)
        {
            // Valid move
            return true;
        }
        else
        {
            // Invalid move
            return false;
        }
    }
    // Invalid move
    return false;
}

bool kingMove(int i, int j, int k, int l, squareValue sV, string piece)
{
    if (sV != king)
    {
        // Invalid piece
        return false;
    }

    int delta_i = abs(k - i);
    int delta_j = abs(l - j);

    if (delta_i <= 1 && delta_j <= 1)
    {
        if (board[k][l] != emptys && board[k][l] != sV)
        {
            // Invalid move
            return false;
        }
        else if (board[k][l] == emptys)
        {
            // Valid move
            return true;
        }
        else
        {
            // Invalid move
            return false;
        }
    }
    // Invalid move
    return false;
}

bool isCheckForPawn(int i, int j, squareValue sV)
{
    int mD = (sV == white) ? -1 : 1;
    int leftDiagonalRow = i + mD;
    int leftDiagonalCol = j - 1;
    int rightDiagonalRow = i + mD;
    int rightDiagonalCol = j + 1;

    if (leftDiagonalRow >= 0 and leftDiagonalRow < boardSize and leftDiagonalCol >= 0 and leftDiagonalCol < boardSize)
    {
        string king = (sV == white) ? blackKing : whiteKing;
        if (defaultBoard[leftDiagonalRow][leftDiagonalCol] == king)
        {
            return true;
        }
    }
    if (rightDiagonalRow >= 0 and rightDiagonalRow < boardSize and rightDiagonalCol >= 0 and rightDiagonalCol < boardSize)
    {
        string king = (sV == white) ? blackKing : whiteKing;
        if (defaultBoard[rightDiagonalRow][rightDiagonalCol] == king)
        {
            return true;
        }
    }
    return false;
}

bool isCheckForRook(int i, int j, squareValue sV)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int d = 0; d < 4; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];
        while (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if (defaultBoard[row][col] != " ")
            {
                if ((sV == white and defaultBoard[row][col] == blackKing) or (sV == black and defaultBoard[row][col] == whiteKing))
                {
                    return true;
                }
                break;
            }
            row += directions[d][0];
            col += directions[d][1];
        }
    }
    return false;
}

bool isCheckForBishop(int i, int j, squareValue sV)
{
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int d = 0; d < 4; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];
        while (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if (defaultBoard[row][col] != " ")
            {
                if ((sV == white and defaultBoard[row][col] == blackKing) or (sV == black and defaultBoard[row][col] == whiteKing))
                {
                    return true;
                }
                break;
            }
            row += directions[d][0];
            col += directions[d][1];
        }
    }
    return false;
}

bool isCheckForKnight(int i, int j, squareValue sV)
{
    int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    for (int m = 0; m < 8; ++m)
    {
        int row = i + moves[m][0];
        int col = j + moves[m][1];
        if (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if ((sV == white and defaultBoard[row][col] == blackKing) or (sV == black and defaultBoard[row][col] == whiteKing))
            {
                return true;
            }
        }
    }
    return false;
}

bool isCheckForQueen(int i, int j, squareValue sV)
{
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    for (int d = 0; d < 8; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];
        while (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if (defaultBoard[row][col] != " ")
            {
                string king = (sV == white) ? blackKing : whiteKing;
                if (defaultBoard[row][col] == king)
                {
                    return true;
                }
                else
                {
                    break;
                }
            }
            row += directions[d][0];
            col += directions[d][1];
        }
    }
    return false;
}

bool isCheckForKings(int i, int j, squareValue sV)
{
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    for (int d = 0; d < 8; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];
        if (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            string king = (sV == white) ? blackKing : whiteKing;
            if (defaultBoard[row][col] == king)
            {
                return true;
            }
        }
    }
    return false;
}
bool isCheck(int i, int j, squareValue sV)
{
    if (sV == white)
    {
        if (defaultBoard[i][j] == whitePawn)
        {
            return isCheckForPawn(i, j, white);
        }
        if (defaultBoard[i][j] == whiteRook)
        {
            return isCheckForRook(i, j, white);
        }
        if (defaultBoard[i][j] == whiteKnight)
        {
            return isCheckForKnight(i, j, white);
        }
        if (defaultBoard[i][j] == whiteBishop)
        {
            return isCheckForBishop(i, j, white);
        }
        if (defaultBoard[i][j] == whiteQueen)
        {
            return isCheckForQueen(i, j, white);
        }
        if (defaultBoard[i][j] == whiteKing)
        {
            return isCheckForKings(i, j, king);
        }
    }
    if (sV == black)
    {
        if (defaultBoard[i][j] == blackPawn)
        {
            return isCheckForPawn(i, j, black);
        }
        if (defaultBoard[i][j] == blackRook)
        {
            return isCheckForRook(i, j, black);
        }
        if (defaultBoard[i][j] == blackKnight)
        {
            return isCheckForKnight(i, j, black);
        }
        if (defaultBoard[i][j] == blackBishop)
        {
            return isCheckForBishop(i, j, black);
        }
        if (defaultBoard[i][j] == blackQueen)
        {
            return isCheckForQueen(i, j, black);
        }
        if (defaultBoard[i][j] == blackKing)
        {
            return isCheckForKings(i, j, black);
        }
    }
    return false;
}

bool checkPiece(int i, int j, int k, int l, squareValue sV)
{
    if (sV == white)
    {
        if (defaultBoard[i][j] == whitePawn)
        {
            return pawnMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == whiteRook)
        {
            return rookMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == whiteKnight)
        {
            return knightMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == whiteBishop)
        {
            return bishopMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == whiteQueen)
        {
            return queenMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == whiteKing)
        {
            return kingMove(i, j, k, l, sV, whiteKing);
        }
        return false;
    }
    else if (sV == black)
    {
        if (defaultBoard[i][j] == blackPawn)
        {
            return pawnMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == blackRook)
        {
            return rookMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == blackKnight)
        {
            return knightMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == blackBishop)
        {
            return bishopMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == blackQueen)
        {
            return queenMove(i, j, k, l, sV);
        }
        else if (defaultBoard[i][j] == blackKing)
        {
            return kingMove(i, j, k, l, sV, blackKing);
        }
        return false;
    }
    return false;
}

void showMove(int i, int j, squareValue sV)
{
    vector<vector<string>> defaultBoardTemporary = defaultBoard;
    vector<vector<squareValue>> boardTemporary = board;
    if (sV == white)
    {
        for (int k = 0; k < boardSize; ++k)
        {
            for (int l = 0; l < boardSize; ++l)
            {
                if (i == k and j == l)
                {
                    cout << " | "; // shows source
                }
                else if (checkPiece(i, j, k, l, sV))
                {
                    cout << k << l << " ";
                }
                else
                {
                    cout << " X ";
                }
                board = boardTemporary;
                defaultBoard = defaultBoardTemporary;
            }
            cout << endl;
        }
    }
    else if (sV == black)
    {
        for (int k = boardSize - 1; k >= 0; --k)
        {
            for (int l = boardSize - 1; l >= 0; --l)
            {
                if (i == k and j == l)
                {
                    cout << " | ";
                }
                else if (checkPiece(i, j, k, l, sV))
                {
                    cout << k << l << " ";
                }
                else
                {
                    cout << " X ";
                }
                board = boardTemporary;
                defaultBoard = defaultBoardTemporary;
            }
            cout << endl;
        }
    }
    cout << endl;
    board = boardTemporary;
    defaultBoard = defaultBoardTemporary;
}

int heuristicFunction(squareValue sV)
{
    int i, j;
    int state = 0;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (sV == white)
            {
                if (defaultBoard[i][j] == whitePawn)
                {
                    state += pawnValue;
                }
                else if (defaultBoard[i][j] == whiteBishop)
                {
                    state += bishopValue;
                }
                else if (defaultBoard[i][j] == whiteKnight)
                {
                    state += knightValue;
                }
                else if (defaultBoard[i][j] == whiteQueen)
                {
                    state += queenValue;
                }
            }
            else if (sV == black)
            {
                if (defaultBoard[i][j] == blackPawn)
                {
                    state += pawnValue;
                }
                else if (defaultBoard[i][j] == blackBishop)
                {
                    state += bishopValue;
                }
                else if (defaultBoard[i][j] == blackKnight)
                {
                    state += knightValue;
                }
                else if (defaultBoard[i][j] == blackQueen)
                {
                    state += queenValue;
                }
            }
        }
    }
    return state;
}

vector<tuple<int, int, int>> minimax(squareValue sV)
{
    vector<vector<string>> defaultBoardTemporary = defaultBoard;
    vector<vector<squareValue>> boardTemporary = board;
    vector<tuple<int, int, int>> allMoves;
    int maxHeuristic = INT_MIN;
    int i, j, k, l;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == sV)
            {
                for (k = 0; k < boardSize; ++k)
                {
                    for (l = 0; l < boardSize; ++l)
                    {
                        if(board[k][l]==sV)
                        {
                            continue;
                        }
                        try
                        {
                            // cout<<"b4check\n";
                            if (checkPiece(i, j, k, l, sV))
                            {
                                reposition(i,j,k,l,sV,defaultBoard[i][j]);
                                int heuristic = heuristicFunction(sV);
                                // cout<<"b4push\n";
                                allMoves.push_back(make_tuple(i * 10 + j, k * 10 + l, heuristic));
                            }
                            // cout<<"b4swap\n";
                            defaultBoard = defaultBoardTemporary;
                            board = boardTemporary;
                        }
                        catch (exception e)
                        {
                            cout << "An exception occurred: " << e.what() << endl;
                        }
                    }
                }
            }
        }
    }
    // cout<<"b4swap2\n";
    defaultBoard = defaultBoardTemporary;
    board = boardTemporary;
    // cout<<"b4lamda\n";
    return allMoves;
}


tuple<int,int,int> bestMove(vector<tuple<int,int,int>>  allMoves)
{
    try
    {
        auto minElement = *min_element(allMoves.begin(), allMoves.end(),
                                       [](auto a, auto b)
                                       {
                                           return get<2>(a) < get<2>(b);
                                       });

        // cout<<"b4return\n";
        return minElement;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        // Return a default value or handle the exception as needed
        return std::make_tuple(0, 0, 0); // Replace with an appropriate default tuple
    }
}
tuple<int,int,int> gameMove(squareValue sV)
{
    vector<tuple<int, int, int>>allMoves=minimax(sV);
    return bestMove(allMoves);
}

int fast_mod(int number, int divider)
{
    if (number == divider)
    {
        return 0;
    }
    else if (number < divider)
    {
        return number;
    }
    else if (!(divider & (divider - 1)))
    {
        return number & (divider - 1);
    }
    return number % divider;
}

void blackPrint(string str)
{
    cout << "\033[0;100m  " << str << "   \033[0m";
}

void whitePrint(string str)
{
    cout << "\033[1;97m  " << str << "   \033[0m";
}
/*void whitePrint(string str)   //0 cross
{
    cout<<"\033[0m  "<<str<<"  ";
}*/
/*void blackPrint(string str)   //0 cross
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout<<"  "<<str<<"  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}*/
/*void blackPrint(string str)  //2
{
    cout<<"\033[0;100m"<<str<<" \033[0m";
}

void printWithColor(string str, int textColor, int bgColor)     //1
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (bgColor << 4));
    cout << "  " << str << "  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
}

void whitePrint(string str)     //1
{
    printWithColor(str, 15, 0);
}

/*void blackPrint(string str)     //1
{
    printWithColor(str, 0, 15);
}*/

void chessboard()
{
    int i, j;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if ((i + j) & 1)
                whitePrint(defaultBoard[i][j]);
            else
                blackPrint(defaultBoard[i][j]);
        }
        cout << endl;
    }
}
void reverseChessboard()
{
    int i, j;
    for (i = boardSize - 1; i >= 0; --i)
    {
        for (j = boardSize - 1; j >= 0; --j)
        {
            if ((i + j) & 1)
                blackPrint(defaultBoard[i][j]);
            else
                whitePrint(defaultBoard[i][j]);
        }
        cout << endl;
    }
}
void cellAssist()
{
    int i, j;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == white)
            {
                cout << i << j << "   ";
            }
            else
            {
                cout << "XX   ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void reverseCellAssist()
{
    int i, j;
    for (i = boardSize - 1; i >= 0; --i)
    {
        for (j = boardSize - 1; j >= 0; --j)
        {
            if (board[i][j] == black)
            {
                cout << i << j << "   ";
            }
            else
            {
                cout << "XX   ";
            }
        }
        cout << endl;
    }
}

void pressAnyKey(string str)
{
    cout << str << "....";
    cout.flush();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cout << endl
         << endl
         << endl;
}

bool isEndGame()
{
}
void multiPlayer2()
{
    int count = 1;
    while (true)
    {
        if (count & 1)
        {
            chessboard();
            cellAssist();
        }
        else
        {
            reverseChessboard();
            reverseCellAssist();
        }

        string srcStr, destStr;
        int src, dest;

        cout << "Enter cell of piece\n";
        try
        {
            cin >> srcStr;
            if (srcStr == "q")
            {
                return;
            }
            src = stoi(srcStr);

            // Validate if src is within the valid range for the board
            if (src < 0 || src >= boardSize * 10)
            {
                cout << "Invalid cell coordinates\n";
                continue;
            }

            int i = src / 10;
            int j = fast_mod(src, 10);

            showMove(i, j, (count & 1) ? white : black);

            cout << "Enter your destination cell\n";
            cin >> destStr;
            if (destStr == "q")
            {
                return;
            }
            dest = stoi(destStr);

            // Validate if dest is within the valid range for the board
            if (dest < 0 || dest >= boardSize * 10)
            {
                cout << "Invalid destination coordinates\n";
                continue;
            }

            int k = dest / 10;
            int l = fast_mod(dest, 10);

            if (!checkPiece(i, j, k, l, (count & 1) ? white : black))
            {
                cout << "Invalid move\n";
                continue;
            }

            string piece = defaultBoard[i][j];
            reposition(i, j, k, l, (count & 1) ? white : black, piece);

            if (isCheck(k, l, (count & 1) ? white : black))
            {
                cout << (count & 1 ? "\nWhite" : "\nBlack") << " side is being checked\n";
            }

            chessboard();
            pressAnyKey("Press enter to switch sides");
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
            continue;
        }

        ++count;
        if (count == 50)
        {
            cout << "Match drawn \n";
            break;
        }
    }
}

void singlePlayer()
{
    string src, dest, side;
    int count;

    cout << "Choose your side\n";
    cout << "\n 1. White\n";
    cout << " 2. Black\n";
    try
    {
        cin >> side;
        if (side == "q")
        {
            return;
        }
        if(side=="1")
        {
            count=1;
        }
        else
        {
            count=0;
        }
    }
    catch (const std::exception &e)
    {
        cerr << "An exception occurred: " << e.what() << endl;
        return;
    }

    while (true)
    {
        if (count & 1)
        {
            chessboard();
            cellAssist();
        }
        else
        {
            reverseChessboard();
            reverseCellAssist();
        }

        vector<vector<string>> defaultBoardTemporary = defaultBoard;
        if (count & 1)
        {
            cout << "Enter cell of piece\n";
            try
            {
                cin >> src;
                if (src == "q")
                {
                    return;
                }
                int srcInt = stoi(src);
                int i = srcInt / 10;
                int j = fast_mod(srcInt, 10);

                // Validate if i and j are within the valid range for the board
                if (i < 0 || i >= boardSize || j < 0 || j >= boardSize)
                {
                    cout << "Invalid cell coordinates\n";
                    continue;
                }

                showMove(i, j, white);

                cout << "Enter your destination cell\n";
                cin >> dest;
                if (dest == "q")
                {
                    return;
                }
                int destInt = stoi(dest);
                int k = destInt / 10;
                int l = fast_mod(destInt, 10);

                // Validate if k and l are within the valid range for the board
                if (k < 0 || k >= boardSize || l < 0 || l >= boardSize)
                {
                    cout << "Invalid destination coordinates\n";
                    continue;
                }

                if (!checkPiece(i, j, k, l, white))
                {
                    cout << "Invalid move\n";
                    continue;
                }
                else
                {
                    string piece=defaultBoard[i][j];
                    reposition(i,j,k,l,white,piece); 
                }

                if (isCheck(k, l, white))
                {
                    cout << "\nWhite side is being checked\n";
                }
            }
            catch (const std::exception &e)
            {
                cerr << e.what() << '\n';
                continue;
            }
        }

        else
        {
            tuple<int, int, int> move = gameMove(black);
            int i = get<0>(move) / 10;
            int j = fast_mod(get<0>(move), 10);
            int k = get<1>(move) / 10;
            int l = fast_mod(get<1>(move), 10);
            string piece=defaultBoard[i][j];
            reposition(i,j,k,l,black,piece);
        }

        ++count;
        if (count == 50)
        {
            cout << "Match drawn \n";
            break;
        }
    }
}

void consoleSet()
{
    try
    {
        system("chcp 65001");
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    catch (exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int ui()
{
    consoleSet();
    cout << "Enter choices: or press 'q' anytime to return to menu\n";
    cout << " 1. Single player against computer\n";
    cout << " 2. Multiplayer against another player\n";
    cout << " 3. exit\n";
    cout << endl
         << endl
         << endl
         << endl;
    string x;
    try
    {
        cin >> x;
    }
    catch (exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    if (x == "1")
    {
        consoleSet();
        singlePlayer();
    }
    else if (x == "2")
    {
        consoleSet();
        multiPlayer2();
    }
    else if (x == "3")
    {
        return 0;
    }
    else
    {
        cout << "Invalid choice\n";
        return -1;
    }
    return 1;
}
int startGame()
{
    while (ui())
    {
    }
    return 0;
}
int main()
{
    // consoleSet();
    // cout<<heuristic(black)<<" "<<heuristic(white)<<endl;
    // multiPlayer();
    // ui();
    // cout<<fast_mod(101,10)<<endl;
    // cout<<fast_mod(102,10)<<endl;
    // cout<<fast_mod(100,10)<<endl;
    return startGame();

}