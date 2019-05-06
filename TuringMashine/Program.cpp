#include "Program.h"
#include "EndlessTape.h"

void Program::ClearProgram()
{
    this->~Program();

    CurrentState = 0;
    StatesCount = 0;
}

Program::~Program()
{
    for(uint16_t i = 0; i < StatesCount; i++)
    {
        delete [] ProgramData[i];
        delete [] StatesNames[i];
    }
    delete [] ProgramData;
    delete [] StatesNames;
    delete [] StatesEntriesCount;

    delete [] ErrorString;
}

bool Program::InitProgram(const char ** ProgramString)
{
    return ERROR;
}

bool Program::Execute(EndlessTape & TapeForExecution)
{
    if(!ProgramIsValid)
        return ERROR;

    char KeyForCheck = TapeForExecution.GetCurrentSymbol();

    bool KeyNotFinded = true;
    for(uint8_t i = 0; i < StatesEntriesCount[CurrentState]; i++)
        if(ProgramData[CurrentState][i].Key == KeyForCheck)
        {
            KeyNotFinded = false;
            TapeForExecution.PutSymbol(ProgramData[CurrentState][i].SetTo);
            (TapeForExecution.*ProgramData[CurrentState][i].TapeMove)();
            CurrentState = ProgramData[CurrentState][i].NextState;
            break;
        }

    if(KeyNotFinded)
        return ERROR;

    return SUCCESS;
}
