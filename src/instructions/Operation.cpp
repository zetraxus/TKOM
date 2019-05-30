//
// Created by adam on 06.05.19.
//

#include "Operation.h"
#include "../interpreter/Multiplication.h"
#include "../interpreter/Division.h"


Operation::Operation() {}

void Operation::addOperation(std::unique_ptr<Operation> next) {
    operations.emplace_back(std::move(next));
}

void Operation::addOperators(Operation::Operator op) {
    operators.emplace_back(op);
}

void Operation::setVariable(std::unique_ptr<Variable> variable) {
    Operation::variable = std::move(variable);
}

std::pair<int, optToken> Operation::calculate(SymbolMap& symbols) {
    std::pair<int, optToken> result;
    if(!operations.empty()){
        for(auto i = 0; i < operations.size(); ++i){
            if(!i)
                result = operations[i]->calculate(symbols);
            else
                result = calculate(result, operations[i]->calculate (symbols), operators[i-1]); // chech if operators[i] is correct
//            std::cout << "&" << result.first << "&" << result.second.value() << "&" << std::endl;
        }
    } else{
        if(variable->getType() == Variable::Id){
            auto name = variable->getName();
            auto pos = variable->getPositionInContainer();
            //TODO
        } else {
            auto value = variable->getValue();
            auto type = value->getType();
            auto val = value->getValue();
            if(type == Token::Value)
                return std::make_pair(stoi(val), optToken{Token::Value});
            else
                return std::make_pair(stoi(val), optToken(type));
        }
    }

    return result;
}

void Operation::setEmpty(bool empty) {
    Operation::empty = empty;
}

bool Operation::isEmpty() const {
    return empty;
}

bool Operation::opEmpty(size_t id) const {
    return operations[id]->isEmpty();
}

ValueType Operation::calculate(ValueType arg1, ValueType arg2, Operator op) {
    if(op == Sum){
        if(arg1.second.value() == arg2.second.value())
            return std::make_pair(arg1.first + arg2.first, arg1.second.value());
        else
            throw std::runtime_error("Cannot calculate it. (+)");
    } else if(op == Sub){
        if(arg1.second.value() == arg2.second.value())
            return std::make_pair(arg1.first - arg2.first, arg1.second.value());
        else
            throw std::runtime_error("Cannot calculate it. (-)");
    } else if(op == Mul){
        if(arg1.second.value() == Token::Value)
            return std::make_pair(arg1.first * arg2.first, arg2.second.value());
        else if(arg2.second.value() == Token::Value)
            return std::make_pair(arg1.first * arg2.first, arg1.second.value());

        auto result = Multiplication::getInstance()->getResult(arg1.second.value(), arg2.second.value());
        if(result != Token::BadType)
            return std::make_pair(arg1.first * arg2.first, result);
        else
            throw std::runtime_error("Cannot calculate it. (*)");
    } else if(op == Div){
        if (arg2.first == 0)
            throw std::runtime_error("Div by 0 is illegal.");
        if(arg1.second.value() == arg2.second.value())
            return std::make_pair(arg1.first / arg2.first, Token::Value);

        auto result = Division::getInstance()->getResult(arg1.second.value(), arg2.second.value());
        if(result != Token::BadType)
            return std::make_pair(arg1.first / arg2.first, result);
        else
            throw std::runtime_error("Cannot calculate it. (*)");
    } else if(op == Par){
        //TODO
    } else if(op == LogMul){
        if(arg1.first != 0 && arg2.first != 0)
            return std::make_pair(1, Token::Value);
        else
            return std::make_pair(0, Token::Value);
    } else if(op == LogSum){
        if(arg1.first == 0 && arg2.first == 0)
            return std::make_pair(0, Token::Value);
        else
            return std::make_pair(1, Token::Value);
    } else if(op == L){
        if(arg1.second.value() == arg2.second.value())
            return arg1.first < arg2.first ? std::make_pair(1, Token::Value) : std::make_pair(0, Token::Value);
        else
            throw std::runtime_error("Cannot calculate it. (Less)");
    } else if(op == LE){
        if(arg1.second.value() == arg2.second.value())
            return arg1.first <= arg2.first ? std::make_pair(1, Token::Value) : std::make_pair(0, Token::Value);
        else
            throw std::runtime_error("Cannot calculate it. (Less or Equal)");
    } else if(op == M){
        if(arg1.second.value() == arg2.second.value())
            return arg1.first > arg2.first ? std::make_pair(1, Token::Value) : std::make_pair(0, Token::Value);
        else
            throw std::runtime_error("Cannot calculate it. (More)");
    } else if(op == ME){
        if(arg1.second.value() == arg2.second.value())
            return arg1.first >= arg2.first ? std::make_pair(1, Token::Value) : std::make_pair(0, Token::Value);
        else
            throw std::runtime_error("Cannot calculate it. (More or Equal)");
    } else if(op == E){
        if(arg1.second.value() == arg2.second.value())
            return arg1.first == arg2.first ? std::make_pair(1, Token::Value) : std::make_pair(0, Token::Value);
        else
            throw std::runtime_error("Cannot calculate it. (Equal)");
    } else if(op == NE){
        if(arg1.second.value() == arg2.second.value())
            return arg1.first != arg2.first ? std::make_pair(1, Token::Value) : std::make_pair(0, Token::Value);
        else
            throw std::runtime_error("Cannot calculate it. (Not Equal)");
    }
}

Variable* Operation::getVariable() {
    return variable.get();
}
