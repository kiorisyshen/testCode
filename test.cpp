#include <iostream>
#include <bitset>
#include <string>
#include <map>

#include <chrono>


enum EXCEPT_Level
{
    EXCEPT_Debug = 0,
    EXCEPT_Warning = 1,
    EXCEPT_Error = 100
};

struct EXCEPT_Exception : public std::exception
{
  private:
    std::string _msg;
    long _lineNum;
    std::string _filePath;
    std::string _funcName;
    std::string _getExceptName(const EXCEPT_Level value) const
    {
        std::string resName;
#define GETNAME(p)    \
    case (p):         \
        resName = #p; \
        break;
        switch (value)
        {
            GETNAME(EXCEPT_Debug);
            GETNAME(EXCEPT_Warning);
            GETNAME(EXCEPT_Error);
        }
#undef GETNAME
        return resName;
    }

  public:
    EXCEPT_Level _lvl;
    explicit EXCEPT_Exception(const EXCEPT_Level &lvl, const std::string funcName, const long lineNum, const std::string filePath, const std::string &msg) : _lineNum(lineNum), _funcName(funcName), _filePath(filePath), _lvl(lvl), _msg(msg){};
    virtual const char *what() const throw()
    {
        return ("Exception level: " + _getExceptName(_lvl) + "\n"+ " In function: " + _funcName +"\n"+
        " At line: " + std::to_string(_lineNum) + " in file: " + _filePath + "\n Message: " + _msg).c_str();
    }
};

class moduleOption
{
  public:
    virtual void setID(int id) = 0;
    // explicit moduleOption(int id) : _id(id){}
};

class FDOption : public moduleOption
{
  public:
    int _id;
    FDOption(int id) : _id(id) {}
    void setID(int id) { _id = id; };
};

class FMOption : public moduleOption
{
  public:
    bool _isSet;
    int _id;
    FMOption(bool isSet) : _isSet(isSet) {}
    void setID(int id) { _id = id; };
};

template <class T_opt>
class module
{
  protected:
  public:
    int _id;
    explicit module(int id) : _id(id){}
    virtual void startCompute(T_opt &MOpt) final
    {
        compute(MOpt);
    }

    virtual bool compute(T_opt &MOpt) = 0;
};

class FD : public module<FDOption>
{

  public:
    // int _id;
    FD(int id) : module(id){}
    bool compute(FDOption &opt)
    {
        _id = opt._id;
        return true;
    }
};

class FM : public module<FMOption>
{
  public:
    bool _isSet;
    FM(int id) : module(id){}
    bool compute(FMOption &opt)
    {
        _isSet = opt._isSet;
        throw EXCEPT_Exception(EXCEPT_Error, __PRETTY_FUNCTION__ , __LINE__, __FILE__, "except in object function "+std::string(typeid(*this).name()));
        return true;
    }
};

void testFunction0() throw(std::exception){
    throw EXCEPT_Exception(EXCEPT_Error, __FUNCTION__ , __LINE__, __FILE__, "heiheihei");
};

void testFunction() throw(std::exception){
    testFunction0();
    // throw EXCEPT_Exception(EXCEPT_Error, __LINE__, __FILE__, "heiheihei");
};

typedef std::map<std::string, float> timeMap;

int main(int argc, char **argv)
{
    // std::cout << 128 * 32 << " bits: " << std::bitset<32>(128 * 32) << std::endl;
    // std::cout << (128 * 32 >> 3) << " bits: " << std::bitset<32>((128 * 32 >> 3)) << std::endl;
    // std::cout << (128 * 32 >> 3) + 3 << " bits: " << std::bitset<32>((128 * 32 >> 3) + 3) << std::endl;
    // std::cout << ~3 << " bits: " << std::bitset<32>(~3) << std::endl;
    // std::cout << (((128 * 32 >> 3) + 3) & ~3) << " bits: " << std::bitset<32>((((128 * 32 >> 3) + 3) & ~3)) << std::endl;

    
    
    auto PROF_exeStart = std::chrono::system_clock::now();
    try
    {
        testFunction();
        // throw EXCEPT_Exception(EXCEPT_Error, __LINE__, __FILE__, "hahaha");
    }
    catch (EXCEPT_Exception &e)
    {
        // std::cout << e.what() << std::endl;
    }
    auto PROF_exeEnd = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<float>(PROF_exeEnd-PROF_exeStart).count() << std::endl;

    // timeMap testMap;
    // std::string testKey = "test";
    // if (testMap.find(testKey) == testMap.end()){
    //     std::cout<< "no exist" << std::endl;
    //     testMap[testKey] = 0.2;
    // }else{
    //     std::cout<< "exist" << std::endl;
    //     testMap[testKey] += 1.3;
    // }
    // std::cout << testMap[testKey] << std::endl;

    // if (testMap.find(testKey) == testMap.end()){
    //     std::cout<< "no exist" << std::endl;
    //     testMap[testKey] = 0.2;
    // }else{
    //     std::cout<< "exist" << std::endl;
    //     testMap[testKey] += 1.3;
    // }
    // std::cout << testMap[testKey] << std::endl;

    // if(!testMap.insert(timeMap::value_type("test", 1.2)).second) std::cout<< "exists 1" << std::endl;
    // if(!testMap.insert(timeMap::value_type("test", 2.0)).second) std::cout<< "exists 2" << std::endl;
    // std::cout<< testMap["test"] << std::endl;

    // std::string test("hahahahah");
    // std::cout << sizeof(test) << std::endl;

    FD testFD(1);
    FDOption testFDO(5);
    // std::cout<< typeid(testFDO).name() << std::endl;
    testFD.startCompute(testFDO);

    // testFD.setOption(testFDO);

    FM testFM(3);
    FMOption testFMO(true);
    // std::cout<< typeid(testFMO).name() << std::endl;
    testFM.startCompute(testFMO);

    // testFM.setOption(testFMO);

    std::cout << testFD._id << " " << testFM._isSet << std::endl;

    return 0;
}