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
bool pawnMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV==white) 
    {
        if(defaultBoard[i][j]!=whitePawn) 
        {
            //cout<<"Invalid move\n";
            return false;
        }
        int mD=-1; 
        if(board[k][l]==emptys) 
        {
            if(k==i+mD and l==j)
            {
                reposition(i,j,k,l,sV,whitePawn);
                return true;
            }
            if(i==6 and k==i+2*mD and l==j and board[i+mD][j]==emptys) 
            {
                reposition(i,j,k,l,sV,whitePawn);
                return true;
            }
        }
        if(k==i+mD and (l==j+1 or l==j-1) and board[k][l]==black) 
        {
            reposition(i,j,k,l,sV,whitePawn);
            return true;
        }
    } 
    else if(sV==black) 
    {
        if(defaultBoard[i][j]!=blackPawn) 
        {
            //cout<<"Invalid move\n";
            return false;
        }
        int mD = 1;
        if(board[k][l]==emptys) 
        {
            if(k==i+mD and l==j) 
            {
                reposition(i,j,k,l,sV,blackPawn);
                return true;
            }
            if(i==1 and k==i+2*mD and l==j and board[i+mD][j]==emptys) 
            {
                reposition(i,j,k,l,sV,blackPawn);
                return true;
            }
        }
        if(k==i+mD and (l==j+1 or l==j-1) and board[k][l]==white) 
        {
            reposition(i,j,k,l,sV,blackPawn);
            return true;
        }
    }
    //cout<< "Invalid move\n";
    return false;
}

bool rookMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        //cout<<"Invalid piece\n";
        return false;
    }
    if(i==k) 
    {
        int step=(l>j) ? 1 : -1;
        for(int x=j+step;x!=l;x+=step)
        {
            if(board[i][x]!=emptys)
            {
                //cout<<"Invalid move\n";
                return true;
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
                //cout <<"Invalid move\n";
                return false;
            }
        }
    } 
    else 
    {
        //cout<<"Invalid move\n";
        return false;
    }
    if(board[k][l]!=emptys and board[k][l]!=sV)
    {
        reposition(i,j,k,l,sV,(sV==white) ? whiteRook : blackRook);
        return true;
    }
    else if(board[k][l]==emptys) 
    {
        reposition(i,j,k,l,sV,(sV == white) ? whiteRook : blackRook);
        return true;
    }
    //else  cout<<"Invalid move\n";
    return false;
}

bool knightMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        //cout<<"Invalid piece\n";
        return false;
    }
    int delta_i=abs(k-i);
    int delta_j=abs(l-j);
    if((delta_i==2 and delta_j==1) or (delta_i==1 and delta_j==2)) 
    {
        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteKnight : blackKnight);
            return true;
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteKnight : blackKnight);
            return true;
        } 
        else 
        {
            //cout<<"Invalid move\n";
            return false;
        }

    } 
   // else  cout<<"Invalid move\n"; 
    return false;
}

bool bishopMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        //cout<<"Invalid piece\n";
        return false;
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
                //cout<<"Invalid move\n";
                return false;
            }
        }
        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteBishop : blackBishop);
            return true;
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,(sV == white) ? whiteBishop : blackBishop);
            return true;
        } 
        else   
        {
            //cout << "Invalid move\n";
            return false;
        }
    } 
    ///else   cout << "Invalid move\n"; 
    return false;
}

bool queenMove(int i,int j,int k,int l,squareValue sV) 
{
    if(sV!=black and sV!=white) 
    {
        //cout<<"Invalid piece\n";
        return false;
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
               // cout<<"Invalid move\n";
                return false;
            }
        }

        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteQueen : blackQueen);
            return true;
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,(sV==white) ? whiteQueen : blackQueen);
            return true;
        } 
        else 
        {
            //cout << "Invalid move\n"; 
            return false;
        }
    } 
    else 
    {
        //cout<<"Invalid move\n"; 
    }
    return false;
}

