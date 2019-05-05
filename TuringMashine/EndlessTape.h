#ifndef ENDLESSTAPE_H_INCLUDED
#define ENDLESSTAPE_H_INCLUDED

#include <cstdint>
#include "Program.h"

class EndlessTape
{
public:
    enum{SYMBOLS_IN_CHUNK = 32};

private:

    struct DataChunk
    {
        char Symbols[SYMBOLS_IN_CHUNK];

        DataChunk(): Symbols{}, PrevChunk(nullptr), NextChunk(nullptr){}
        char & operator[](unsigned int i){return Symbols[i];}

        DataChunk * PrevChunk;
        DataChunk * NextChunk;
    };

    uint8_t PositionInChunk;
    DataChunk * GlobalPosition;

    uint32_t ChunksNumber;
    DataChunk * FirstChunk;
    DataChunk * LastChunk;

    bool InvalidString;
    int16_t StringShift;
    uint16_t OutputBufferSize;
    char * StringBuffer;

    int16_t MoveLeft();
    int16_t MoveRight();
    void PutSymbol(char Symbol){(*GlobalPosition)[PositionInChunk] = Symbol;}

    friend bool Program::Execute(EndlessTape & TapeForExecution);

public:

    EndlessTape(EndlessTape &) = delete;
    EndlessTape(EndlessTape &&) = delete;

    EndlessTape(uint8_t OutputBufferLength);
    void operator=(const char * String);
    ~EndlessTape();

    EndlessTape & operator=(EndlessTape & CopiedTape);
    EndlessTape & operator=(EndlessTape && MovedTape);

    char GetCurrentSymbol(){return (*GlobalPosition)[PositionInChunk];}
    void ResetPosition();
    bool StringIsInvalid(){return InvalidString;}
    const char * GetTapeString();
};

#endif // ENDLESSTAPE_H_INCLUDED
