#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <cstdint>
#include <cstring>

class EndlessTape;

class Program
{
private:

    struct ProgramUnit
    {
        char Key;
        char SetTo;
        void (EndlessTape::*TapeMove)();
        uint16_t NextState;
    };

    ProgramUnit ** ProgramData;

    uint8_t * StatesEntriesCount;
    uint16_t StatesCount;
    char ** StatesNames;
    enum{HALT = 0xFFFF};
    uint16_t CurrentState;
    bool Halted;

    bool ProgramIsValid;
    char * ErrorString;

    size_t WordLen(const char * String);
    bool WordCmp(const char * String1, const char * String2);
    void Sort(const char ** Strings, size_t n, size_t * Numbers);

public:
    enum{ERROR = false, SUCCESS = true};

    Program(Program &) = delete;
    Program(Program &&) = delete;
    Program & operator=(Program &) = delete;
    Program & operator=(Program &&) = delete;

    Program(): ProgramData(nullptr), StatesEntriesCount(nullptr), StatesCount(0), StatesNames(nullptr), CurrentState(0), Halted(false), ProgramIsValid(false), ErrorString(nullptr){}
    ~Program();

    bool InitProgram(const char ** ProgramString, size_t LinesCount);
    void ResetState(){Halted = false, CurrentState = 0;}

    bool Execute(EndlessTape & TapeForExecution);

    const char * GetError(){return ErrorString? ErrorString: Halted? "Program has been halted!": "Program has not been initialized!";}
};

#endif // PROGRAM_H_INCLUDED
