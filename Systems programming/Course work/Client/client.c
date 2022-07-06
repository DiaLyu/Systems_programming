#include <windows.h> 
#include <stdio.h>
#include <conio.h>

int main()
{
    HANDLE hPipe;
    LPTSTR lpvMessage;
    char  Buf[50];
    BOOL   fSuccess = FALSE;
    DWORD  cbRead, cbToWrite, cbWritten, dwMode;
    LPCWSTR PipeName = L"\\\\.\\pipe\\$MyPipe$";

    printf("Waiting for connection to server....\n");
    //����������� � ������
    hPipe = CreateFile(
        PipeName, GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL);


    while (1) {
        printf("=> ");
        fgets(Buf, 10, stdin);
        //������� �������� �������
        if (!strcmp(Buf, "exit\n")) break;
        else {
            //�������� ������ �������
            WriteFile(hPipe, Buf, 50, &cbWritten, NULL);
            // ������ ��������� �� ������
            ReadFile(hPipe, Buf, 50, &cbRead, NULL);
            printf("%s\n", Buf);
        }
    }

    printf("\nClosing the program, press ENTER to exit");
    _getch();
    CloseHandle(hPipe);
    return 0;
}
