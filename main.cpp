#include <iostream>
#include "TheArk.h"
using std::cin;
using std::cout;

int main() {
    TheArk & ark = *TheArk::get_instance();

    ark.init(&cin, &cout);
    ark.flight();
    ark.deleteArk();

    return 0;
}
