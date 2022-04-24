#include <iostream>
#include <list>
#include <climits>
#include <cmath>

using namespace std;

struct DeliveryMan
{
    int time;
    int items[100];
};

struct ListOfNodes
{
    int initialPoint;
    int distance;
};

// function to create graph for calculate
//@Param list to create graph
//@Param value aux
//@Param value aux
//@Param value weight
void createGraphMethod(list<ListOfNodes> adjacencyList[], int valueOne, int valueTwo, int weight)
{
    adjacencyList[valueOne].push_back({valueOne, weight});
    adjacencyList[valueTwo].push_back({valueTwo, weight});
}

// function based on a dijsktra Algotorithm to calculate better route
//@Param list of node
//@Param number of vertices
//@Param start
//@Param end
//@Param totalCost for route
void dijkstraAlgorithm(
    list<ListOfNodes> adjacencyList[],
    int verticesNumber,
    int start,
    int end,
    int &totalCost)
{
    int distanceArray[10];
    int parents[10];
    int auxValue = 0;
    int destination;
    int weight;
    int distance;
    int index;
    int cost;

    list<int> path;
    list<int>::iterator pathIterator;
    list<ListOfNodes>::iterator nodeIterator;

    bool hasOnThere[10];

    for (int aux = 1; aux <= verticesNumber; aux++)
    {
        hasOnThere[aux] = false;
        distanceArray[aux] = INT_MAX;
        parents[aux] = -1;
    }

    distanceArray[start] = 0;
    index = start;

    while (!hasOnThere[index])
    {
        hasOnThere[index] = true;

        for (
            nodeIterator = adjacencyList[index].begin();
            nodeIterator != adjacencyList[index].end();
            nodeIterator++)
        {
            destination = nodeIterator->initialPoint;
            weight = nodeIterator->distance;
            if (distanceArray[destination] > distanceArray[index] + weight)
            {
                distanceArray[destination] = distanceArray[index] + weight;
                parents[destination] = index;
            }
        }

        distance = INT_MAX;

        for (int aux = 1; aux <= verticesNumber; aux++)
        {
            if (!hasOnThere[aux] && distance > distanceArray[aux])
            {
                distance = distanceArray[aux];
                index = aux;
                auxValue += aux;
            }
        }
    }

    auxValue = end;
    path.push_front(end);

    while (parents[auxValue] != -1)
    {
        path.push_front(parents[auxValue]);
        auxValue = parents[auxValue];
    }

    cost = distanceArray[end];

    cout << "Menor caminho: ";
    for (pathIterator = path.begin(); pathIterator != path.end(); pathIterator++)
    {
        cout << *pathIterator << " ";
    }

    cout << endl;
    totalCost += cost;
}

