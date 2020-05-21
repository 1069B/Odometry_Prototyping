#include "robot/varibleDecleration.hpp"

#ifndef EXTERNALFILECLASS_H
#define EXTERNALFILECLASS_H

class ExternalFile{
private:
    std::fstream m_file;
    std::string m_fileAddress;

public:
    static bool SDCardIsInserted();

    ExternalFile(const std::string p_address, const bool p_erase = false);

    int addLine(const std::string p_lineValue);
    int updateLine(const std::string p_varibleTitle, const std::string p_lineValue);
    int storeVar(const std::string p_varibleTitle, const std::string p_lineValue);
    std::string readLine(const std::string p_varibleTitle);

    bool fileExist();
    bool varExist(const std::string p_varibleTitle);

    //Single Varibles
    int storeInt(const std::string p_varibleName,const int p_varibleValue);
    int readInt(const std::string p_varibleName);

    int storeDouble(const std::string p_varibleName, const double p_varibleValue);
    double readDouble(const std::string p_varibleName);

    int storeChar(const std::string p_varibleName, const char p_varibleValue);
    char readChar(const std::string p_varibleName);

    int storeBool(const std::string p_varibleName, const bool p_varibleValue);
    bool readBool(const std::string p_varibleName);

    int storeString(const std::string p_varibleName, const std::string p_varibleValue);
    std::string readString(const std::string p_varibleName);

    // Array of Varibles
    int storeIntArray(const std::string p_varibleName,const std::vector<int> p_varibleValue);
    std::vector<int> readIntArray(const std::string p_varibleName);

    int storeDoubleArray(const std::string p_varibleName, const std::vector<double> p_varibleValue);
    std::vector<double> readDoubleArray(const std::string p_varibleName);

    int storeCharArray(const std::string p_varibleName, const std::vector<char> p_varibleValue);
    std::vector<char> readCharArray(const std::string p_varibleName);

    int storeBoolArray(const std::string p_varibleName, const std::vector<bool> p_varibleValue);
    std::vector<bool> readBoolArray(const std::string p_varibleName);

    int storeStringArray(const std::string p_varibleName, const std::vector<std::string> p_varibleValue);
    std::vector<std::string> readStringArray(const std::string p_varibleName);

    int defineGUI(GraphicalInterface& p_gui, std::string p_returnScreen);
};

#endif // EXTERNALFILECLASS_H
