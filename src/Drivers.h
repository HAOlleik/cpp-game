#ifndef DRIVERS_H
#define DRIVERS_H

#include <iostream>
#include <string>
#include <vector>

#include "CommandProcessing.h"

void testLoadMaps();
void testGameEngineStates();
void testOrdersLists();
// void testPlayers();
void testCards();
void testCommandProcessor(vector<string> arguments, size_t size);

#endif