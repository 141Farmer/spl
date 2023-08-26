#include<iostream>
#include<Windows.h>
#include<vector>
#include<cstring>
using namespace std;

const int boardSize=8;

const string whitePawn="\u2659";
const string blackPawn="\u265F";
const string whiteKnight="\u2658";
const string blackKnight="\u265E";
const string whiteBishop="\u2657";
const string blackBishop="\u265D";
const string whiteRook="\u2656";
const string blackRook="\u265C";
const string whiteQueen="\u2655";
const string blackQueen="\u265B";
const string whiteKing="\u2654";
const string blackKing="\u265A";

enum squareValue
{
    black,
    empty,
    white,
    king
};

vector<vector<squareValue>> board={
    {black,black,black,black,king,black,black,black},
    {black,black,black,black,black,black,black,black},
    {empty,empty,empty,empty,empty,empty,empty,empty},
    {empty,empty,empty,empty,empty,empty,empty,empty},
    {empty,empty,empty,empty,empty,empty,empty,empty},
    {empty,empty,empty,empty,empty,empty,empty,empty},
    {white,white,white,white,white,white,white,white},
    {white,white,white,white,king,white,white,white}
};




 vector<vector<string>> defaultBoard={
    {blackRook,blackKnight,blackBishop,blackQueen,blackKing,blackBishop,blackKing,blackRook},
    {blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn,blackPawn},
    {" "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "},
    {whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn,whitePawn},
    {whiteRook,whiteKnight,whiteBishop,whiteQueen,whiteKing,whiteBishop,whiteKnight,whiteRook}
};

void reposition(int i,int j,int k,int l,squareValue sV,string piece)
{
    if(sV==black)
    {
        board[i][j]=empty;
        board[k][l]=black;
        defaultBoard[i][j]=" ";
        defaultBoard[k][l]=piece;
    }
    if(sV==white)
    {
        board[i][j]=empty;
        board[k][l]=white;
        defaultBoard[i][j]=" ";
        defaultBoard[k][l]=piece;
    }

}

void pawnMove(int i,int j,int k,int l,squareValue sV) // work left
{
    
}

void rookMove(int i,int j,int k,int l,squareValue sV)
{
    if(sV==white)
    {
        if(defaultBoard[i][j]!=whiteRook)
        {
            cout<<"Invalid move\n";
            return ;
        }
        
        
        if(board[k][l]==empty or board[k][l]==black)
        {
            board[k][l]=white;
            defaultBoard[i][j]=" ";
            defaultBoard[k][l]=whiteRook;
        }

    }
    if(sV==black)
    {
        if(defaultBoard[i][j]!=blackRook)
        {
            cout<<"Invalid move\n";
            return ;
        }
        if(i!=k)
        {
            cout<<"Invalid move\n";
            return ;
        }
        if(j!=l)
        {
            cout<<"Invalid move\n";
            return ;
        }
        
        
        if(board[k][l]==empty or board[k][l]==white)
        {
            board[k][l]=white;
            defaultBoard[i][j]=" ";
            defaultBoard[k][l]=whiteRook;
        }

    }
}
void knightMove(int i,int j,int k,int l,squareValue sV)
{

}
void bishopMove(int i,int j,int k,int l,squareValue sV)
{

}
void queenMove(int i,int j,int k,int l,squareValue sV)
{

}
void kingMove(int i,int j,int k,int l,squareValue sV)
{

}
void checkPiece(int i,int j,int k,int l,squareValue sV)
{
    if(sV==white)
    {
        if(defaultBoard[i][j]==whitePawn) 
            pawnMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==whiteRook) 
            rookMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==whiteKnight) 
            knightMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==whiteBishop) 
            bishopMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==whiteQueen) 
            queenMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==whiteKing) 
            kingMove(i,j,k,l,sV);
    }
    else if(sV==black)
    {
        if(defaultBoard[i][j]==blackPawn) 
            pawnMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==blackRook) 
            rookMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==blackKnight) 
            knightMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==blackBishop) 
            bishopMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==blackQueen) 
            queenMove(i,j,k,l,sV);
        else if(defaultBoard[i][j]==blackKing) 
            kingMove(i,j,k,l,sV);
    }

}
void whitePrint(string str)
{
    cout<<"\033[0m  "<<str<<"  ";
}
void blackPrint(string str)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout<<"  "<<str<<"  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
/*void blackPrint(string str)
{
    cout<<"\033[0;100m"<<str<<" \033[0m";
}*/


void chessboard()
{
    //system("cls");

    int i,j;
    for(i=0;i<boardSize;++i)
    {
        for(j=0;j<boardSize;++j)
        {
            if((i+j) & 1)  whitePrint(defaultBoard[i][j]);
            else blackPrint(defaultBoard[i][j]);
        }
        cout<<endl;
    }

}
int main()
{
    chessboard();
    //pawnMove(1,2,black);
    //pawnMove(6,2,white);
    chessboard();
}