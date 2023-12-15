#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <limits>
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

bool isWhiteChecked = false;
bool isBlackChecked = false;

enum pieceType
{
    black,
    emptys,
    white,
    wKing,
    bKing
};

vector<vector<pieceType>> board = {
    {black, black, black, black, bKing, black, black, black},
    {black, black, black, black, black, black, black, black},
    {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
    {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
    {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
    {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
    {white, white, white, white, white, white, white, white},
    {white, white, white, white, wKing, white, white, white}};

vector<vector<string>> pieceBoard = {
    {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook},
    {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
    {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook}};

int startGame();
int userInterface();
void consoleSet();
void restartChessBoard();
void restartTileBoard();
void playerVsComputer();
void playerVsPlayer();
void chessboard();
void cellAssist();
void reverseChessboard();
void reverseCellAssist();
void showMove(int i, int j, pieceType sV);
bool isValidMove(int i, int j, int k, int l, pieceType sV);
int fast_mod(int number, int divider);
bool isCheck(int k, int l, pieceType sV);
void reposition(int i, int j, int k, int l, pieceType sV, string piece);
bool pressAnyKey(string str);
bool isEndGame();
void whitePrint(string str);
void blackPrint(string str);
tuple<int, int, int> gameMove(pieceType sV);
tuple<int, int, int> bestMove(vector<tuple<int, int, int>> allMoves);
bool compareTuple(const tuple<int, int, int> &a, const tuple<int, int, int> &b);
vector<tuple<int, int, int>> minimax(pieceType sV);
int heuristicFunction(pieceType sV);
bool pawnMove(int i, int j, int k, int l, pieceType sV);
bool knightMove(int i, int j, int k, int l, pieceType sV);
bool bishopMove(int i, int j, int k, int l, pieceType sV);
bool rookMove(int i, int j, int k, int l, pieceType sV);
bool queenMove(int i, int j, int k, int l, pieceType sV);
bool kingMove(int i, int j, int k, int l, pieceType sV, string piece);
bool isCheckForPawn(int k, int l, pieceType sV);
bool isCheckForKnight(int k, int l, pieceType sV);
bool isCheckForBishop(int k, int l, pieceType sV);
bool isCheckForRook(int i, int j, pieceType sV);
bool isCheckForQueen(int k, int l, pieceType sV);
bool isCheckForKings(int k, int l, pieceType sV);
bool isStalemate(pieceType sV);

int main()
{
    return startGame();
}

int startGame()
{
    while (userInterface())
    {
    }
    return 0;
}

int userInterface()
{
    consoleSet();
    restartChessBoard();
    restartTileBoard();
    cout << "Enter choices: or press 'q' anytime to return to menu\n";
    cout << " 1. Player vs Computer\n";
    cout << " 2. Player vs Player\n";
    cout << " 3. exit\n";
    cout << endl
         << endl
         << endl
         << endl;
    string x;
    cin >> x;
    if (x == "1")
    {
        consoleSet();
        playerVsComputer();
    }
    else if (x == "2")
    {
        consoleSet();
        playerVsPlayer();
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
        cerr << e.what() << '\n';
    }
}

void restartTileBoard()
{
    board = {
        {black, black, black, black, bKing, black, black, black},
        {black, black, black, black, black, black, black, black},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {emptys, emptys, emptys, emptys, emptys, emptys, emptys, emptys},
        {white, white, white, white, white, white, white, white},
        {white, white, white, white, wKing, white, white, white}};
}
void restartChessBoard()
{
    pieceBoard = {
        {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook}};
}

void playerVsPlayer()
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
        cin >> srcStr;
        if (srcStr == "q")
        {
            return;
        }
        src = stoi(srcStr);
        if (src < 0 or src >= boardSize * 10)
        {
            cout << "Invalid cell coordinates\n";
            continue;
        }

        int i = src / 10;
        int j = fast_mod(src, 10);

        if (count & 1)
        {
            showMove(i, j, white);
        }
        else
        {
            showMove(i, j, black);
        }
        cout << "Enter your destination cell\n";
        cin >> destStr;
        if (destStr == "q")
        {
            return;
        }
        dest = stoi(destStr);
        if (dest < 0 or dest >= boardSize * 10)
        {
            cout << "Invalid destination coordinates\n";
            continue;
        }
        int k = dest / 10;
        int l = fast_mod(dest, 10);

        if ((!isValidMove(i, j, k, l, white) and (count & 1)) or (!isValidMove(i, j, k, l, black) and !(count & 1)))
        {
            cout << "Invalid move\n";
            continue;
        }

        string piece = pieceBoard[i][j];
        reposition(i, j, k, l, (count & 1) ? white : black, piece);
        if (count & 1)
        {
            reposition(i, j, k, l, white, piece);
            if (isCheck(k, l, white))
            {
                cout << "Black side has been checked\n";
                isBlackChecked = true;
            }
            else
            {
                isBlackChecked = false;
            }
            chessboard();
        }
        else
        {
            reposition(i, j, k, l, black, piece);
            if (isCheck(k, l, black))
            {
                cout << "White side has been checked\n";
                isWhiteChecked = true;
            }
            else
            {
                isWhiteChecked = false;
            }
            reverseChessboard();
        }

        pressAnyKey("Press enter to switch sides");

        ++count;
        if (count == 50)
        {
            pressAnyKey("Press enter to continue\n");
            cout << "Match drawn \n";
            break;
        }
        if (isEndGame())
        {
            pressAnyKey("Press enter to continue \n");
            return;
        }
    }
}

void playerVsComputer()
{
    string src, dest, side;
    int count = 1;
    pieceType player, computer, turn;
    cout << "Choose your side\n\n\n";
    cout << " 1. White\n";
    cout << " 2. Black\n\n\n";
    cin >> side;
    if (side == "q")
    {
        return;
    }
    if (side == "1")
    {
        player = white;
        computer = black;
        turn = player;
    }
    else if (side == "2")
    {
        player = black;
        computer = white;
        turn = computer;
    }
    else
    {
        cout << "Invalid choice\n ";
        return;
    }

    while (true)
    {
        if (count & 1 and turn==player)
        {
            chessboard();
            cellAssist();
        }
        else if(turn == player)
        {
            reverseChessboard();
            reverseCellAssist();
        }

        if (turn == player)
        {
            cout << "Enter cell of piece\n";
            cin >> src;
            if (src == "q")
            {
                return;
            }
            int srcInt = stoi(src);
            int i = srcInt / 10;
            int j = fast_mod(srcInt, 10);

            if (i < 0 or i >= boardSize or j < 0 or j >= boardSize)
            {
                cout << "Invalid cell coordinates\n";
                continue;
            }
            showMove(i, j, player);
            cout << "Enter your destination cell\n";
            cin >> dest;
            if (dest == "q")
            {
                return;
            }
            int destInt = stoi(dest);
            int k = destInt / 10;
            int l = fast_mod(destInt, 10);
            if (k < 0 or k >= boardSize or l < 0 or l >= boardSize)
            {
                cout << "Invalid destination coordinates\n";
                continue;
            }

            if (!isValidMove(i, j, k, l, player))
            {
                cout << "Invalid move\n";
                continue;
            }
            string tempSrcPiece = pieceBoard[i][j];
            string tempDestPiece = pieceBoard[k][l];
            pieceType tempSrcSV = board[i][j];
            pieceType tempDestSV = board[k][l];
            reposition(i, j, k, l, player, tempSrcPiece);

            if (player == white)
            {
                chessboard();
            }
            else
            {
                reverseChessboard();
            }
            if (pressAnyKey("Press enter to continue or press 'u' to undo your move\n"))
            {
                pieceBoard[i][j] = tempSrcPiece;
                pieceBoard[k][l] = tempDestPiece;
                board[i][j] = tempSrcSV;
                board[k][l] = tempDestSV;
                continue;
            }
            if (isCheck(k, l, player))
            {
                if (player == white)
                {
                    isBlackChecked = true;
                }
                else
                {
                    isWhiteChecked = true;
                }
                cout << "\nComputer side is being checked\n";
            }

            turn = computer;
        }
        else
        {
            tuple<int, int, int> move = gameMove(computer);
            int i = get<0>(move) / 10;
            int j = fast_mod(get<0>(move), 10);
            int k = get<1>(move) / 10;
            int l = fast_mod(get<1>(move), 10);
            string piece = pieceBoard[i][j];
            reposition(i, j, k, l, computer, piece);
            if (isCheck(k, l, computer))
            {
                cout << "\nPlayer side is being checked\n";
                if (computer == white)
                {
                    isBlackChecked = true;
                }
                else
                {
                    isWhiteChecked = true;
                }
            }
            turn = player;
        }

        ++count;
        if (count == 50)
        {
            cout << "Match drawn \n";
            pressAnyKey("Press enter to continue \n");
            break;
        }

        if (isEndGame())
        {
            pressAnyKey("Press enter to continue \n");
            return;
        }
    }
}

void chessboard()
{
    int i, j;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if ((i + j) & 1)
            {
                whitePrint(pieceBoard[i][j]);
            }

            else
            {
                blackPrint(pieceBoard[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}
void reverseChessboard()
{
    int i, j;
    for (i = boardSize - 1; i >= 0; --i)
    {
        for (j = boardSize - 1; j >= 0; --j)
        {
            if ((i + j) & 1)
            {
                blackPrint(pieceBoard[i][j]);
            }
            else
            {
                whitePrint(pieceBoard[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}
void cellAssist()
{
    int i, j;
    cout << "Numbers are your piece and 'XX' are not your piece\n\n\n";
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == white or board[i][j] == wKing)
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
    cout << "Numbers are your piece and 'XX' are not your piece\n\n\n";
    for (i = boardSize - 1; i >= 0; --i)
    {
        for (j = boardSize - 1; j >= 0; --j)
        {
            if (board[i][j] == black or board[i][j] == bKing)
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

void blackPrint(string str)
{
    cout << "\033[0;100m  " << str << "   \033[0m";
}

void whitePrint(string str)
{
    cout << "\033[1;97m  " << str << "   \033[0m";
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

void reposition(int i, int j, int k, int l, pieceType sV, string piece)
{
    board[i][j] = emptys;
    board[k][l] = sV;
    pieceBoard[i][j] = " ";
    pieceBoard[k][l] = piece;
}

tuple<int, int, int> gameMove(pieceType sV)
{
    vector<tuple<int, int, int>> allMoves = minimax(sV);
    return bestMove(allMoves);
}

tuple<int, int, int> bestMove(vector<tuple<int, int, int>> allMoves)
{
    try
    {
        auto minElement = *min_element(allMoves.begin(), allMoves.end(), compareTuple);
        return minElement;
    }
    catch (exception &e)
    {
        cerr << e.what() << '\n';
        return make_tuple(0, 0, 0);
    }
}

bool compareTuple(const tuple<int, int, int> &a, const tuple<int, int, int> &b)
{
    return get<2>(a) < get<2>(b);
}

vector<tuple<int, int, int>> minimax(pieceType sV)
{
    vector<vector<string>> pieceBoardTemporary = pieceBoard;
    vector<vector<pieceType>> boardTemporary = board;
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
                        if (board[k][l] == sV)
                        {
                            continue;
                        }
                        try
                        {
                            if (isValidMove(i, j, k, l, sV))
                            {
                                reposition(i, j, k, l, sV, pieceBoard[i][j]);
                                int heuristic;
                                if (sV == white)
                                {
                                    heuristic = heuristicFunction(black);
                                }
                                else
                                {
                                    heuristic = heuristicFunction(white);
                                }
                                allMoves.push_back(make_tuple(i * 10 + j, k * 10 + l, heuristic));
                            }
                            pieceBoard = pieceBoardTemporary;
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
    pieceBoard = pieceBoardTemporary;
    board = boardTemporary;
    return allMoves;
}

int heuristicFunction(pieceType sV)
{
    int i, j;
    int state = 0;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (sV == white)
            {
                if (pieceBoard[i][j] == whitePawn)
                {
                    state += pawnValue;
                }
                else if (pieceBoard[i][j] == whiteBishop)
                {
                    state += bishopValue;
                }
                else if (pieceBoard[i][j] == whiteKnight)
                {
                    state += knightValue;
                }
                else if (pieceBoard[i][j] == whiteRook)
                {
                    state += rookValue;
                }
                else if (pieceBoard[i][j] == whiteQueen)
                {
                    state += queenValue;
                }
            }
            else if (sV == black)
            {
                if (pieceBoard[i][j] == blackPawn)
                {
                    state += pawnValue;
                }
                else if (pieceBoard[i][j] == blackBishop)
                {
                    state += bishopValue;
                }
                else if (pieceBoard[i][j] == blackKnight)
                {
                    state += knightValue;
                }
                else if (pieceBoard[i][j] == blackRook)
                {
                    state += rookValue;
                }
                else if (pieceBoard[i][j] == blackQueen)
                {
                    state += queenValue;
                }
            }
        }
    }
    return state;
}

void showMove(int i, int j, pieceType sV)
{
    vector<vector<string>> pieceBoardTemporary = pieceBoard;
    vector<vector<pieceType>> boardTemporary = board;
    cout << " '|' refers to source cell numbers mean possible cell of moves 'X' means invalid cell of moves\n\n\n";
    if (sV == white or sV == wKing)
    {
        for (int k = 0; k < boardSize; ++k)
        {
            for (int l = 0; l < boardSize; ++l)
            {
                if (i == k and j == l)
                {
                    cout << " | ";
                }
                else if (isValidMove(i, j, k, l, sV))
                {
                    cout << k << l << " ";
                }
                else
                {
                    cout << " X ";
                }
                board = boardTemporary;
                pieceBoard = pieceBoardTemporary;
            }
            cout << endl;
        }
    }
    else if (sV == black or sV == bKing)
    {
        for (int k = boardSize - 1; k >= 0; --k)
        {
            for (int l = boardSize - 1; l >= 0; --l)
            {
                if (i == k and j == l)
                {
                    cout << " | ";
                }
                else if (isValidMove(i, j, k, l, sV))
                {
                    cout << k << l << " ";
                }
                else
                {
                    cout << " X ";
                }
                board = boardTemporary;
                pieceBoard = pieceBoardTemporary;
            }
            cout << endl;
        }
    }
    cout << endl;
    board = boardTemporary;
    pieceBoard = pieceBoardTemporary;
}

bool isValidMove(int i, int j, int k, int l, pieceType sV)
{
    if (sV == white)
    {
        if (pieceBoard[i][j] == whitePawn)
        {
            return pawnMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == whiteRook)
        {
            return rookMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == whiteKnight)
        {
            return knightMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == whiteBishop)
        {
            return bishopMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == whiteQueen)
        {
            return queenMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == whiteKing)
        {
            return kingMove(i, j, k, l, sV, whiteKing);
        }
        return false;
    }
    else if (sV == black)
    {
        if (pieceBoard[i][j] == blackPawn)
        {
            return pawnMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == blackRook)
        {
            return rookMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == blackKnight)
        {
            return knightMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == blackBishop)
        {
            return bishopMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == blackQueen)
        {
            return queenMove(i, j, k, l, sV);
        }
        else if (pieceBoard[i][j] == blackKing)
        {
            return kingMove(i, j, k, l, sV, blackKing);
        }
        return false;
    }
    return false;
}

bool isStalemate(pieceType sV)
{

    int kingRow, kingCol, i, j;
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (pieceBoard[i][j] == whiteKing and sV == white)
            {
                kingRow = i;
                kingCol = j;
                break;
            }
            else if (pieceBoard[i][j] == blackKing and sV == black)
            {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
    }

    for (i = -1; i <= 1; ++i)
    {
        for (j = -1; j <= 1; ++j)
        {
            if (i == 0 and j == 0)
                continue;

            int newRow = kingRow + i;
            int newCol = kingCol + j;

            if (isValidMove(kingRow, kingCol, newRow, newCol, sV))
            {
                return false;
            }
        }
    }

    return true;
}

bool isCheck(int i, int j, pieceType sV)
{
    if (sV == white)
    {
        if (pieceBoard[i][j] == whitePawn)
        {
            return isCheckForPawn(i, j, white);
        }
        if (pieceBoard[i][j] == whiteRook)
        {
            return isCheckForRook(i, j, white);
        }
        if (pieceBoard[i][j] == whiteKnight)
        {
            return isCheckForKnight(i, j, white);
        }
        if (pieceBoard[i][j] == whiteBishop)
        {
            return isCheckForBishop(i, j, white);
        }
        if (pieceBoard[i][j] == whiteQueen)
        {
            return isCheckForQueen(i, j, white);
        }
        if (pieceBoard[i][j] == whiteKing)
        {
            return isCheckForKings(i, j, wKing);
        }
    }

    if (sV == black)
    {
        if (pieceBoard[i][j] == blackPawn)
        {
            return isCheckForPawn(i, j, black);
        }
        if (pieceBoard[i][j] == blackRook)
        {
            return isCheckForRook(i, j, black);
        }
        if (pieceBoard[i][j] == blackKnight)
        {
            return isCheckForKnight(i, j, black);
        }
        if (pieceBoard[i][j] == blackBishop)
        {
            return isCheckForBishop(i, j, black);
        }
        if (pieceBoard[i][j] == blackQueen)
        {
            return isCheckForQueen(i, j, black);
        }
        if (pieceBoard[i][j] == blackKing)
        {
            return isCheckForKings(i, j, bKing);
        }
    }
    return false;
}

bool pawnMove(int i, int j, int k, int l, pieceType sV)
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

    if ((pieceBoard[i][j] != whitePawn and sV == white) and (pieceBoard[i][j] != blackPawn and sV == black))
    {
        return false;
    }

    if (board[k][l] == emptys)
    {
        if (k == i + moveDirection and l == j)
        {
            return true;
        }

        if (i == startingRow and k == i + 2 * moveDirection and l == j and board[i + moveDirection][j] == emptys)
        {
            return true;
        }
    }

    if (k == i + moveDirection and (l == j + 1 or l == j - 1) and board[k][l] == (sV == white ? black : white))
    {
        return true;
    }

    return false;
}

bool rookMove(int i, int j, int k, int l, pieceType sV)
{
    if (sV != black and sV != white)
    {
        return false;
    }

    if (i == k)
    {
        int step;
        if (l > j)
        {
            step = 1;
        }
        else
        {
            step = -1;
        }
        for (int x = j + step; x != l; x += step)
        {
            if (board[i][x] != emptys)
            {
                return false;
            }
        }
    }
    else if (j == l)
    {
        int step;
        if (k > i)
        {
            step = 1;
        }
        else
        {
            step = -1;
        }
        for (int x = i + step; x != k; x += step)
        {
            if (board[x][j] != emptys)
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    if (board[k][l] != emptys and board[k][l] != sV)
    {
        return true;
    }
    else if (board[k][l] == emptys)
    {
        return true;
    }

    return false;
}

bool knightMove(int i, int j, int k, int l, pieceType sV)
{
    if (sV != black and sV != white)
    {
        return false;
    }

    int delta_i = abs(k - i);
    int delta_j = abs(l - j);

    if ((delta_i == 2 and delta_j == 1) or (delta_i == 1 and delta_j == 2))
    {
        if (board[k][l] == sV)
        {
            return false;
        }
        else if (board[k][l] == emptys or board[k][l]!=sV)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool bishopMove(int i, int j, int k, int l, pieceType sV)
{
    if (sV != black and sV != white)
    {
        return false;
    }

    int deltaRow = abs(k - i);
    int deltaCol = abs(l - j);

    if (deltaRow != deltaCol)
    {
        return false;
    }
    int rowIncrement = (k > i) ? 1 : -1;
    int colIncrement = (l > j) ? 1 : -1;

    for (int row = i + rowIncrement, col = j + colIncrement; row != k and col != l; row += rowIncrement, col += colIncrement)
    {
        if (board[row][col] != emptys)
        {
            return false;
        }
    }

    if (board[k][l] != emptys and board[k][l] == sV)
    {
        return false;
    }
    return true;
}

bool queenMove(int i, int j, int k, int l, pieceType sV)
{
    if (sV != black and sV != white)
    {
        return false;
    }

    int deltaRow = abs(k - i);
    int deltaCol = abs(l - j);

    if ((deltaRow == deltaCol) or (deltaRow == 0 and deltaCol != 0) or (deltaRow != 0 and deltaCol == 0))
    {
        int rowIncrement = (k > i) ? 1 : ((k < i) ? -1 : 0);
        int colIncrement = (l > j) ? 1 : ((l < j) ? -1 : 0);

        for (int row = i + rowIncrement, col = j + colIncrement; row != k or col != l; row += rowIncrement, col += colIncrement)
        {
            if (board[row][col] != emptys)
            {
                return false;
            }
        }
        if (board[k][l] != emptys and board[k][l] == sV)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool kingMove(int i, int j, int k, int l, pieceType sV, string piece)
{
    int delta_i = abs(k - i);
    int delta_j = abs(l - j);

    if (delta_i <= 1 and delta_j <= 1)
    {
        if (board[k][l] == sV)
        {
            return false;
        }
        else if (board[k][l] == emptys or board[k][l]!=sV)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool isCheckForPawn(int i, int j, pieceType sV)
{
    int mD = (sV == white) ? -1 : 1;
    int leftDiagonalRow = i + mD;
    int leftDiagonalCol = j - 1;
    int rightDiagonalRow = i + mD;
    int rightDiagonalCol = j + 1;

    if (leftDiagonalRow >= 0 and leftDiagonalRow < boardSize and leftDiagonalCol >= 0 and leftDiagonalCol < boardSize)
    {
        string king = (sV == white) ? blackKing : whiteKing;
        if (pieceBoard[leftDiagonalRow][leftDiagonalCol] == king)
        {
            return true;
        }
    }

    if (rightDiagonalRow >= 0 and rightDiagonalRow < boardSize and rightDiagonalCol >= 0 and rightDiagonalCol < boardSize)
    {
        string king = (sV == white) ? blackKing : whiteKing;
        if (pieceBoard[rightDiagonalRow][rightDiagonalCol] == king)
        {
            return true;
        }
    }

    return false;
}

bool isCheckForRook(int i, int j, pieceType sV)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int d = 0; d < 4; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];

        while (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if (pieceBoard[row][col] != " ")
            {
                if ((sV == white and pieceBoard[row][col] == blackKing) or (sV == black and pieceBoard[row][col] == whiteKing))
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

bool isCheckForBishop(int i, int j, pieceType sV)
{
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int d = 0; d < 4; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];

        while (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if (pieceBoard[row][col] != " ")
            {
                if ((sV == white and pieceBoard[row][col] == blackKing) or (sV == black and pieceBoard[row][col] == whiteKing))
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

bool isCheckForKnight(int i, int j, pieceType sV)
{
    int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int m = 0; m < 8; ++m)
    {
        int row = i + moves[m][0];
        int col = j + moves[m][1];

        if (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if ((sV == white and pieceBoard[row][col] == blackKing) or (sV == black and pieceBoard[row][col] == whiteKing))
            {
                return true;
            }
        }
    }

    return false;
}

bool isCheckForQueen(int i, int j, pieceType sV)
{
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};

    for (int d = 0; d < 8; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];

        while (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            if (pieceBoard[row][col] != " ")
            {
                string king = (sV == white) ? blackKing : whiteKing;
                if (pieceBoard[row][col] == king)
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

bool isCheckForKings(int i, int j, pieceType sV)
{
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};

    for (int d = 0; d < 8; ++d)
    {
        int row = i + directions[d][0];
        int col = j + directions[d][1];

        if (row >= 0 and row < boardSize and col >= 0 and col < boardSize)
        {
            string king = (sV == white) ? blackKing : whiteKing;
            if (pieceBoard[row][col] == king)
            {
                return true;
            }
        }
    }

    return false;
}

bool pressAnyKey(string str)
{
    cout << str << "....\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char ch;
    scanf("%c", &ch);
    if (ch == 'u')
    {
        cout << "undoing the move\n\n\n";
        return true;
    }

    cout << endl
         << endl
         << endl
         << "switching sides\n\n\n";
    return false;
}

bool isEndGame()
{
    if (heuristicFunction(white) == 0)
    {
        cout << "White side has lost\n";
        return true;
    }

    if (heuristicFunction(black) == 0)
    {
        cout << "Black side has lost\n";
        return true;
    }

    if (isWhiteChecked and isStalemate(white))
    {
        cout << "White side has lost\n";
        return true;
    }

    if (isBlackChecked and isStalemate(black))
    {
        cout << "Black side has lost\n";
        return true;
    }

    return false;
}