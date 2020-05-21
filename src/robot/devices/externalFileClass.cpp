#include "externalFileClass.hpp"

bool ExternalFile::SDCardIsInserted(){
  std::fstream m_file;
  m_file.open("/usd/.PROS_SD_Detection/SD_Card.txt", std::ios::app);
  m_file.close();

  m_file.open("/usd/.PROS_SD_Detection/SD_Card.txt", std::ios::in);
  if(m_file.is_open()){
      m_file.close();
      return true;
  }
  return false;
}

ExternalFile::ExternalFile(const std::string p_address, const bool p_erase){
    m_fileAddress = "/usd/" + p_address;
    m_file.open(m_fileAddress, std::ios::in);
    if(!p_erase && m_file.is_open()){
        m_file.close();
    }
    else{
        m_file.open(m_fileAddress, std::ios::out);
        m_file.close();
    }
}

bool ExternalFile::fileExist(){
  if(!SDCardIsInserted()){
    return false;
  }
  m_file.open(m_fileAddress, std::ios::in);
  if(m_file.is_open()){
      m_file.close();
      return true;
  }
  return false;
}

bool ExternalFile::varExist(const std::string p_varibleTitle){
    m_file.open(m_fileAddress, std::ios::in);
    std::string tempString;
    while(std::getline(m_file, tempString)){
        if(!tempString.find(p_varibleTitle)){
            m_file.close();
            return true;
        }
    }
    m_file.close();
    return false;
}
int ExternalFile::addLine(const std::string p_lineValue){
    m_file.open(m_fileAddress, std::ios::app);
    m_file << p_lineValue << std::endl;
    m_file.close();
    return 0;
}
int ExternalFile::updateLine(const std::string p_varibleTitle, const std::string p_lineValue){
    std::vector<std::string> stringVector;
    std::string tempString;
    m_file.open(m_fileAddress, std::ios::in);
    while(std::getline(m_file, tempString)){
        if(!tempString.find(p_varibleTitle)){
            tempString = p_lineValue;
            stringVector.push_back(tempString);
        }
        else{
            stringVector.push_back(tempString);
        }
    }
    m_file.close();

    m_file.open(m_fileAddress, std::ios::out);
    for(int x = 0; x < stringVector.size(); x++){
        m_file << stringVector.at(x) << std::endl;
    }
    m_file.close();
    return 0;
}
std::string ExternalFile::readLine(const std::string p_varibleTitle){
    m_file.open(m_fileAddress, std::ios::in);
    std::string tempString;
    while(std::getline(m_file, tempString)){
        if(!tempString.find(p_varibleTitle)){
            m_file.close();
            return tempString;
        }
    }
    m_file.close();
    return "Error";
}

int ExternalFile::storeVar(const std::string p_varibleTitle, const std::string p_lineValue){
    if(varExist(p_varibleTitle)){
        updateLine(p_varibleTitle, p_lineValue);
    }
    else{
        addLine(p_lineValue);
    }
    return 0;
}

int ExternalFile::storeInt(const std::string p_varibleName, const int p_varibleValue){
    std::string varibleTitle = p_varibleName + ":Int= ";
    std::string lineValue = varibleTitle + std::to_string(p_varibleValue);
    return storeVar(varibleTitle, lineValue);
}
int ExternalFile::readInt(const std::string varibleName){
    std::string varibleTitle = varibleName + ":Int= ";
    std::string lineValue = readLine(varibleTitle);
    if(lineValue == "Error")
      return -1;
    return std::stoi(lineValue.substr(varibleTitle.size()));
}

int ExternalFile::storeDouble(const std::string p_varibleName, const double p_varibleValue){
    std::string varibleTitle = p_varibleName + ":Double= ";
    std::string lineValue = varibleTitle + std::to_string(p_varibleValue);
    return storeVar(varibleTitle, lineValue);
}
double ExternalFile::readDouble(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":Double= ";
    std::string lineValue = readLine(varibleTitle);
    if(lineValue == "Error")
      return -1.1;
    return std::stod(lineValue.substr(varibleTitle.size()));
}

int ExternalFile::storeChar(const std::string p_varibleName, const char p_varibleValue){
    std::string varibleTitle = p_varibleName + ":Char= ";
    std::string lineValue = varibleTitle + p_varibleValue;
    return storeVar(varibleTitle, lineValue);
}
char ExternalFile::readChar(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":Char= ";
    std::string lineValue = readLine(varibleTitle);
    if(lineValue == "Error")
      return 'E';
    return lineValue.at(varibleTitle.size());
}

