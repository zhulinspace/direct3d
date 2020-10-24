#include "App.h"
#include"WindowMessageMap.h"
#include<sstream>

//entry point
int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInst,
    LPSTR lpszCmdLine, int nCmdShow)
{

   
    try 
    {

        return APP{}.Go();
    }
    catch (const ChiliException &e)
    {
        MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const std::exception &e)
    {
        MessageBox(nullptr, e.what(), "standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, "No detail available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    return -1;
 
    
    
}