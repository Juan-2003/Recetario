#include <string>

#ifndef AUTOR_HPP
#define AUTOR_HPP

class Autor{
    private:
        std::string firstName;
        std::string lastName;
    
    public:
        Autor();
        Autor(std::string fisrtName, std::string lastName);

        void setFirstName(std::string firstName);
        void setLastName(std::string lastName);
        std::string getFirstName();
        std::string getLastName();

        std::string toString();

        Autor& operator=(const Autor& e);
        bool operator==(const Autor& e);
        bool operator<(const Autor& e);
        bool operator>(const Autor& e);
        bool operator<=(const Autor& e);
        bool operator>=(const Autor& e);
        friend std::ostream& operator <<(std::ostream&, Autor&);
        friend std::istream& operator >>(std::istream&, Autor&);

    };

#endif
