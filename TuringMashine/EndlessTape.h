#ifndef ENDLESSTAPE_H_INCLUDED
#define ENDLESSTAPE_H_INCLUDED

#include <cstdint>

class EndlessTape
{
private:

    enum{SYMBOLS_IN_CHUNK = 32};

    struct DataChunk
    {
        char Symbols[SYMBOLS_IN_CHUNK];

        DataChunk(): Symbols{}, PrevChunk(nullptr), NextChunk(nullptr){}

        DataChunk * PrevChunk;
        DataChunk * NextChunk;
    };

    uint8_t PositionInChunk;
    DataChunk * GlobalPosition;

    uint32_t ChunksNumber;
    DataChunk * FirstChunk;
    DataChunk * LastChunk;

    char * StringBuffer;

public:

    EndlessTape(EndlessTape &) = delete;
    EndlessTape(EndlessTape &&) = delete;
    EndlessTape & operator=(EndlessTape &) = delete;
    EndlessTape & operator=(EndlessTape &&) = delete;

    EndlessTape();
    void operator=(const char * String);
    ~EndlessTape();

    void MoveLeft();
    void MoveRight();
    void ResetPosition();
    void PutSymbol(char Symbol);
};

#endif // ENDLESSTAPE_H_INCLUDED
