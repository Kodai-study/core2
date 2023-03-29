#include "header.h"
#include <LinkedList.h>
void printDirectory(File dir, int numTabs)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            dir.rewindDirectory();
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Llcd.print('\t');
        }
        Llcd.print(entry.name());
        if (entry.isDirectory())
        {
            Llcd.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            Llcd.println("\t\t");
        }
    }
}

bool split(char *str, char *buff)
{
    String input = String(str);
    int first = 0;
    int i = 0;
    int last = input.indexOf(',');
    while (first < input.length())
    {
        String subStr = input.substring(first, last - first);
        buff[i++] = atoi(subStr.c_str());
        first = last + 1;
        last = input.indexOf(',', first);
        if (last == std::string::npos)
        {
            last = input.length();
        }
    }
    return false;
}

bool sdCheck(const char *path, LinkedList<String> list)
{
    File fp = SD.open(path, "rw", false);
    if (!fp)
    {
        Llcd.println("NO SD!!");
        return false;
    }
    while (fp.available())
    {
        list.add(fp.readStringUntil('\n'));
    }
    return true;
}

String getCSVColum(String lineData, int index)
{
    static const char kugiri = ',';
    int firstIndex = 0;
    int last = lineData.indexOf(kugiri);
    if (index == 0)
    {
        return lineData.substring(last);
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            firstIndex = last + 1;
            last = lineData.indexOf(kugiri);
        }
        return lineData.substring(firstIndex, last);
    }
}