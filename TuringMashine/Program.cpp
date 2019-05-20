#include "mydialog.h"


size_t Program::WordLen(const char * String)
{
    size_t i = 0;
    while(String[i] != ' ')i++;
    return i;
}

bool Program::WordCmp(const char * String1, const char * String2)
{
    if(WordLen(String1) != WordLen(String2))
        return false;
    for(size_t i = 0; String1[i] != ' '; i++)
        if(String1[i] != String2[i])
            return false;
    return true;
}

Program::~Program()
{
    if(ProgramData)
        for(uint16_t i = 0; i < StatesCount; i++)
            delete [] ProgramData[i];

    if(StatesNames)
        for(uint16_t i = 0; i < StatesCount; i++)
            delete [] StatesNames[i];

    delete [] ProgramData;
    delete [] StatesNames;
    delete [] StatesEntriesCount;

    delete [] ErrorString;
}

bool Program::InitProgram(char ** ProgramString, size_t LinesCount)
{
    this->~Program();
    CurrentState = 0;
    StatesCount = 1;
    ProgramIsValid = false;
    Halted = false;

    size_t * LinesNumbers = new size_t[LinesCount];
    for(size_t i = 0; i < LinesCount; i++)
        LinesNumbers[i] = i + 1;

    Sort(ProgramString, LinesCount, LinesNumbers);

    size_t ValidStringsShift = 0;
    while(ProgramString[ValidStringsShift][0] == '\t' || ProgramString[ValidStringsShift][0] == ' ' || ProgramString[ValidStringsShift][0] == '\n' || ProgramString[ValidStringsShift][0] == ';')
        ValidStringsShift++;

    const char * PrevString = ProgramString[ValidStringsShift];
    for(size_t i = 1 + ValidStringsShift; i < LinesCount; i++)
    {
        if(!WordCmp(PrevString, ProgramString[i]))
        {
            StatesCount++;
            PrevString = ProgramString[i];
        }
    }

    StatesEntriesCount = new uint8_t[StatesCount]{};
    StatesEntriesCount[ValidStringsShift]++;
    size_t WordSize = WordLen(ProgramString[ValidStringsShift]);
    StatesNames = new char *[StatesCount];
    StatesNames[ValidStringsShift] = new char[WordSize + 1];
    strncpy(StatesNames[0], ProgramString[ValidStringsShift], WordSize);
    StatesNames[ValidStringsShift][WordSize] = '\0';

    PrevString = ProgramString[0];
    for(size_t i = 1 + ValidStringsShift, j = 0; i < LinesCount; i++)
    {
        if(!WordCmp(PrevString, ProgramString[i]))
        {
            j++;
            PrevString = ProgramString[i];
            WordSize = WordLen(ProgramString[i]);
            StatesNames[j] = new char[WordSize + 1];
            strncpy(StatesNames[j], ProgramString[i], WordSize);
            StatesNames[j][WordSize] = '\0';
        }
        StatesEntriesCount[j]++;
    }

    ProgramData = new ProgramUnit *[StatesCount];
    for(size_t i = 0, Line = ValidStringsShift, StringShift; i < StatesCount; i++)
    {
        ProgramData[i] = new ProgramUnit[StatesEntriesCount[i]];
        for(size_t j = 0; j < StatesEntriesCount[i]; j++, Line++)
        {
            StringShift = 0;
            StringShift += WordLen(ProgramString[Line] + StringShift) + 1;
            ProgramData[i][j].Key = ProgramString[Line][StringShift] == '_'? 0: ProgramString[Line][StringShift];
            StringShift += 2;
            ProgramData[i][j].SetTo = ProgramString[Line][StringShift] == '_'? 0: ProgramString[Line][StringShift];
            StringShift += 2;
            switch(ProgramString[Line][StringShift])
            {
                case '*':
                    ProgramData[i][j].TapeMove = EndlessTape::Stay;
                    break;

                case 'r':
                case 'R':
                    ProgramData[i][j].TapeMove = EndlessTape::MoveRight;
                    break;

                case 'l':
                case 'L':
                    ProgramData[i][j].TapeMove = EndlessTape::MoveLeft;
                    break;
            }
            StringShift += 2;
            if(!strncmp(ProgramString[Line] + StringShift, "halt", 4))
                ProgramData[i][j].NextState = HALT;
            else
                for(size_t k = 0; k < StatesCount; k++)
                    if(!strcmp(ProgramString[Line] + StringShift, StatesNames[k]))
                    {
                        ProgramData[i][j].NextState = k;
                        break;
                    }
        }
    }

    delete [] LinesNumbers;

    ProgramIsValid = true;

    return SUCCESS;
}

void Program::Sort(char ** Strings, size_t n, size_t * Numbers)
{
    const size_t CiuraSteps[9] = {701, 301, 132, 57, 23, 10, 4, 1, 0};
    char * Cashe;
    for(size_t i = 0, d = CiuraSteps[i]; d != 0; d = CiuraSteps[++i])
        for(size_t i = d, j; i < n; i++)
        {
            Cashe = Strings[i];
            for(j = i; j >= d; j -= d)
            {
                if(strcmp(Cashe, Strings[j-d]) < 0)
                {
                    Strings[j] = Strings[j-d];
                    Numbers[j] = Numbers[j-d];
                }
                else
                    break;
            }
            Strings[j] = Cashe;
        }
}

bool Program::Execute(EndlessTape & TapeForExecution)
{
    if(!ProgramIsValid || Halted)
        return ERROR;

    char KeyForCheck = *TapeForExecution.GetCurrentSymbol();
    if(KeyForCheck == ' ')
        KeyForCheck = 0;

    int16_t KeyFinded = -1;
    for(uint8_t i = 0; i < StatesEntriesCount[CurrentState]; i++)
    {
        if(ProgramData[CurrentState][i].Key == KeyForCheck)
        {
            KeyFinded = i;
            break;
        }
        else
            if(ProgramData[CurrentState][i].Key == '*')
                KeyFinded = i;

    }

    if(KeyFinded > -1)
    {
        if(ProgramData[CurrentState][KeyFinded].SetTo != '*')
            TapeForExecution.PutSymbol(ProgramData[CurrentState][KeyFinded].SetTo);
        (TapeForExecution.*ProgramData[CurrentState][KeyFinded].TapeMove)();
        CurrentState = ProgramData[CurrentState][KeyFinded].NextState;
    }
    else
    {
        const char * Str1 = "State, named ";
        const char * Str2 = " has don't have entry for ";

        ErrorString = new char[strlen(Str1) + strlen(StatesNames[CurrentState]) + strlen(Str2) + 2];

        strcpy(ErrorString, Str1);

        size_t ErrorStringShift = strlen(Str1);
        strcpy(ErrorString + ErrorStringShift, StatesNames[CurrentState]);

        ErrorStringShift += strlen(StatesNames[CurrentState]);
        strcpy(ErrorString + ErrorStringShift, Str2);

        ErrorStringShift += strlen(Str2);
        ErrorString[ErrorStringShift] = KeyForCheck? KeyForCheck: '_';
        ErrorString[ErrorStringShift+1] = '\0';

        return ERROR;
    }

    if(CurrentState == HALT)
        Halted = true;

    return SUCCESS;
}
