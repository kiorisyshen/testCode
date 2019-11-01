#include <vector>
#include <iostream>

enum ImgType {
    a = 0,
    b,
    c
};

class IBase {
    protected:
    std::vector<ImgType> mTypes;
    public:
    IBase(std::vector<ImgType> types):
    mTypes(types)
    {}
    virtual void cal() = 0;
};

class Derived : public IBase{
    public:
    Derived() :
    IBase({b,c})
    {}
    virtual void cal(){std::cout << "Derived cal()" << std::endl;}
};

class Proc {
    public:
    std::vector<std::shared_ptr<IBase> > mList;
    Proc(std::vector<std::shared_ptr<IBase> > cList={std::dynamic_pointer_cast<IBase>(std::make_shared<Derived>())}) :
    mList(cList)
    {}
};

void RUN_test()
{
    Proc testProc;
    for (int i=0; i<testProc.mList.size(); ++i) {
        testProc.mList[i]->cal();
    }
}