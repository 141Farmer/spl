#include<iostream>
#ifdef _WIN32
#include<Windows.h>
#endif
using namespace std;

int boardSize=8;
bool board[8][8];
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}
CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
BOOL GetCurrentConsoleFontEx(HANDLE hConsoleOutput,BOOL bMaximumWindow,PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
HANDLE GetStdHandle(DWORD nStdHandle);



void setFont()
{
    #ifdef _WIN32

    CONSOLE_FONT_INFOEX fontex;
    fontex.cbSize=sizeof(CONSOLE_FONT_INFOEX);
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(handle,FALSE,&fontex);

    fontex.dwFontSize.X=20;
    fontex.dwFontSize.Y=20;

    SetCurrentConsoleFontEx(handle,FALSE,&fontex);

    #endif
}
void chessboard()
{
    int i,j;
    for(i=0;i<boardSize;++i)
    {
        for(j=0;j<boardSize;++j)
        {
            if((i+j) & 1) cout<<"\u25A1";
            else cout<<"\u25A0";
        }
        cout<<endl;
    }

}
int main()
{
    chessboard();

}