#include <iostream>
#include <list>
#include <vector>
#include "data.h"
#include "matrix.h"

using namespace std;

vector<Command> &parse_test(istream &datafile);

int main()
{
    vector<Command> &transforms = parse_test(cin);

    Matrix transformResult = Matrix(4,4);  // start with identity 4x4

    for (size_t i = 0; i < transforms.size(); i++) {
        string type = transforms[i].transformation;
        vector<double> args = transforms[i].data;
        if (type == "T") {
            Matrix T = Matrix(4,4);
            T.translationMatrix(args[0], args[1], args[2]);
            transformResult *= T;
        } else if (type == "R") {
            Matrix R = Matrix(4,4);
            R.rotationMatrix(args[0], args[1], args[2], args[3]);
            transformResult *= R;
        } else if (type == "S") {
            Matrix S = Matrix(4,4);
            S.scaleFactorMatrix(args[0], args[1], args[2]);
            transformResult *= S;
        }
    }
    transformResult.print(); // print the result to stdout
    return 0;
}
