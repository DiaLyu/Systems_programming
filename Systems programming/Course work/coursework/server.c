#include <stdio.h>
#include <string.h>
#include <windows.h>
#include<conio.h>

int sum_of_numbers = 0;

DWORD WINAPI ThreadFun(LPVOID lpParameter)
{
    DWORD cbWritten, cbRead;
    HANDLE hPipe_ = lpParameter;

    while (1) {
        char input[50], number[10];

        // чтение сообщения из канала
        if (ReadFile(hPipe_, input, 50, &cbRead, NULL))
        {

            int a = atoi(input);
            printf("received %s\n", input);

            sum_of_numbers = sum_of_numbers + a;
            char output[50] = "Sum = ";
            strcat_s(output, sizeof(output), (char*)sum_of_numbers);
            //strcat(output, itoa(sum_of_numbers, number, 10));

            WriteFile(hPipe_, output, 50, &cbWritten, NULL);
        }
        else {
            printf("Client disconnected, processing closed...");
            break;
        }
    }
    return 1;
}


int main(int args)
{

    BOOL fConnected;    // Флаг успешного создания канала
    HANDLE hPipe;  // Идентификатор канала Pipe
    LPCWSTR PipeName = L"\\\\.\\pipe\\$MyPipe$";
    DWORD cbRead, cbWritten;

    HANDLE hThread;
    DWORD threadID;

    printf("Waiting for connection....\n");
    // бесконечный цикл обработки ввода от пользователя
    while (1)
    {

        hPipe = CreateNamedPipe(PipeName, PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);

        if (hPipe == INVALID_HANDLE_VALUE)
        {
            printf("CreateNamedPipe failed.\n");
            return -1;
        }

        fConnected = ConnectNamedPipe(hPipe, NULL);

        if (fConnected)
        {
            printf("Client connected, creating a processing thread.\n");

            // Create a thread for this client. 
            hThread = CreateThread(NULL, 0, ThreadFun, (LPVOID)hPipe, 0, &threadID);

            if (hThread == NULL)
            {
                printf("CreateThread failed.\n");
                return -1;
            }
            else CloseHandle(hThread);
        }
        else
            CloseHandle(hPipe);
    }
    CloseHandle(hThread);
    _getch();
}


//DWORD WINAPI ThreadFun(LPVOID lpParameter)
//{
//    DWORD cbWritten, cbRead;
//    HANDLE hPipe_ = lpParameter;
//
//    while (1) {
//        char input[50], number[10];
//
//        // чтение сообщения из канала
//        if (ReadFile(hPipe_, input, 50, &cbRead, NULL))
//        {
//
//            int a = atoi(input);
//            printf("received %s\n", input);
//
//            sum_of_numbers = sum_of_numbers + a;
//            char output[50] = "Sum = ";
//            strcat(output, itoa(sum_of_numbers, number, 10));
//
//            WriteFile(hPipe_, output, 50, &cbWritten, NULL);
//        }
//        else {
//            printf("Client disconnected, processing closed...");
//            break;
//        }
//    }
//    return 1;
//}

//int main(int args)
//{
//    int sum_of_numbers = 0;
//
//    BOOL fConnected;    // Флаг успешного создания канала
//    HANDLE hPipe;  // Идентификатор канала Pipe
//    LPCWSTR PipeName = L"\\\\.\\pipe\\$MyPipe$";
//    DWORD cbRead, cbWritten;
//
//    HANDLE hThread;
//    DWORD threadID;
//
//    STARTUPINFO sti = { 0 };
//    PROCESS_INFORMATION pi = { 0 };
//    DWORD excode;
//
//    printf("Waiting for connection....\n");
//    // бесконечный цикл обработки ввода от пользователя
//    while (1)
//    {
//
//        hPipe = CreateNamedPipe(
//            PipeName, 
//            PIPE_ACCESS_DUPLEX,
//            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
//            PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);
//
//        if (hPipe == INVALID_HANDLE_VALUE)
//        {
//            printf("CreateNamedPipe failed.\n");
//            return -1;
//        }
//
//        fConnected = ConnectNamedPipe(hPipe, NULL);
//
//        if (fConnected)
//        {
//            printf("Client connected, process creation.\n");
//            
//            if (!CreateProcess(NULL, L"client.exe", NULL, NULL, TRUE, NULL, NULL, NULL, &sti, &pi)) {
//                printf("Unable to generate process");
//                return -1;
//            }
//
//            _getch;
//
//            GetExitCodeProcess(pi.hProcess, &excode);
//            printf("%s", excode);
//
//            if (excode != STILL_ACTIVE) {
//                printf("Done");
//            }
//            else {
//                printf("Process still running");
//            }
//            printf("PARENT PROCESS END");
//
//            //// Create a process for this client. 
//            //hThread = CreateThread(NULL, 0, ThreadFun, (LPVOID)hPipe, 0, &threadID);
//
//            //if (hThread == NULL)
//            //{
//            //    printf("CreateThread failed.\n");
//            //    return -1;
//            //}
//            //else CloseHandle(hThread);
//        }
//        else
//            CloseHandle(hPipe);
//    }
//    CloseHandle(hThread);
//    _getch();
//}


