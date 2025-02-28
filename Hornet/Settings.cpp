#include "Settings.h"
#include "ErrorLogger.h"
#include <fstream>
#include <sstream>

Settings Settings::instance;

Settings::Settings()
{
    m_filename = "settings.dat";
}

Settings::~Settings()
{
    Clear();
}

void Settings::ProcessLine(std::string& line)
{
    std::stringstream lineString(line);

    std::string name;
    lineString >> name;
    if (name.size()==0) return;
    std::string value;
    lineString>> value;
    m_valuesMap[name] = value;
    lineString.clear();
}

void Settings::Clear()
{
    m_valuesMap.clear();
}

void Settings::SetValue(std::string name, std::string value)
{
    m_valuesMap[name] = value;
}

void Settings::SetValue(std::string name, double value)
{
    m_valuesMap[name] = std::to_string(value);
}

void Settings::Load()
{
    std::ifstream filedata;
    filedata.open(m_filename);

    while (filedata)
    {
        std::string line;
        std::getline(filedata, line);
        ProcessLine(line);
    }
    filedata.close();

}

void Settings::Save()
{
    std::ofstream filedata;
    filedata.open(m_filename);

    for (auto& entry : m_valuesMap)
    {
        filedata << entry.first << "  \t" << entry.second << "\n";
    }

    filedata.close();
}

std::string Settings::GetStringValue(const std::string& name)
{
    auto it = m_valuesMap.find(name);
    if (it == m_valuesMap.end())
    {
        ErrorLogger::Write(std::string("Settings value not found: " + name));
        return "";
    }
    return it->second;
}



double Settings::GetNumberValue(const std::string& name)
{
    std::string value = GetStringValue(name);
    try
    {
        double val = std::stod(value);
        return val;
    }
    catch (std::invalid_argument)
    {
        ErrorLogger::Write(std::string("Bad number format in setting: " + name));
        return 0;
    }
}