int ExternalFile::storeBool(const std::string p_varibleName, const bool p_varibleValue){
    std::string varibleTitle = p_varibleName + ":Bool= ";
    std::string lineValue = varibleTitle + std::to_string(p_varibleValue);
    return storeVar(varibleTitle, lineValue);
}
bool ExternalFile::readBool(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":Bool= ";
    std::string lineValue = readLine(varibleTitle);
    if(lineValue == "Error")
      return false;
    return std::stoi(lineValue.substr(varibleTitle.size()));
}

int ExternalFile::storeString(const std::string p_varibleName, const std::string p_varibleValue){
    std::string varibleTitle = p_varibleName + ":String= ";
    std::string lineValue = varibleTitle + p_varibleValue;
    return storeVar(varibleTitle, lineValue);
}
std::string ExternalFile::readString(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":String= ";
    std::string lineValue = readLine(varibleTitle);
    if(lineValue == "Error")
      return "Error";
    return lineValue.substr(varibleTitle.size());
}

// Array of Varibles
int ExternalFile::storeIntArray(const std::string p_varibleName,const std::vector<int> p_varibleValue){
    std::string varibleTitle = p_varibleName + ":IntArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<p_varibleValue.size()-1; x++){
        lineValue += std::to_string(p_varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(p_varibleValue.at(p_varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<int> ExternalFile::readIntArray(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":IntArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<int> tempVec;
    if(lineValue == "Error"){
      tempVec.push_back(-1);
      return tempVec;
    }
    int position = (int)varibleTitle.size();
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(std::stoi(tempString.substr(0, tempString.find("~"))));
            x = false;
        }
        else{
            tempVec.push_back(std::stoi(tempString.substr(0,tempString.find(","))));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::storeDoubleArray(const std::string p_varibleName, const std::vector<double> p_varibleValue){
    std::string varibleTitle = p_varibleName + ":DoubleArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<p_varibleValue.size()-1; x++){
        lineValue += std::to_string(p_varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(p_varibleValue.at(p_varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<double> ExternalFile::readDoubleArray(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":DoubleArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<double> tempVec;
    if(lineValue == "Error"){
      tempVec.push_back(-1.1);
      return tempVec;
    }
    int position = (int)varibleTitle.size();
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(std::stod(tempString.substr(0, tempString.find("~"))));
            x = false;
        }
        else{
          tempVec.push_back(std::stod(tempString.substr(0,tempString.find(","))));
          position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::storeCharArray(const std::string p_varibleName, const std::vector<char> p_varibleValue){
    std::string varibleTitle = p_varibleName + ":CharArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<p_varibleValue.size()-1; x++){
        lineValue += std::string(1, p_varibleValue.at(x))+ ", ";
    }
    lineValue += std::string(1, p_varibleValue.at(p_varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<char> ExternalFile::readCharArray(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":CharArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<char> tempVec;
    if(lineValue == "Error"){
      tempVec.push_back('E');
      tempVec.push_back('R');
      return tempVec;
    }
    int position = (int)varibleTitle.size();
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(tempString.at(tempString.find("~")-1));
            x = false;
        }
        else{
            tempVec.push_back(tempString.at(tempString.find(",")-1));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::storeBoolArray(const std::string p_varibleName, const std::vector<bool> p_varibleValue){
    std::string varibleTitle = p_varibleName + ":BoolArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<p_varibleValue.size()-1; x++){
        lineValue += std::to_string(p_varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(p_varibleValue.at(p_varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<bool> ExternalFile::readBoolArray(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":BoolArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<bool> tempVec;
    if(lineValue == "Error"){
      tempVec.push_back(false);
      return tempVec;
    }
    int position = (int)varibleTitle.size();
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(std::stoi(tempString.substr(0, tempString.find("~"))));
            x = false;
        }
        else{
            tempVec.push_back(std::stoi(tempString.substr(0,tempString.find(","))));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::storeStringArray(const std::string p_varibleName, const std::vector<std::string> p_varibleValue){
    std::string varibleTitle = p_varibleName + ":StringArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<p_varibleValue.size()-1; x++){
        lineValue += p_varibleValue.at(x)+ ", ";
    }
    lineValue += p_varibleValue.at(p_varibleValue.size()-1)+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<std::string> ExternalFile::readStringArray(const std::string p_varibleName){
    std::string varibleTitle = p_varibleName + ":StringArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<std::string> tempVec;
    if(lineValue == "Error"){
      tempVec.push_back("Error");
      return tempVec;
    }
    int position = (int)varibleTitle.size();
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(tempString.substr(0, tempString.find("~")));
            x = false;
        }
        else{
            tempVec.push_back(tempString.substr(0,tempString.find(",")));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}
