#include<iostream>
#include<vector>
#include<cstring>
#ifdef _WIN32
#include<Windows.h>
#endif
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
    {blackRook,blackKnight,blackBishop,blackQueen,blackKing,blackBishop,blackKnight,blackRook},
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

void pawnMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV==white) 
    {
        if(defaultBoard[i][j]!=whitePawn) 
        {
            cout<<"Invalid move\n";
            return;
        }
        int mD=-1; 
        if(board[k][l]==empty) 
        {
            if(k==i+mD and l==j)
            {
                reposition(i,j,k,l,sV,whitePawn);
                return;
            }
            if(i==6 and k==i+2*mD and l==j and board[i+mD][j]==empty) 
            {
                reposition(i,j,k,l,sV,whitePawn);
                return;
            }
        }
        if(k==i+mD and (l==j+1 or l==j-1) and board[k][l]==black) 
        {
            reposition(i,j,k,l,sV,whitePawn);
            return;
        }
    } 
    else if(sV==black) 
    {
        if(defaultBoard[i][j]!=blackPawn) 
        {
            cout<<"Invalid move\n";
            return;
        }
        int mD = 1;
        if(board[k][l]==empty) 
        {
            if(k==i+mD and l==j) 
            {
                reposition(i,j,k,l,sV,blackPawn);
                return;
            }
            if(i==1 and k==i+2*mD and l==j and board[i+mD][j]==empty) 
            {
                reposition(i,j,k,l,sV,blackPawn);
                return;
            }
        }
        if(k==i+mD and (l==j+1 or l==j-1) and board[k][l]==white) 
        {
            reposition(i,j,k,l,sV,blackPawn);
            return;
        }
    }
    cout<< "Invalid move\n";
}

void rookMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        cout<<"Invalid piece\n";
        return;
    }
    if(i==k) 
    {
        int step=(l>j) ? 1 : -1;
        for(int x=j+step;x!=l;x+=step)
        {
            if(board[i][x]!=empty)
            {
                cout<<"Invalid move\n";
                return;
            }
        }
    } 
    else if(j==l)
    {
        int step=(k>i) ? 1 : -1;
        for(int x=i+step;x!=k;x+=step) 
        {
            if(board[x][j]!=empty) 
            {
                cout <<"Invalid move\n";
                return;
            }
        }
    } 
    else 
    {
        cout<<"Invalid move\n";
        return;
    }
    if(board[k][l]!=empty and board[k][l]!=sV)
    {
        reposition(i,j,k,l,sV,(sV==white) ? whiteRook : blackRook);
    }
    else if(board[k][l]==empty) 
    {
        reposition(i,j,k,l,sV,(sV == white) ? whiteRook : blackRook);
    }
    else  cout<<"Invalid move\n";
}

void knightMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        cout<<"Invalid piece\n";
        return;
    }
    int delta_i=abs(k-i);
    int delta_j=abs(l-j);
    if((delta_i==2 and delta_j==1) or (delta_i==1 and delta_j==2)) 
    {
        if(board[k][l]!=empty and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteKnight : blackKnight);
        } 
        else if(board[k][l]==empty) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteKnight : blackKnight);
        } 
        else cout<<"Invalid move\n";
    } 
    else  cout<<"Invalid move\n"; 
}

void bishopMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        cout<<"Invalid piece\n";
        return;
    }
    int delta_i=abs(k-i);
    int delta_j=abs(l-j);
    if(delta_i==delta_j) 
    {
        int step_i=(k>i) ? 1 : -1;
        int step_j=(l>j) ? 1 : -1;
        for(int x=i+step_i,y=j+step_j;x!=k and y!=l;x+=step_i,y+=step_j) 
        {
            if (board[x][y]!=empty) 
            {
                cout<<"Invalid move\n";
                return;
            }
        }
        if(board[k][l]!=empty and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteBishop : blackBishop);
        } 
        else if(board[k][l]==empty) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteBishop : blackBishop);
        } 
        else   cout << "Invalid move\n";
    } 
    else   cout << "Invalid move\n"; 
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
/*void whitePrint(string str)
{
    cout<<"\033[0m  "<<str<<"  ";
}
/*void blackPrint(string str)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout<<"  "<<str<<"  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}*/
/*=void blackPrint(string str)
{
    cout<<"\033[0;100m"<<str<<" \033[0m";
}*/

void printWithColor(string str,int textColor,int bgColor)
{
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),textColor | (bgColor<<4));
    cout<<"  "<<str<<"  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    #endif
}

void whitePrint(string str)
{
    printWithColor(str,15,0);
}

void blackPrint(string str)
{
    printWithColor(str,0,15);
}

void chessboard()
{

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
void reverseChessboard()
{
    int i,j;
    for(i=boardSize-1;i>=0;--i)
    {
        for(j=boardSize-1;j>=0;--j)
        {
            if((i+j) & 1) blackPrint(defaultBoard[i][j]);
            else whitePrint(defaultBoard[i][j]);
        }
        cout<<endl;
    }
}
void cellAssist()
{
    int i,j;
    for(i=0;i<boardSize;++i)
    {
        for(j=0;j<boardSize;++j)
        {
            cout<<i<<j<<"   ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void reverseCellAssist()
{
    int i,j;
    for(i=boardSize-1;i>=0;--i)
    {
        for(j=boardSize-1;j>=0;--j)
        {
            cout<<i<<j<<"   ";
        }
        cout<<endl;
    }
}
void game()
{
    int src,dest,count=1;
    while(true)
    {
        if(count&1) 
        {
            //system("cls");
            chessboard();
            cellAssist();
        }
        else 
        {
            reverseChessboard();
            reverseCellAssist();
        }
        cout<<"Enter source cell and destination cell\n";
        cin>>src>>dest;
        int i=src/10;
        int j=src%10;
        int k=dest/10;
        int l=dest%10;
        if(count & 1) checkPiece(i,j,k,l,white);
        else checkPiece(i,j,k,l,black);
        ++count;
        if(count==50)
        {
            cout<<"Match drawn \n";
            break;
        }
    }
}
int main()
{
    system("cls");
    game();
}