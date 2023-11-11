#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
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

const int pawnValue=1;
const int knightValue=3;
const int bishopValue=3;
const int rookValue=5;
const int queenValue=9;


enum squareValue
{
    black,
    emptys,
    white,
    king
};

vector<vector<squareValue>> board=
{
    {black,black,black,black,king,black,black,black},
    {black,black,black,black,black,black,black,black},
    {emptys,emptys,emptys,emptys,emptys,emptys,emptys,emptys},
    {emptys,emptys,emptys,emptys,emptys,emptys,emptys,emptys},
    {emptys,emptys,emptys,emptys,emptys,emptys,emptys,emptys},
    {emptys,emptys,emptys,emptys,emptys,emptys,emptys,emptys},
    {white,white,white,white,white,white,white,white},
    {white,white,white,white,king,white,white,white}
};




 vector<vector<string>> defaultBoard=
 {
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
    board[i][j]=emptys;
    board[k][l]=sV;
    defaultBoard[i][j]=" ";
    defaultBoard[k][l]=piece;
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
        if(board[k][l]==emptys) 
        {
            if(k==i+mD and l==j)
            {
                reposition(i,j,k,l,sV,whitePawn);
                return;
            }
            if(i==6 and k==i+2*mD and l==j and board[i+mD][j]==emptys) 
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
        if(board[k][l]==emptys) 
        {
            if(k==i+mD and l==j) 
            {
                reposition(i,j,k,l,sV,blackPawn);
                return;
            }
            if(i==1 and k==i+2*mD and l==j and board[i+mD][j]==emptys) 
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
            if(board[i][x]!=emptys)
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
            if(board[x][j]!=emptys) 
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
    if(board[k][l]!=emptys and board[k][l]!=sV)
    {
        reposition(i,j,k,l,sV,(sV==white) ? whiteRook : blackRook);
    }
    else if(board[k][l]==emptys) 
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
        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteKnight : blackKnight);
        } 
        else if(board[k][l]==emptys) 
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
            if (board[x][y]!=emptys) 
            {
                cout<<"Invalid move\n";
                return;
            }
        }
        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteBishop : blackBishop);
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteBishop : blackBishop);
        } 
        else   cout << "Invalid move\n";
    } 
    else   cout << "Invalid move\n"; 
}

void queenMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        cout<<"Invalid piece\n";
        return;
    }

    int delta_i=abs(k - i);
    int delta_j=abs(l - j);

    if((delta_i==delta_j) or (delta_i==0 and delta_j!=0) or (delta_i!=0 and delta_j==0)) 
    {
        
        int step_i=(k>i) ? 1 : ((k<i) ? -1 : 0);
        int step_j=(l>j) ? 1 : ((l<j) ? -1 : 0);

        for(int x=i+step_i,y=j+step_j;x!=k or y!=l;x+=step_i,y+=step_j) 
        {
            if(board[x][y]!=emptys) 
            {
                cout<<"Invalid move\n";
                return;
            }
        }

        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteQueen : blackQueen);
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteQueen : blackQueen);
        } 
        else 
        {
            cout << "Invalid move\n"; 
        }
    } 
    else 
    {
        cout<<"Invalid move\n"; 
    }
}

void kingMove(int i,int j,int k,int l,squareValue sV,string piece) 
{
    if(sV!=king) 
    {
        cout<<"Invalid piece\n";
        return;
    }

    int delta_i=abs(k-i);
    int delta_j=abs(l-j);

    if(delta_i<=1 and delta_j<=1) 
    {
        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,piece);
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,piece);
        } 
        else  cout<<"Invalid move\n";
    }
    else  cout<<"Invalid move\n";
}


