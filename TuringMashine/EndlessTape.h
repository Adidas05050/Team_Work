#ifndef ENDLESSTAPE_H_INCLUDED
#define ENDLESSTAPE_H_INCLUDED

#include <cstdint>
#include <utility>

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

    void Stay(){}
    void MoveLeft();
    void MoveRight();
    void PutSymbol(char Symbol){(*GlobalPosition)[PositionInChunk] = Symbol;}

    friend class Program;

public:

    EndlessTape & operator=(EndlessTape & CopiedTape);
    EndlessTape & operator=(EndlessTape && MovedTape);
    void operator=(const char * String);

    EndlessTape();
    EndlessTape(EndlessTape & CopiedTape): EndlessTape(){operator=(CopiedTape);}
    EndlessTape(EndlessTape && MovedTape): EndlessTape(){operator=(std::move(MovedTape));}
    EndlessTape(const char * String): EndlessTape(){operator=(String);}
    ~EndlessTape();

    void ResetPosition();
    char GetCurrentSymbol(){return (*GlobalPosition)[PositionInChunk];}
};

#endif // ENDLESSTAPE_H_INCLUDED
