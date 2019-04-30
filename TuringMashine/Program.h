#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <cstdint>

class EndlessTape;

class Program
{
private:

    struct ProgramUnit
    {
        char Key;
        char SetTo;
        uint8_t TapeShift;
        uint16_t NextState;
    };

    ProgramUnit ** ProgramData;
    uint8_t * StatesEntriesCount;

    char ** StatesNames;

    uint16_t CurrentState;
    char * ErrorString;

    void ClearProgram();

public:

    Program(Program &) = delete;
    Program(Program &&) = delete;
    Program & operator=(Program &) = delete;
    Program & operator=(Program &&) = delete;

    Program();
    ~Program();

    bool InitProgram(const char ** ProgramString);
    void ResetState();

    bool Execute(EndlessTape & TapeForExecution);

    const char * GetError();
};

#endif // PROGRAM_H_INCLUDED
