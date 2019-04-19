#include"fiveInARow.h"

using namespace fiveInARow;

int main(int argc, char ** argv)
{
    Chess fchess;
    fchess.evaluate();
    cout<< fchess.value() <<endl;
    return 0;
}

