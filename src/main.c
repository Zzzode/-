#include <windows.h>
#include "graphics.h"
#include "Menu.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil) {
    MSG messages;  /* Here messages to the application are saved */

    //    Login();
    ShowMainWindow(messages);

    return messages.wParam;
}