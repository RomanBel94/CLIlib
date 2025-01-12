#include "../googletest/googletest/include/gtest/gtest.h"
#include "CLIlib.h"
#include <list>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
