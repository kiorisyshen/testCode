#include <typeinfo>
#include <string>
#include <iostream>
#include <vector>

class TESTFUNC
{
    protected:
        const std::string _inDir;
        const std::string _name;

    public:
        TESTFUNC(std::string name, std::string inDir) :
        _name(name),
        _inDir(inDir)
        {};

        virtual bool RUN() = 0;
};

class testF1 : public TESTFUNC
{
    public:
        testF1(std::string inDir) : TESTFUNC(typeid(this).name(), inDir)
        {}
        bool RUN() {
            std::cout << _name << " " << _inDir << std::endl;
            return true;
        }
};

class testF2 : public TESTFUNC
{
    public:
        testF2(std::string inDir) : TESTFUNC(typeid(this).name(), inDir)
        {}
        bool RUN() {
            std::cout << _name << " " << _inDir << std::endl;
            return true;
        }
};

void RUN_test(){
    testF1 a("/home");
    testF2 b("/home/b");

    std::vector<TESTFUNC*> testFuncList;
    testFuncList.emplace_back((TESTFUNC*)&a);
    testFuncList.emplace_back((TESTFUNC*)&b);
    
    for (int i=0; i<testFuncList.size(); ++i) {
        testFuncList[i]->RUN();
    }
}