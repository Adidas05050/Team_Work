#inlcude "EndlessTape.h"

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

EndlessTape::EndlessTape & operator=(EndlessTape &)
{

}

EndlessTape::EndlessTape & operator=(EndlessTape &&)
{

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
