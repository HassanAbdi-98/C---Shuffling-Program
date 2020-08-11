#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class StringUtils {
public:
    virtual std::string performStep(std::string input) = 0; // Pure Virtual Function
};


class Reverser:public StringUtils {
public:
    std::string performStep(std::string input) {
        //std::cout << "Reverser Function in Derived class"<< std::endl;
        std::string rev = std::string(input.rbegin(),input.rend());
        return rev;
    }
};

class Cutter:public StringUtils {
private:
    int n;
public:
    Cutter(){

    }
    Cutter(int opcount){
        n=opcount;
    }
    void setSteps(int opcount){
        n=opcount;
    }
    std::string performStep(std::string input) {
        //std::cout << "Cutter Function in Derived class"<< std::endl;
        std::string str2 = input.substr(0, n);
        std::string str3 = input.substr(n, input.length());

        return str3+str2;
    }
};

std::vector<std::string> getAllStepsToPerform(){
    std::vector<std::string> vecOfStr;
    std::ifstream in("steps.txt");
    std::string str;

    while (std::getline(in, str))
    {

        if(str.size() > 0)
            vecOfStr.push_back(str);
    }

    in.close();
    return vecOfStr;
}

std::vector<std::string> getStringsToPerformOn(){
    std::vector<std::string> vecOfStr;
    std::ifstream in("inputs.txt");
    std::string str;

    while (std::getline(in, str))
    {

        if(str.size() > 0)
            vecOfStr.push_back(str);
    }

    in.close();
    return vecOfStr;
}



int main()
{
    std::vector<std::string> stepsToPerform=getAllStepsToPerform();
    std::vector<std::string> stringsToPerformOn=getStringsToPerformOn();
    StringUtils *objStringUtils;
    Reverser objReverser;
    Cutter objCutter;

    for(std::string toWorkOn: stringsToPerformOn){
        std::string tempToWorkOn=toWorkOn;
        for(std::string stepToPerform: stepsToPerform){

            if(stepToPerform.rfind("rev", 0) == 0){
                objStringUtils = &objReverser;
                tempToWorkOn=objStringUtils->performStep(tempToWorkOn);
            } else {

                std::istringstream ss(stepToPerform);
                std::string act;
                int countn;
                ss >> act >> countn;
                objCutter.setSteps(countn);
                objStringUtils = &objCutter;

                tempToWorkOn=objStringUtils->performStep(tempToWorkOn);
            }

        }
        std::cout<<tempToWorkOn<< std::endl;
    }


    \
}
