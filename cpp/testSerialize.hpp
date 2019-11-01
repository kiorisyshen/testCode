#include <string>
#include <iostream>

/**
 Serialize a std::string "str" to the address position "addr"
 and return the size of all serialized content.

 @param addr Address where to serialize
 @param size Total size (# of bytes) of serialized content
 @param str The std::string need to be serialized
 @return GeoMap error code
 */
bool serializeStdString(unsigned char* const addr, uint32_t &size, const std::string &str){
    uint32_t offset = 0;
    try {
        if (addr) *(uint32_t*)(addr + offset) = (uint32_t)str.size();
        offset += sizeof(uint32_t);
        
        // if (addr) strcpy((char*)(addr + offset), str.c_str());
        if (addr) str.copy((char*)(addr+offset), str.size());
        offset += (uint32_t)str.size();
    } catch (...) { // all exceptions are considered as error
        return false;
    }
    size = offset;
    return true;
}

/**
 Restore a std::string "str" from the address position "addr"
 and return the size of all restored content.

 @param addr Address where the data stored
 @param size Total size (# of bytes) of restored content
 @param str Restored std::string
 @return GeoMap error code
 */
bool restoreStdString(const unsigned char* const addr, uint32_t &size, std::string &str){
    if (addr==NULL) return false;
    uint32_t offset = 0;
    try {
        uint32_t sizeStr = *(uint32_t*)(addr + offset);
        offset += sizeof(uint32_t);

        str.assign((char*)(addr + offset), sizeStr);
        offset += sizeStr;
    } catch (...) { // all exceptions are considered as error
        return false;
    }
    size = offset;
    return true;
}


template<typename T>
bool serializeFixSizeType(unsigned char *const addr, const uint32_t offset, T &&inValue, uint32_t &offsetNew)
{
    offsetNew = offset;
    if (addr)
    {
        try {
            *(T *)(addr + offset) = (T)inValue;
            offsetNew += sizeof(T);
        } catch (...) {
            // all exceptions are considered as error
            return false;
        }
    }
    
    return true;
}

template<typename T>
bool restoreFixSizeType(const unsigned char *const addr, const uint32_t offset, T &&outValue, uint32_t &offsetNew)
{
    if (addr == NULL)
    {
        return false;
    }
    offsetNew = offset;
    try
    {
        outValue = *(T *)(addr + offset);
        offsetNew += sizeof(T);
    }
    catch (...)
    {// all exceptions are considered as error
        return false;
    }
    
    return true;
}


void RUN_test(){
    uint32_t testFixSizeType = 17;
    uint32_t aa = 21;

    unsigned char* const addr = new unsigned char [10];
    uint32_t offset = 0;
    serializeFixSizeType(addr, 0, testFixSizeType, offset);
    serializeFixSizeType(addr, offset, aa, offset);
    std::cout << offset << " " << testFixSizeType << " " << aa << std::endl << addr << std::endl << std::endl;

    uint32_t restored_testFixSizeType = 0;
    uint32_t bb = 0;
    restoreFixSizeType(addr, 0, restored_testFixSizeType, offset);
    restoreFixSizeType(addr, offset, bb, offset);
    std::cout << offset << " " << restored_testFixSizeType << " " << bb << std::endl << addr << std::endl << std::endl;

    // unsigned char* const addr = new unsigned char [30];
    // std::string str1(u8"ハロー・ワールド");
    // assert(24 == str1.size()); // 24 code units in UTF-8
    // std::string str2 = "test2";

    // uint32_t size_1 = 0;
    // uint32_t size_2 = 0;
    // serializeStdString(addr, size_1, str1);
    // serializeStdString(addr+size_1, size_2, str2);
    // std::cout << size_1 << " " << str1 << std::endl;
    // std::cout << size_2 << " " << str2 << std::endl;

    // std::string str_a;
    // std::string str_b;
    // uint32_t size_a = 0;
    // uint32_t size_b = 0;
    // restoreStdString(addr, size_a, str_a);
    // restoreStdString(addr+size_a, size_b, str_b);
    // std::cout << size_a << " " << str_a << std::endl;
    // std::cout << size_b << " " << str_b << std::endl;

    // delete[] addr;

    // std::string c(u8"ハロー・ワールド"); // 8 code points
    // assert(24 == c.size()); // 24 code units in UTF-8
    // std::string c("test1");
    // std::cout << c << std::endl;

    // unsigned char* const addr = new unsigned char[c.size()];
    // c.copy((char*)addr, c.size());
    // std::cout << addr << std::endl;

    // std::string d = "";
    // d.assign((char*)addr, c.size());
    // std::cout << d << std::endl;

    // delete[] addr;

    // const char* const t = "hhhh";
    // std::string a = t;
    // std::cout << a << std::endl;

}