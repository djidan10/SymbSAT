#include <iostream>
#include <fstream>

#include "poly.h"
#include "gb.h"

int main (int argc, char *argv[]) {
    std::ifstream cnf(argv[1]);

    std::cout << "cnf-file - '" << argv[1] << "'" << std::endl;

    std::string str;
    while (!cnf.eof() && cnf.peek() == 'c') {
        getline(cnf, str);
        std::cout << str << "\n";
    }

    if (cnf.peek() != 'p') {
        std::cerr << "Error to content file '" << argv[1] << "'" << std::endl;
        cnf.close();
        return EXIT_FAILURE;
    }

    cnf.ignore(6);
    int pols=-1, vars=-1;
    cnf >> vars >> pols;
    std::cout << "variables - " << vars << ", polynomials - " << pols << std::endl;

    std::vector<Poly> P;

    int line = 0;
    while (!cnf.eof()) {
        int var = 0;

        Monom m_one(0);
        Poly p(m_one), _1(m_one);
        do {
            cnf >> var;
            Monom m(std::abs(var));
            if (var > 0) {
                p = p*m;
            }  else if (var < 0) {
                Poly tmp(m);
                p = p*(tmp + _1);
            }
        } while (var);

        if (!p.isOne())
            P.push_back(p);

        ++line;
    }

    for (auto&& p: P) 
        std::cout << p << "\n";

    auto G = buchberger(P, vars);

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";

    for (auto&& p: G) 
        std::cout << p << "\n";

    cnf.close();

    return EXIT_SUCCESS;
}
