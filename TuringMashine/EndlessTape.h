#ifndef ENDLESSTAPE_H_INCLUDED
#define ENDLESSTAPE_H_INCLUDED

#include <cstdint>
#include <cstring>
#include "Program.h"

class EndlessTape
{
private:

    enum{SYMBOLS_IN_CHUNK = 32};

    struct DataChunk
    {
        char Symbols[SYMBOLS_IN_CHUNK];

        DataChunk(): PrevChunk(nullptr), NextChunk(nullptr){memset(Symbols+1, 1, SYMBOLS_IN_CHUNK - 2);}

        DataChunk * PrevChunk;
        DataChunk * NextChunk;
    };

    uint8_t PositionInChunk;
    DataChunk * GlobalPosition;

    uint32_t ChunksNumber;
    DataChunk * FirstChunk;
    DataChunk * LastChunk;

    char * StringBuffer;

    void MoveLeft();
    void MoveRight();
    void PutSymbol(char Symbol);

    friend bool Program::Execute(EndlessTape & TapeForExecution);

public:

    EndlessTape(EndlessTape &) = delete;
    EndlessTape(EndlessTape &&) = delete;
    EndlessTape & operator=(EndlessTape &) = delete;
    EndlessTape & operator=(EndlessTape &&) = delete;

    EndlessTape();
    void operator=(const char * String);
    ~EndlessTape();

    void ResetPosition(uint8_t NewPosition = 0);
    char GetCurrentSymbol();
    const char * GetTapeString();
};

#endif // ENDLESSTAPE_H_INCLUDED