bool isCheckForPawn(int i,int j,squareValue sV) 
{
    int mD=(sV==white) ? -1 : 1;
    int leftDiagonalRow=i+mD;
    int leftDiagonalCol=j-1;
    int rightDiagonalRow=i+mD;
    int rightDiagonalCol=j+1;

    if(leftDiagonalRow>=0 and leftDiagonalRow<boardSize and leftDiagonalCol>=0 and leftDiagonalCol<boardSize) 
    {
        string king=(sV==white) ? blackKing : whiteKing;
        if(defaultBoard[leftDiagonalRow][leftDiagonalCol]==king) 
        {
            return true;
        }
    }
    if(rightDiagonalRow>=0 and rightDiagonalRow<boardSize and rightDiagonalCol>=0 and rightDiagonalCol<boardSize) 
    {
        string king=(sV==white) ? blackKing : whiteKing;
        if(defaultBoard[rightDiagonalRow][rightDiagonalCol]==king) 
        {
            return true;
        }
    }
    return false;
}

bool isCheckForRook(int i,int j,squareValue sV) 
{
    int directions[4][2]={{-1,0}, {1,0}, {0,-1}, {0,1}};

    for(int d=0;d<4;++d) 
    {
        int row=i+directions[d][0];
        int col=j+directions[d][1];
        while (row>=0 and row<boardSize and col>=0 and col<boardSize) 
        {
            if(defaultBoard[row][col]!=" ") 
            {
                if((sV==white and defaultBoard[row][col]==blackKing) or (sV==black and defaultBoard[row][col]==whiteKing)) 
                {
                    return true; 
                }
                break; 
            }
            row+=directions[d][0];
            col+=directions[d][1];
        }
    }
    return false; 
}

bool isCheckForBishop(int i,int j,squareValue sV) 
{
    int directions[4][2]={{-1,-1}, {-1,1}, {1,-1}, {1,1}};
    for(int d=0;d<4;++d) 
    {
        int row=i+directions[d][0];
        int col=j+directions[d][1];
        while(row>=0 and row<boardSize and col>=0 and col<boardSize) 
        {
            if(defaultBoard[row][col]!=" ") 
            {
                if((sV==white and defaultBoard[row][col]==blackKing) or (sV==black and defaultBoard[row][col]==whiteKing)) 
                {
                    return true; 
                }
                break; 
            }
            row+=directions[d][0];
            col+=directions[d][1];
        }
    }
    return false; 
}

