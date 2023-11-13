// #include "Order.h"
// #include "Drivers.h"

// void testOrdersLists()
// {
//     DeployOrder deploy;
//     AdvanceOrder advance;
//     BombOrder bomb;
//     BlockadeOrder blockade;
//     AirliftOrder airlift;
//     NegotiateOrder negotiate;
//     OrdersList list;

//     std::cout << "========================" << endl;
//     std::cout << "Inserting orders in list" << endl;
//     list.addOrder(&deploy);
//     list.addOrder(&advance);
//     list.addOrder(&bomb);
//     list.addOrder(&blockade);
//     list.addOrder(&airlift);
//     list.addOrder(&negotiate);
//     std::cout << "========================" << endl;
//     std::cout << "Printing orders in list" << endl;
//     std::cout << "========================" << endl;
//     list.printOrders();

//     // demo remove order
//     std::cout << "========================" << endl;
//     std::cout << "Removing orders from list" << endl;
//     std::cout << "========================" << endl;

//     list.remove(0);


//     // print again
    
//     list.printOrders();

//     // demo
//     std::cout << "========================" << endl;
//     std::cout << "Moving orders in list" << endl;
//     std::cout << "========================" << endl;
//     list.move(0, 3);

//     // print again
//     std::cout << "========================" << endl;
//     std::cout << "Printing orders in list" << endl;
//     std::cout << "========================" << endl;
//     list.printOrders();

//     // executing the order
//     std::cout << "========================" << endl;
//     std::cout << "Executing orders " << endl;
//     std::cout << "========================" << endl;
//     deploy.execute();
//     advance.execute();
// }