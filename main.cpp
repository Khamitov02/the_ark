#include <iostream>
#include <iomanip>
#include "TheArk.h"
using std::cin;
using std::cout;
using std::endl;

int main() {
    TheArk & ark = *TheArk::get_instance();

    ark.init(&cin, &cout);
    cout << std::setw(CELL_WIDTH) << "Total"
         << std::setw(CELL_WIDTH) << "Child"
         << std::setw(CELL_WIDTH) << "Adults"
         << std::setw(CELL_WIDTH) << "Old"
         << std::setw(CELL_WIDTH) << "Consum"
         << std::setw(CELL_WIDTH) << "Compon"
         << std::setw(CELL_WIDTH) << "Used"
         << std::setw(CELL_WIDTH) << "Junk"
         << std::setw(CELL_WIDTH) << "Ref";

    for (int i = 0; i < 6; ++i)
        cout << std::setw(CELL_WIDTH - 1) << "St" << i;

    cout << endl;

    ark.flight();
    ark.deleteArk();

    return 0;
}