bool isCheckForKnight(int i,int j,squareValue sV) 
{
    int moves[8][2]={{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};
    for(int m=0;m<8;++m) 
    {
        int row=i+moves[m][0];
        int col=j+moves[m][1];
        if(row>=0 and row<boardSize and col>=0 and col<boardSize) 
        {
            if((sV==white and defaultBoard[row][col]==blackKing) or (sV==black and defaultBoard[row][col]==whiteKing)) 
            {
                return true; 
            }
        }
    }
    return false; 
}

bool isCheckForQueen(int i,int j,squareValue sV) 
{
    int directions[8][2]={{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {1,1}, {-1,1}, {1,-1}};
    for (int d=0;d<8;++d) 
    {
        int row=i+directions[d][0];
        int col=j+directions[d][1];
        while(row>=0 and row<boardSize and col>=0 and col<boardSize) 
        {
            if(defaultBoard[row][col]!=" ") 
            {                
                string king=(sV == white) ? blackKing : whiteKing;
                if(defaultBoard[row][col]==king) 
                {
                    return true; 
                } 
                else 
                {
                    break;
                }
            }
            row+=directions[d][0];
            col+=directions[d][1];
        }
    }
    return false;
}

bool isCheckForKings(int i,int j,squareValue sV) 
{
    int directions[8][2]={{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {1,1}, {-1,1}, {1,-1}};
    for(int d=0;d<8;++d) 
    {
        int row=i+directions[d][0];
        int col=j+directions[d][1];
        if(row>=0 and row<boardSize and col>=0 and col<boardSize) 
        {
            string king=(sV == white) ? blackKing : whiteKing;
            if(defaultBoard[row][col]==king) 
            {
                return true;
            }
        }
    }
    return false; 
}
bool isCheck(int i,int j,squareValue sV)
{
    if(sV==white)
    {
        if(defaultBoard[i][j]==whitePawn) 
        {
            return isCheckForPawn(i,j,white);
        }
        if(defaultBoard[i][j]==whiteRook) 
        {
            return isCheckForRook(i,j,white);
        }
        if(defaultBoard[i][j]==whiteKnight) 
        {
            return isCheckForKnight(i,j,white);
        }
        if(defaultBoard[i][j]==whiteBishop)
        {
            return isCheckForBishop(i,j,white);
        } 
        if(defaultBoard[i][j]==whiteQueen) 
        {
            return isCheckForQueen(i,j,white);
        }
        if(defaultBoard[i][j]==whiteKing) 
        {
            return isCheckForKings(i,j,king);
        }     
    }
    if(sV==black)
    {
        if(defaultBoard[i][j]==blackPawn) 
        {
            return isCheckForPawn(i,j,black);
        }
        if(defaultBoard[i][j]==blackRook) 
        {
            return isCheckForRook(i,j,black);
        }
        if(defaultBoard[i][j]==blackKnight) 
        {
            return isCheckForKnight(i,j,black);
        }
        if(defaultBoard[i][j]==blackBishop) 
        {
            return isCheckForBishop(i,j,black);
        }
        if(defaultBoard[i][j]==blackQueen) 
        {
            return isCheckForQueen(i,j,black);
        }    
        if(defaultBoard[i][j]==blackKing) 
        {
            return isCheckForKings(i,j,black);
        }         
    }
    return false;
}

void checkPiece(int i,int j,int k,int l,squareValue sV)
{
    if(sV==white)
    {
        if(defaultBoard[i][j]==whitePawn) 
        {
            pawnMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteRook) 
        {
            rookMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteKnight) 
        {
            knightMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteBishop)
        {
            bishopMove(i,j,k,l,sV);
        } 
        else if(defaultBoard[i][j]==whiteQueen) 
        {
            queenMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteKing) 
        {
            kingMove(i,j,k,l,sV,whiteKing);
        }     
    }
    else if(sV==black)
    {
        if(defaultBoard[i][j]==blackPawn) 
        {
            pawnMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackRook) 
        {
            rookMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackKnight) 
        {
            knightMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackBishop) 
        {
            bishopMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackQueen) 
        {
            queenMove(i,j,k,l,sV);
        }    
        else if(defaultBoard[i][j]==blackKing) 
        {
            kingMove(i,j,k,l,sV,blackKing);
        }         
    }
}
int heuristic(squareValue sV)
{
    int i,j;
    int state=0;
    for(i=0;i<boardSize;++i)
    {
        for(j=0;j<boardSize;++j)
        {
            if(sV==white)
            {
                if(defaultBoard[i][j]==whitePawn)
                {
                    state+=pawnValue;
                }
                else if(defaultBoard[i][j]==whiteBishop)
                {
                    state+=bishopValue;
                }
                else if(defaultBoard[i][j]==whiteKnight)
                {
                    state+=knightValue;
                }
                else if(defaultBoard[i][j]==whiteQueen)
                {
                    state+=queenValue;
                }
            }
            else if(sV==black)
            {
                if(defaultBoard[i][j]==blackPawn)
                {
                    state+=pawnValue;
                }
                else if(defaultBoard[i][j]==blackBishop)
                {
                    state+=bishopValue;
                }
                else if(defaultBoard[i][j]==blackKnight)
                {
                    state+=knightValue;
                }
                else if(defaultBoard[i][j]==blackQueen)
                {
                    state+=queenValue;
                }
            }
        }
    }
    return state;
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




bool isEndGame()
{
    
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
        if(count & 1) 
        {
            checkPiece(i,j,k,l,white);
            if(isCheck(k,l,white)) 
            {
                cout<<"\nWhite side is being checked\n";
            }
        }
        else 
        {
            checkPiece(i,j,k,l,black);
            if(isCheck(k,l,black))
            {
                cout<<"\nBlack side has been checked\n";
            }
        }
        ++count;
        if(count==50)
        {
            cout<<"Match drawn \n";
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
    catch(exception& e)
    {

    }
}
int main()
{
    consoleSet();
    //cout<<heuristic(black)<<" "<<heuristic(white)<<endl;
    game();
}