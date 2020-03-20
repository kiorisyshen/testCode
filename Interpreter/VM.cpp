#include "VM.hpp"
#include "Driver.hpp"

// -----------------------
// VM
// -----------------------

void VM::Run() {
    for (m_state.m_currIdx = 0; m_state.m_currIdx < m_insList.size(); ++m_state.m_currIdx) {
        if (!m_insList[m_state.m_currIdx]->execute(m_state)) {
            std::cout << "Terminate with error!" << std::endl;
            break;
        }
    }

    m_insList.clear();
    m_state.reset();
}

void VM::AddInstruction(const std::shared_ptr<Instruction> &ins) {
    m_insList.push_back(ins);
}

void VM::LabelHere(const std::string &label) {
    if (m_state.m_labelMap.find(label) != m_state.m_labelMap.end()) {
        std::cout << "Duplicate label: " << label << ". Will override it now." << std::endl;
    }
    m_state.m_labelMap[label] = m_insList.size();
}

// -----------------------
// Instructions
// -----------------------

bool INS_GetValue::execute(VM_State &state) {
    if (!Instruction::execute(state)) {
        return false;
    }

    // TODO: Search local context first

    if (state.m_globalContext.find(m_name) == state.m_globalContext.end()) {
        std::cout << "Can't get value with name: " << m_name << std::endl;
        return false;
    }
    state.m_valueStack.push(state.m_globalContext[m_name]);
    return true;
}

bool INS_Add::execute(VM_State &state) {
    if (!Instruction::execute(state)) {
        return false;
    }

    {  // check if int
        auto v1 = std::dynamic_pointer_cast<TypedValue<int>>(m_args[0]);
        auto v2 = std::dynamic_pointer_cast<TypedValue<int>>(m_args[1]);

        if (v1 && v2) {
            state.m_valueStack.push(std::make_shared<TypedValue<int>>(Driver::Add(v1->m_data, v2->m_data)));
            return true;
        }
    }

    {  // check if string
        auto v1 = std::dynamic_pointer_cast<TypedValue<std::string>>(m_args[0]);
        auto v2 = std::dynamic_pointer_cast<TypedValue<std::string>>(m_args[1]);

        if (v1 && v2) {
            state.m_valueStack.push(std::make_shared<TypedValue<std::string>>(Driver::Add(v1->m_data, v2->m_data)));
            return true;
        } else {
            if (!v1 || !v2) {
                std::cout << "Can't cast type " << m_args[0]->type.name() << " or " << m_args[1]->type.name() << " to "
                          << typeid(int).name() << " or " << typeid(std::string).name() << std::endl;
                return false;
            }
            return false;
        }
    }

    return true;
}

bool INS_Multiply::execute(VM_State &state) {
    if (!Instruction::execute(state)) {
        return false;
    }

    {  // check if int
        auto v1 = std::dynamic_pointer_cast<TypedValue<int>>(m_args[0]);
        auto v2 = std::dynamic_pointer_cast<TypedValue<int>>(m_args[1]);

        if (!v1 || !v2) {
            std::cout << "Can't cast type " << m_args[0]->type.name() << " or " << m_args[1]->type.name() << " to " << typeid(int).name() << std::endl;
            return false;
        }

        state.m_valueStack.push(std::make_shared<TypedValue<int>>(Driver::Multiply(v1->m_data, v2->m_data)));
        return true;
    }

    return true;
}

bool INS_Goto::execute(VM_State &state) {
    if (!Instruction::execute(state)) {
        return false;
    }

    if (state.m_labelMap.find(m_label) == state.m_labelMap.end()) {
        std::cout << "Can't find label: " << m_label << std::endl;
        return false;
    }

    state.m_currIdx = state.m_labelMap[m_label] - 1;
    return true;
}