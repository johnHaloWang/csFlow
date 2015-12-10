#include <iostream>
#include <ctokenize.h>

using namespace std;

int main()
{
    CTokenize test("int x = 55; if(x > 55){x += 2; else { x = 0}}");
    Token* temp = NULL;

    while(test.More())
    {
        temp = test.NextToken();
        cout << temp->TokenString() << "     Type: [" << temp->Type() << "]" << " Sub-type: ["
             << temp->SubType() << "]" << endl;
    }


    return 0;
}

