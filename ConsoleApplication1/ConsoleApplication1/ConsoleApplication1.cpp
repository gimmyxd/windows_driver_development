// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

#pragma comment(lib, "advapi32.lib")


int main(int argc, char** argv)
{   
    TCHAR szSvcName[80];
    SC_HANDLE schSCManager;
    SC_HANDLE schService;
    SERVICE_DESCRIPTION sd;
    LPTSTR szDesc = LPTSTR("This is a test description");

    StringCchCopy(szSvcName, 80, TEXT("SampleService"));

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return 1;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,            // SCM database 
        szSvcName,               // name of service 
        SERVICE_CHANGE_CONFIG);  // need change config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        
        return 1;
    }

    // Change the service description.
    SERVICE_LAUNCH_PROTECTED_INFO Info;

    Info.dwLaunchProtected = atoi(argv[1]);
    printf("%d\n", Info.dwLaunchProtected);
    printf("%d\n", SERVICE_LAUNCH_PROTECTED_ANTIMALWARE_LIGHT);
    sd.lpDescription = szDesc;

    if (!ChangeServiceConfig2(
        schService,                 // handle to service
        SERVICE_CONFIG_LAUNCH_PROTECTED, // change: description
        &Info))                      // new description
    {
        printf("ChangeServiceConfig2 failed\n");
    }
    else printf("Service description updated successfully.\n");

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
    printf("Done \n");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
