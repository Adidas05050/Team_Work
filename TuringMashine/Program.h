#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <cstdint>

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

    char * StatesNames;

public:
    enum{LEFT = -1, STAY, RIGHT};

    Program(Program &) = delete;
    Program(Program &&) = delete;
    Program & operator=(Program &) = delete;
    Program & operator=(Program &&) = delete;

    Program();
    ~Program();

    void InitProgram(uint16_t StatesCount, uint8_t * EntriesCount);
    bool InitState(const char * StringForCompilation, char ** StringForErrorOutput);

    struct LastExecutionResult
    {
        uint8_t ErrorCode;
        uint8_t TapeMoving;
        uint16_t NewState;
    };

    LastExecutionResult ExecuteCommand(uint16_t State, char Key);
};

#endif // PROGRAM_H_INCLUDED