// Function quickSortMethod to order the deliveryMans
//@Param struct of array deliveryMans
//@Param number of deliveryMans
//@Param struct of array deliveryMans
//@Param value aux
//@Param value aux
void quickSortMethod(DeliveryMan deliveryMan[], int manyDeliveryMan, int valueOne, int valueTwo)
{
    int left = valueOne;
    int right = valueTwo;
    int axys;
    int acessValue;

    axys = deliveryMan[int(round((left + right)) / 2.0)].time;

    do
    {
        while (deliveryMan[left].time < axys)
        {
            left++;
        }

        while (deliveryMan[right].time > axys)
        {
            right--;
        }

        if (left <= right)
        {
            acessValue = deliveryMan[left].time;
            deliveryMan[left].time = deliveryMan[right].time;
            deliveryMan[right].time = acessValue;

            left++;
            right--;
        }
    } while (left <= right);

    // recursive
    if (right - valueOne >= 0)
    {
        quickSortMethod(deliveryMan, manyDeliveryMan, valueOne, right);
    }

    // recursive
    if (valueTwo - left >= 0)
    {
        quickSortMethod(deliveryMan, manyDeliveryMan, left, valueTwo);
    }
}
// Function to choose the itens to the deliveryman
//@Param The quantity of itens
//@Param The capacity
//@Param The initialLocation
void chooseItemsMethod(
    int manyItems,
    int capacity,
    int locationId,
    int initialLocation,
    const int weights[],
    int manyDeliveryMans,
    list<ListOfNodes> adjacencyList[],
    DeliveryMan deliveryMans[])
{
    int manyItemsTaken = 0;
    int totalCost = 0;
    int remainingCapacity = capacity;

    // create array of taken items
    bool takenItems[100];
    bool hasTaken = false;

    for (int j = 1; j <= manyDeliveryMans; j++)
    {
        for (int i = 1; i <= manyItems + 1; i++)
        {
            deliveryMans[j].items[i] = -1;
        }
    }

    for (int i = 0; i <= manyItems; i++)
    {
        takenItems[i] = false;
    }

    for (int j = 1; j <= manyDeliveryMans; j++)
    {
        totalCost = deliveryMans[j].time;

        for (int i = 1; i <= manyItems + 1; i++)
        {
            if (remainingCapacity >= weights[i] && i != initialLocation && !takenItems[i])
            {
                manyItemsTaken++;
                deliveryMans[j].items[manyItemsTaken] = i;
                remainingCapacity -= weights[i];
                takenItems[i] = true;
            }
        }

        if (manyItemsTaken == 0)
        {
            cout << "O entregador " << j + 1 << " nao pegou nenhum item\n";
            cout << "Não realizou nenhuma entregas\n";
            cout << "Não teve tempo de realizar nenhuma entrega\n";
        }
        cout << "O entregador " << j + 1 << " esta com o(s) item(ns): \n";
        for (int i = 1; i <= manyItemsTaken; i++)
        {
            if (deliveryMans[j].items[i] != -1)
            {
                cout << deliveryMans[j].items[i] << " ";
            }
        }
        for (int i = 1; i <= manyItemsTaken; i++)
        {
            if (!hasTaken)
            {
                dijkstraAlgorithm(
                    adjacencyList,
                    locationId,
                    initialLocation,
                    deliveryMans[j].items[i],
                    totalCost);
                hasTaken = true;
            }
            else
            {
                dijkstraAlgorithm(
                    adjacencyList,
                    locationId,
                    deliveryMans[j].items[i - 1],
                    deliveryMans[j].items[i],
                    totalCost);
            }
        }

        if (manyItemsTaken != 0)
        {
            cout << "Ele gastou " << totalCost << " minuto(s)" << endl;
        }

        hasTaken = false;

        remainingCapacity = capacity;

        totalCost = 0;
        manyItemsTaken = 0;
    }
}

int main()
{
    list<ListOfNodes> adjacencyList[100];

    DeliveryMan deliveryMans[100];

    int weights[100];

    int manyDeliveryMan;

    int originalLocation;
    int destinyLocation;
    int timeUntilLocation;
    int locationId;
    int superMarket;
    int auxOne;
    int auxTwo;
    int capacity;
    int itemsId;

    cout << "Quantas localizacoes vao ser?\n ";
    cin >> locationId;

    cout << "Qual vai ser a posicao do mercado?\n ";
    cin >> superMarket;

    // create graph
    do
    {
        //        cout << "Entre a casa de origem, a de destino e o tempo entre elas: \n";
        //        cout << "Apos preencher tudo entre com 0 0 0 para finalizar \n";
        cin >> originalLocation >> destinyLocation >> timeUntilLocation;
        createGraphMethod(adjacencyList, originalLocation, destinyLocation, timeUntilLocation);
    } while (originalLocation != 0 && destinyLocation != 0 && timeUntilLocation != 0);

    // get how many deliveryman will be
    cout << "Vão ser quantos entregadores? ";
    cin >> manyDeliveryMan;

    // calculate time for each deliveryman
    for (auxOne = 0; auxOne < manyDeliveryMan; auxOne++)
    {
        cout << "Tempo do entregador " << auxOne + 1 << " : ";
        cin >> deliveryMans[auxOne].time;
    }

    // set how many deliveryMan
    auxTwo = manyDeliveryMan;
    quickSortMethod(deliveryMans, manyDeliveryMan, 1, auxTwo);

    // set how many items
    cout << "Entre com a quantidade de itens: ";
    cin >> itemsId;

    // set backpack supported
    cout << "Entre com a capacidade da mochila: ";
    cin >> capacity;

    for (auxOne = 1; auxOne <= itemsId + 1; auxOne++)
    {
        if (auxOne != superMarket)
        {
            cout << "Entre com o peso do item " << auxOne << ": ";
            cin >> weights[auxOne];
        }
    }
    // function that will calculate and return
    chooseItemsMethod(
        itemsId,
        capacity,
        locationId,
        superMarket,
        weights,
        manyDeliveryMan,
        adjacencyList,
        deliveryMans);

    return 0;
}
