#include <iostream>
#include <fstream>
#include <sstream>
#include <comlar.hpp>

int main(int argc, char** argv){
    
    bool ifflag = false;
    bool offlag = false;
    std::string ifstr, ofstr;

    comlar::Executor exec(argc, argv);
    {
        comlar::Option<comlar::Arg<std::string>> opt{"i", "input", comlar::OPTIONAL};
        opt.set_function([&](const std::string& ifstr_){
            ifstr = ifstr_;
            ifflag = true;
            return 0;
        });
        exec.add_option(opt);
    }
    {
        comlar::Option<comlar::Arg<std::string>> opt{"o", "output", comlar::OPTIONAL};
        opt.set_function([&](const std::string& ofstr_){
            ofstr = ofstr_;
            offlag = true;
            return 0;
        });
        exec.add_option(opt);
    }
    {
        comlar::Option<> opt{"h", "help", comlar::OPTIONAL};
        opt.set_function([](void){
            std::cout<<"No NewLine ver.1.1 (2023/10/24)"<<std::endl;
            std::cout<<" -i  --input   input file name   (Opt.)  <str>"<<std::endl;
            std::cout<<" -o  --output  output file name  (Opt.)  <str> "<<std::endl;
            std::cout<<" -h  --help    show help         (Opt.)"<<std::endl;
            std::cout<<std::endl;
            std::cout<<"Enter \"END\" to terminate the input from the standard input."<<std::endl;
            return 0;
        });
        exec.add_option(opt);
    }

    int result=exec.execute();
    if(result){
        std::cout<<"command line error (result "<<result<<')'<<std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::stringstream ss1;
    if(ifflag){
        std::ifstream ifs(ifstr);
        std::string str;
        while(getline(ifs,str)){
            for(char& a : str) if(a=='\r' or a=='\n') a=' ';
            ss1<<str<<' ';
        }

    }else{
        std::string str;
        std::cout<<">>> ";
        std::cin>>str;
        while(str!="END"){
            for(char& a : str) if(a=='\r' or a=='\n') a=' ';
            ss1<<str<<' ';
            std::cin>>str;
        }
    }

    if(offlag){
        std::ofstream ofs(ofstr);
        ofs<<ss1.str()<<std::endl;
    }else{
        if(!ifflag) std::cout<<std::endl;
        std::cout<<ss1.str()<<std::endl;
    }

    return 0;
}
