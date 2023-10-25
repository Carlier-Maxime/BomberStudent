#include <iostream>
#include "Log.h"

int main() {
    Log::open();
    Log::info("Launching BomberStudent...");
    Log::info("BomberStudent launched");
    Log::close();
}