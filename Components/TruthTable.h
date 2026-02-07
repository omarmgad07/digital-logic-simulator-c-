#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

class ApplicationManager;

class TruthTable
{
private:
    ApplicationManager* pManager;

public:
    TruthTable(ApplicationManager* pApp);
    void BuildTruthTable();
};

#endif
