#include <iostream>
#include "VM.hpp"

int main() {
    VM vm;

    vm.AddInstruction(std::make_shared<INS_SetGlobalValue<int>>("threshold", 3));
    vm.AddInstruction(std::make_shared<INS_SetGlobalValue<std::string>>("msgForTrue", "Great True!"));
    vm.AddInstruction(std::make_shared<INS_SetGlobalValue<std::string>>("msgForFalse", "Sad False!"));

    vm.AddInstruction(std::make_shared<INS_Literal<int>>(1));
    vm.AddInstruction(std::make_shared<INS_Literal<int>>(2));
    vm.AddInstruction(std::make_shared<INS_Add>());
    vm.AddInstruction(std::make_shared<INS_GetValue>("threshold"));

    vm.AddInstruction(std::make_shared<INS_Compare<int>>(T_GreaterThan));
    vm.AddInstruction(std::make_shared<INS_Goto>("falseBlock"));

    vm.AddInstruction(std::make_shared<INS_GetValue>("msgForTrue"));
    vm.AddInstruction(std::make_shared<INS_Print<std::string>>());
    vm.AddInstruction(std::make_shared<INS_Goto>("EndIF"));

    vm.LabelHere("falseBlock");

    vm.AddInstruction(std::make_shared<INS_GetValue>("msgForFalse"));
    vm.AddInstruction(std::make_shared<INS_Print<std::string>>());

    vm.LabelHere("EndIF");

    vm.AddInstruction(std::make_shared<INS_GetValue>("threshold"));
    vm.AddInstruction(std::make_shared<INS_Print<int>>());

    vm.Run();
    return 0;
}