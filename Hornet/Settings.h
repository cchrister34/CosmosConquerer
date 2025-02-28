#pragma once
#include <string>
#include <map>

class Settings
{
private:
    std::string m_filename;
    std::map<std::string, std::string> m_valuesMap;

    Settings(const Settings&) = delete;
    Settings();
    ~Settings();

    void ProcessLine(std::string& line);
public:
    static Settings instance;

    // Deletes all settings
    void Clear();

    void SetValue(std::string name, std::string value);
    void SetValue(std::string name, double value);
    void Load();
    void Save();
    std::string GetStringValue(const std::string& name);
    double GetNumberValue(const std::string& name);
};

