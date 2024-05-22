#include <windows.h>
#include <fstream>
#include <iostream>
#include <ctime>

void log(const char file[], int line, const char* text, ...)
{
    static char tmp_string[256];
    static char tmp_string2[256];
    static va_list ap;
    static bool is_first_call = true; //flag to track if it's the first call

    //Create a string from the last occurrence of the path separator character
    const char* filename = strrchr(file, '\\') + 1;

    //Construct the string from variable arguments
    va_start(ap, text);
    vsprintf_s(tmp_string, 256, text, ap);
    va_end(ap);

    //Construct the log message
    sprintf_s(tmp_string2, 256, "%s(%d): %s\n", filename, line, tmp_string);

    //Option 1: print message in console (C), printf(tmp_string2);
    //Option 2: print message in console (C++), std::cout << tmp_string2;
    //Option 3: print message in Visual Studio output tab, OutputDebugString((LPCWSTR)tmp_string2);
    //Option 4: use a log file

    //Open the log file
    std::ofstream logfile;
    if (is_first_call)
    {
        //Open in truncation mode to overwrite contents on first call
        logfile.open("log.txt", std::ios_base::trunc);
        is_first_call = false; // Update flag for subsequent calls

        time_t rawtime;
        std::tm timeinfo;
        char buffer[128];

        std::time(&rawtime);
        localtime_s(&timeinfo, &rawtime);

        std::strftime(buffer, sizeof(buffer), "Project executed on %d-%m-%Y at %H:%M:%S.", &timeinfo);
        logfile << buffer << std::endl;
    }
    else
    {
        //Open in append mode for subsequent calls
        logfile.open("log.txt", std::ios_base::app);
    }
    if (!logfile.is_open())
    {
        //Failed to open the file
        std::cerr << "Failed to open log file!" << std::endl;
        return;
    }

    //Write the log message to the log file
    logfile << tmp_string2;

    //Close the log file
    logfile.close();
}