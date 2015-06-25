
#include <iostream>
#include <list>

using namespace std;

int LambdasAndContainers()
{
    // что это за выражение и в чем ошибка?
    auto summ = [] (int v1, int v2) -> int
    {
       return v1 + v2;
    };

    // как заставить данное выражение работать?
    auto summ2 = [&] (int v1, int v2) -> int
    {
       return summ(v1, v2);
    };

    cout << summ(1, 2) << endl;
    cout << summ2(0, 1) << endl;

    // Есть некая структура или класс
    struct ItemContainer
    {
       ItemContainer(int val) :value(val) {}
       int value = 0;
    };


    // есть контейнер.
    list<ItemContainer *> some_container;

    // в нем несколько элементов
    ItemContainer *item1 = new ItemContainer(1);
    ItemContainer *item2 = new ItemContainer(2);
    ItemContainer *item3 = new ItemContainer(3);

    some_container.push_back(item1);
    some_container.push_back(item2);
    some_container.push_back(item3);

    int elements_summ = 0;
    // найти сумму элементов максимально простым образом.
    for (auto item : some_container)
    {
       elements_summ += item->value;
    }

    ItemContainer *valueToFind = item2;
    // найти элемент величиной value_to_find
    auto foundItem = find_if( some_container.begin(), some_container.end(), [&valueToFind] (const ItemContainer * const item) -> bool
    {
           return item->value == valueToFind->value;
    });
    if (nullptr != *foundItem)
    {
       cout << (*foundItem)->value << endl;
    }


    //как улучшить?
    auto criteriaLambda = [&valueToFind] (const ItemContainer * const item) -> bool
    {
        return item->value == valueToFind->value;
    };
    foundItem = find_if(some_container.begin(), some_container.end(), criteriaLambda);

    auto findFunc = [] (const list<ItemContainer *> &items, const int val) -> ItemContainer *
    {
       for (auto item : items)
       {
           if (item->value == val)
           {
               return item;
           }
       }
       return nullptr;
    };

    findFunc(some_container, 1);

    // как сделать перебор по известному контейнеру?
    auto findFuncContainer = [&some_container] (const int val) -> ItemContainer *
    {
        for (auto item : some_container)
        {
            if (item->value == val)
            {
                return item;
            }
        }
        return nullptr;
    };

    findFuncContainer(2);

    // как сделать перебор без foreach?
    auto findWithoutForeach = [] (const list<ItemContainer *> &items, const int val) -> ItemContainer *
    {
        ItemContainer itemToFind(val);
        auto it = find_if(items.begin(), items.end(),
                          [&itemToFind] (const ItemContainer * const itemInList) -> bool
        {
            return itemToFind.value == itemInList->value;
        });
        if (items.end() != it)
        {
            return *it;
        }
        return nullptr;
    };

    cout << findWithoutForeach(some_container, 3)->value << endl;

    return 0;
}

