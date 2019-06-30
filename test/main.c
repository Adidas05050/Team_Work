#define CTEST_MAIN
#define CTEST_COLOR_OK

#include "TuringMashine/EndlessTape.h"
#include "TuringMashine/Program.h"
#include <ctest.h>

int main(int argc, const char *argv[])
{
    return ctest_main(argc, argv);
}

CTEST(Errors_test, Unexpected_symbol)
{
    //Given
    const size_t Lines = 1;
    const char * ProgramText[Lines] = {"0 * * * halt s"};

    //When
    Program A;
    A.InitProgram(ProgramText, Lines);

    //Then
    const char * Expected = "Unexpected symbol(s) on line 1.";
    ASSERT_STR(Expected, A.GetError());
}