bool kingMove(int i,int j,int k,int l,squareValue sV,string piece) 
{
    if(sV!=king) 
    {
        //cout<<"Invalid piece\n";
        return false;
    }

    int delta_i=abs(k-i);
    int delta_j=abs(l-j);

    if(delta_i<=1 and delta_j<=1) 
    {
        if(board[k][l]!=emptys and board[k][l]!=sV) 
        {
            reposition(i,j,k,l,sV,piece);
            return true;
        } 
        else if(board[k][l]==emptys) 
        {
            reposition(i,j,k,l,sV,piece);
            return true;
        } 
        else  
        {
            //cout<<"Invalid move\n";
            return false;
        }

    }
    //else  cout<<"Invalid move\n";
    return false;
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

bool checkPiece(int i,int j,int k,int l,squareValue sV)
{
    if(sV==white)
    {
        if(defaultBoard[i][j]==whitePawn) 
        {
            return pawnMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteRook) 
        {
            return rookMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteKnight) 
        {
            return knightMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteBishop)
        {
            return bishopMove(i,j,k,l,sV);
        } 
        else if(defaultBoard[i][j]==whiteQueen) 
        {
            return queenMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==whiteKing) 
        {
            return kingMove(i,j,k,l,sV,whiteKing);
        }   
        return false;  
    }
    else if(sV==black)
    {
        if(defaultBoard[i][j]==blackPawn) 
        {
            return pawnMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackRook) 
        {
            return rookMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackKnight) 
        {
            return knightMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackBishop) 
        {
            return bishopMove(i,j,k,l,sV);
        }
        else if(defaultBoard[i][j]==blackQueen) 
        {
            return queenMove(i,j,k,l,sV);
        }    
        else if(defaultBoard[i][j]==blackKing) 
        {
            return kingMove(i,j,k,l,sV,blackKing);
        }     
        return false;    
    }
    return false;
}

void showMove(int i,int j,squareValue sV)
{
    vector<vector<string>>defaultBoardTemporary=defaultBoard;
    vector<vector<squareValue>>boardTemporary=board;
    if(sV==white)
    {
        for(int k=0;k<boardSize;++k)
        {
            for(int l=0;l<boardSize;++l)
            {
                if(checkPiece(i,j,k,l,sV))
                {
                    cout<<k<<l<<" ";
                }
                else
                {
                    cout<<"   ";
                }
                board=boardTemporary;
                defaultBoard=defaultBoardTemporary;
            }
            cout<<endl;
        }   
    }
    else if(sV==black)
    {
        for(int k=boardSize-1;k>=0;--k)
        {
            for(int l=boardSize-1;l>=0;--l)
            {
                if(checkPiece(i,j,k,l,sV))
                {
                    cout<<k<<l<<" ";
                }
                else
                {
                    cout<<"   ";
                }
                board=boardTemporary;
                defaultBoard=defaultBoardTemporary;
            }
            cout<<endl;
        }
    }
    cout<<endl;
    board=boardTemporary;
    defaultBoard=defaultBoardTemporary;


}






int heuristic(squareValue sV,vector<vector<string>>defaultBoard)
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
struct move
{
    int srcCell;
    int destCell;
    int nextHeuristicValue;
};













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
void multiPlayer2()
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
        cout<<"Enter cell of piece\n";
        cin>>src;
        int i=src/10;
        int j=src%10;
        vector<vector<string>>defaultBoardTemporary=defaultBoard;
        if(count & 1) 
        {
            /*checkPiece(i,j,k,white);
            if(isCheck(k,l,white)) 
            {
                cout<<"\nWhite side is being checked\n";
            }*/
            showMove(i,j,white);
            cout<<"Enter your destination cell\n";
            cin>>dest;
            int k=dest/10;
            int l=dest%10;
            if(!checkPiece(i,j,k,l,white))
            {
                cout<<"Invalid move\n";
               // --count;
                continue;
            }
            if(isCheck(k,l,white)) 
            {
                cout<<"\nWhite side is being checked\n";
            }

        }
        else 
        {
            showMove(i,j,black);
            cout<<"Enter your destination cell\n";
            cin>>dest;
            int k=dest/10;
            int l=dest%10;
            if(!checkPiece(i,j,k,l,black))
            {
                cout<<"Invalid move\n";
                //--count;
                continue;
            }
            if(isCheck(k,l,black)) 
            {
                cout<<"\nBlack side is being checked\n";
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

void multiPlayer1()
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
void singlePlayer()
{

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


void ui()
{
    consoleSet();
    cout<<"Enter choices:\n";
    cout<<" 1. Single player against computer\n";
    cout<<" 2. Multiplayer against another player\n";
    cout<<" 3. exit\n";
    int x;
    try
    {
        cin>>x;
    }
    catch(const std::exception& e)
    {

    }
    if(x==1)    
    {
        singlePlayer();
    }
    else if(x==2)       
    {
        multiPlayer2();
    }
    else if(x==3)
    {
        return;
    }
    else
    {
        cout<<"Invalid choice\n";
    }
}
int main()
{
    /*consoleSet();
    //cout<<heuristic(black)<<" "<<heuristic(white)<<endl;
    multiPlayer();*/
    ui();
}