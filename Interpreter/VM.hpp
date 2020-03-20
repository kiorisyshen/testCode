#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Value {
   public:
    const std::type_info &type;

    Value(const std::type_info &t)
        : type(t) {
    }
    virtual ~Value() {
    }
};

template <typename T>
class TypedValue : public Value {
   public:
    T m_data;

    TypedValue(const T &data)
        : Value(typeid(T)), m_data(data) {
    }

    TypedValue(T &&data)
        : Value(typeid(T)), m_data(std::move(data)) {
    }
};

typedef std::unordered_map<std::string, std::shared_ptr<Value>> Context;

class VM_State {
   public:
    Context m_globalContext;
    std::stack<std::shared_ptr<Context>> m_localContextStack;

    int m_currIdx;
    std::stack<std::shared_ptr<Value>> m_valueStack;

    std::unordered_map<std::string, int> m_labelMap;

    void reset() {
        m_currIdx = 0;
        m_labelMap.clear();

        while (!m_localContextStack.empty()) {
            m_localContextStack.pop();
        }

        while (!m_valueStack.empty()) {
            m_valueStack.pop();
        }
    }
};

class Instruction {
   public:
    virtual bool execute(VM_State &state) {
        if (state.m_valueStack.size() < m_numNeedArgs) {
            std::cout << "Internal Error! No enough value in stack." << std::endl;
            return false;
        }

        for (int i = 0; i < m_numNeedArgs; ++i) {
            m_args.push_front(state.m_valueStack.top());
            state.m_valueStack.pop();
        }

        return true;
    }

   protected:
    int m_numNeedArgs;
    std::deque<std::shared_ptr<Value>> m_args;
};

// -----------------------
// VM
// -----------------------

class VM {
   public:
    void Run();
    void AddInstruction(const std::shared_ptr<Instruction> &ins);
    void LabelHere(const std::string &label);

   public:
    VM_State m_state;

    std::vector<std::shared_ptr<Instruction>> m_insList;
};

// -----------------------
// Instructions
// -----------------------

template <typename T>
class INS_Literal : public Instruction {
   public:
    INS_Literal(const T &p_value)
        : m_value(p_value) {
        m_numNeedArgs = 0;
    }
    INS_Literal(T &&p_value)
        : m_value(std::move(p_value)) {
        m_numNeedArgs = 0;
    }

    virtual bool execute(VM_State &state) final {
        if (!Instruction::execute(state)) {
            return false;
        }
        state.m_valueStack.push(std::make_shared<TypedValue<T>>(m_value));
        return true;
    }

   private:
    T m_value;
};

template <typename T>
class INS_SetGlobalValue : public Instruction {
   public:
    INS_SetGlobalValue(const std::string &name, const T &p_value)
        : m_name(name), m_value(p_value) {
        m_numNeedArgs = 0;
    }
    INS_SetGlobalValue(const std::string &name, T &&p_value)
        : m_name(name), m_value(std::move(p_value)) {
        m_numNeedArgs = 0;
    }

    virtual bool execute(VM_State &state) final {
        if (!Instruction::execute(state)) {
            return false;
        }
        if (state.m_globalContext.find(m_name) != state.m_globalContext.end()) {
            std::cout << "Warning! Overriding value: " << m_name << std::endl;
        }

        state.m_globalContext[m_name] = std::make_shared<TypedValue<T>>(m_value);
        return true;
    }

   private:
    std::string m_name;
    T m_value;
};

template <typename T>
class INS_SetLocalValue : public Instruction {
   public:
    INS_SetLocalValue(const std::string &name, const T &p_value)
        : m_name(name), m_value(p_value) {
        m_numNeedArgs = 0;
    }
    INS_SetLocalValue(const std::string &name, T &&p_value)
        : m_name(name), m_value(std::move(p_value)) {
        m_numNeedArgs = 0;
    }

    virtual bool execute(VM_State &state) final {
        if (!Instruction::execute(state)) {
            return false;
        }
        // TODO: Implement local context
        return true;
    }

   private:
    std::string m_name;
    T m_value;
};

class INS_GetValue : public Instruction {
   public:
    INS_GetValue(const std::string &name)
        : m_name(name) {
        m_numNeedArgs = 0;
    }

    virtual bool execute(VM_State &state) final;

   private:
    std::string m_name;
};

template <typename T>
class INS_Print : public Instruction {
   public:
    INS_Print() {
        m_numNeedArgs = 1;
    }

    virtual bool execute(VM_State &state) final {
        if (!Instruction::execute(state)) {
            return false;
        }

        auto v1 = std::dynamic_pointer_cast<TypedValue<T>>(m_args[0]);
        if (v1) {
            std::cout << v1->m_data << std::endl;
        } else {
            std::cout << "Can't print this type (" << m_args[0]->type.name() << ") as type (" << typeid(T).name() << ")" << std::endl;
            return false;
        }

        return true;
    }
};

class INS_Add : public Instruction {
   public:
    INS_Add() {
        m_numNeedArgs = 2;
    }

    virtual bool execute(VM_State &state) final;
};

class INS_Multiply : public Instruction {
   public:
    INS_Multiply() {
        m_numNeedArgs = 2;
    }

    virtual bool execute(VM_State &state) final;
};

enum Type_Compare {
    T_Equal,
    T_GreaterThan,
    T_LessThan,
    T_GreaterEqualTo,
    T_LessEqualTo
};

template <typename T>
class INS_Compare : public Instruction {
   public:
    INS_Compare(const Type_Compare &typeCompare)
        : m_typeCompare(typeCompare) {
        m_numNeedArgs = 2;
    }

    virtual bool execute(VM_State &state) final {
        if (!Instruction::execute(state)) {
            return false;
        }

        auto v1 = std::dynamic_pointer_cast<TypedValue<T>>(m_args[0]);
        auto v2 = std::dynamic_pointer_cast<TypedValue<T>>(m_args[1]);

        if (v1 && v2) {
            // Skip goto if true (goto is must followed by this instruction)
            switch (m_typeCompare) {
                case T_Equal:
                    if (v1 == v2) {
                        ++state.m_currIdx;
                    }
                    break;

                case T_GreaterThan:
                    if (v1->m_data > v2->m_data) {
                        ++state.m_currIdx;
                    }
                    break;

                case T_LessThan:
                    if (v1->m_data < v2->m_data) {
                        ++state.m_currIdx;
                    }
                    break;

                case T_GreaterEqualTo:
                    if (v1->m_data >= v2->m_data) {
                        ++state.m_currIdx;
                    }
                    break;

                case T_LessEqualTo:
                    if (v1->m_data <= v2->m_data) {
                        ++state.m_currIdx;
                    }
                    break;

                default:
                    std::cout << "Unsupport compare type: " << m_typeCompare << std::endl;
                    return false;
                    break;
            }

        } else {
            std::cout << "Can't cast type " << m_args[0]->type.name() << " or " << m_args[1]->type.name() << " to "
                      << typeid(T).name() << std::endl;
            return false;
        }

        return true;
    }

   private:
    Type_Compare m_typeCompare;
};

class INS_Goto : public Instruction {
   public:
    INS_Goto(const std::string &label)
        : m_label(label) {
        m_numNeedArgs = 0;
    }

    virtual bool execute(VM_State &state) final;

   private:
    std::string m_label;
};
