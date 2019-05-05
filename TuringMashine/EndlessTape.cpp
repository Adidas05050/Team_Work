#include "EndlessTape.h"
#include <cstring>

int16_t EndlessTape::MoveLeft()
{

}

int16_t EndlessTape::MoveRight()
{

}

EndlessTape::EndlessTape(uint8_t OutputBufferLength)
{
    PositionInChunk = 0;

    ChunksNumber = 1;
    GlobalPosition = new DataChunk;
    FirstChunk = GlobalPosition;
    LastChunk = GlobalPosition;

    InvalidString = true;
    OutputBufferSize = (OutputBufferLength + 2)*SYMBOLS_IN_CHUNK;
    StringBuffer = new char[OutputBufferSize]{};
}

void EndlessTape::operator=(const char * String)
{
    size_t StringLength = strlen(String);

    DataChunk * CurrentChunk;
    while(FirstChunk)
    {
        CurrentChunk = FirstChunk->NextChunk;
        delete FirstChunk;
        FirstChunk = CurrentChunk;
    }

    PositionInChunk = 0;
    ChunksNumber = 1;
    GlobalPosition = FirstChunk = new DataChunk;
    for(CurrentChunk = FirstChunk; StringLength > SYMBOLS_IN_CHUNK; StringLength -= SYMBOLS_IN_CHUNK, String += SYMBOLS_IN_CHUNK)
    {
        strncpy(CurrentChunk->Symbols, String, SYMBOLS_IN_CHUNK);
        CurrentChunk->NextChunk = new DataChunk;
        CurrentChunk->NextChunk->PrevChunk = CurrentChunk;
        CurrentChunk = CurrentChunk->NextChunk;
        ChunksNumber++;
    }
    strncpy(CurrentChunk->Symbols, String, StringLength);
    LastChunk = CurrentChunk;
    InvalidString = true;
}

EndlessTape::~EndlessTape()
{
    DataChunk * Temp;
    while(FirstChunk)
    {
        Temp = FirstChunk->NextChunk;
        delete FirstChunk;
        FirstChunk = Temp;
    }
    delete [] StringBuffer;
}

EndlessTape & EndlessTape::operator=(EndlessTape & CopiedTape)
{
    PositionInChunk = CopiedTape.PositionInChunk;
    ChunksNumber = CopiedTape.ChunksNumber;

    FirstChunk = new DataChunk;
    strncpy(FirstChunk->Symbols, CopiedTape.FirstChunk->Symbols, SYMBOLS_IN_CHUNK);
    if(CopiedTape.GlobalPosition == CopiedTape.FirstChunk)
        GlobalPosition = FirstChunk;

    DataChunk * i = FirstChunk;
    for(DataChunk * j = CopiedTape.FirstChunk->NextChunk; j; i = i->NextChunk, j = j->NextChunk)
    {
        i->NextChunk = new DataChunk;
        i->NextChunk->PrevChunk = i;
        strncpy(i->NextChunk->Symbols, j->Symbols, SYMBOLS_IN_CHUNK);
        if(CopiedTape.GlobalPosition == j)
            GlobalPosition = i->NextChunk;
    }
    LastChunk = i;

    InvalidString = true;
    OutputBufferSize = CopiedTape.OutputBufferSize;
    StringBuffer = new char[OutputBufferSize]{};
}

EndlessTape & EndlessTape::operator=(EndlessTape && MovedTape)
{
    PositionInChunk = MovedTape.PositionInChunk;
    GlobalPosition = MovedTape.GlobalPosition;
    MovedTape.GlobalPosition = nullptr;

    ChunksNumber = MovedTape.ChunksNumber;
    FirstChunk = MovedTape.FirstChunk;
    LastChunk = MovedTape.LastChunk;
    MovedTape.FirstChunk = MovedTape.LastChunk = nullptr;

    InvalidString = MovedTape.InvalidString;
    StringShift = MovedTape.StringShift;
    OutputBufferSize = MovedTape.OutputBufferSize;
    StringBuffer = MovedTape.StringBuffer;
    MovedTape.StringBuffer = nullptr;
}

void EndlessTape::ResetPosition()
{
    PositionInChunk = 0;
    GlobalPosition = FirstChunk;
    InvalidString = true;
}

const char * EndlessTape::GetTapeString()
{

}
