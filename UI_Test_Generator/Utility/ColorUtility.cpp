#include <iostream>

#include "ColorUtility.hpp"



bool getColor(std::vector<int> &col, const std::wstring& tmp)
{
    col.clear();
    col.push_back(0);
    for (int i=0;i<tmp.size();i++)
    {
        if (tmp[i]>=L'0' && tmp[i]<=L'9')
            col[col.size()-1] = col[col.size()-1] * 10 + int(tmp[i] - '0');
        else if (tmp[i] == L' ' && tmp[i-1]!=L' ')
            col.push_back(0);
        else if (tmp[i] != L' ')
        {
            std::wcout<<L"Error on line '"<<tmp<<L"': invalid character"<<std::endl;
            return false;
        }
    }

    if (col.size()<3)
    {
        std::wcout<<L"Error on line '"<<tmp<<L"': not enough colors"<<std::endl;
        return false;
    }

    bool hasError = false;
    for (int i=0;i<col.size();i++)
        if (col[i]<0 || col[i]>255)
        {
            std::wcout<<L"Error on line'"<<tmp<<L"': invalid color"<<std::endl;
            hasError = true;
        }
    if (hasError)
        return false;
    return true;
}
