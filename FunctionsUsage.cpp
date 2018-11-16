#include "FunctionsUsage.h"

#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

int functionForBindTest(int a, int b, int c)
{
    return a + b + c;
}

void FunctionsUsage()
{
    std::cout << "Functions and Shared Pointers" << std::endl;
    
    std::function<int (int, int)> summ = [] (int a, int b) -> int
    {
        return a + b;
    };
    
    std::cout << summ(1, 2) << std::endl;
    
    struct ItemType
    {
        ItemType() = delete;
        explicit ItemType(int val)
            : value(val)
        {
            std::cout << "Creation of ItemType with Value = " << value << std::endl;
        }
        
        ~ItemType()
        {
            std::cout << "Destruction of ItemType with Value = " << value << std::endl;
        }
        
        
        
        int value;
    };
    
    {
        
        std::vector<std::shared_ptr<ItemType> > intVector;
        
        auto item = std::make_shared<ItemType>(1);
        intVector.push_back(item);
        intVector.push_back(std::make_shared<ItemType>(2));
        
        
        auto criteria = [&item] (const std::shared_ptr<ItemType> it) -> bool
        {
            return item->value == it->value;
        };
        
        auto it = std::find_if(intVector.begin(), intVector.end(), criteria);
        
        if (it != intVector.end())
        {
            std::cout << (*it)->value << std::endl;
        }
        
        
        auto sharedItem = std::make_shared<ItemType>(3);
        std:: cout << "Used References for just created item " << sharedItem->value << " = " << sharedItem.use_count() << std::endl;
        
        struct ItemDeleter
        {
            ItemDeleter(std::shared_ptr<ItemType> itemToHold) : ownedItem(itemToHold)
            {
                // здесь будет вывод что использовано 3 референса. Почему 3 и как сделать 2?
                std::cout << "Used References for owned item " << ownedItem->value << " = " << ownedItem.use_count() << std::endl;
            }
            
            std::shared_ptr<ItemType> ownedItem;
        };

        ItemDeleter *deleter = new ItemDeleter(sharedItem);
        delete deleter;
        std::cout << "Used References for shared item after delete owner item " << sharedItem->value << " = " << sharedItem.use_count() << std::endl;
    }
    
    std::vector<std::shared_ptr<ItemType> > itemsList;
    
    itemsList.emplace_back(std::make_shared<ItemType>(3));
    itemsList.emplace_back(std::make_shared<ItemType>(5));
    itemsList.emplace_back(std::make_shared<ItemType>(2));
    itemsList.emplace_back(std::make_shared<ItemType>(4));
    itemsList.emplace_back(std::make_shared<ItemType>(1));
    
    std::sort(itemsList.begin(), itemsList.end(),[] (const std::shared_ptr<ItemType> &a, const std::shared_ptr<ItemType> &b) -> bool
    {
        return a->value > b->value;
    });
    
    std::cout << "sorted list " << std::endl;
    for (auto item : itemsList)
    {
        std::cout << item->value << std::endl;
    }
    
    
    // лямбда как bind
    // допустим есть некая функция с 3 параметрами. Мы хотим сделать функциональный объект, которому будем передавать
    // 2 параметра, а третий должен быть закреплен в фиксированном значении.
    
    
    std::function<int (int, int, int)> FunctionObj = [] (int a, int b, int c) -> int
    {
        return a + b + c;
    };
    
    auto bind = [&FunctionObj] (int a, int b) -> int
    {
        return FunctionObj(a, b, 3);
    };
    
    bind(1,2);
    
    //пойдем дальше
    auto func = functionForBindTest;
    auto bind1 = [&func] (int a, int b) -> int
    {
        return func(a, b, 3);
    };
    
    bind1(1, 2);
    
}
