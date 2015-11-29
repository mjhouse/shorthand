#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>


#ifndef CONFIG_H
#define CONFIG_H

namespace shorthand {
	
	class config {
		private: // variables
			std::map<std::string,std::string> options;
			std::string path;
			char delim;
		public:
			config(){
				}
			config(std::string p, char d){
				path = p;
				delim = d;
			}
			~config(){};
			
			int load(){
				//Load options into map from configuration file 
				std::fstream f(path, std::fstream::in);
				if(f.is_open()){
					std::string l;
					while(getline(f,l)){
						//remove commented portions
						int c = l.find('#');
						if(c!=std::string::npos){
							l = l.substr(0,c);
						}
						//remove spaces
						l.erase(std::remove_if(l.begin(), l.end(), [](char x){return std::isspace(x);}), l.end());
						
						//find before delim and after delim
						int d = l.find(delim);
						if(d!=std::string::npos){
							options[l.substr(0,d)] = l.substr(d+1);;
						}
					}
					f.close();
				}
				else
					return 0;
			}	
			
			int load(std::string s){
				path = s;
				return load();
			}	

//----------------------------------------------------------------------
//----------------------------------------------------------------------
			void print(){
				for(auto i : options){
					std::cout << i.first << "=>" << i.second << std::endl;
				}
			}
	};
}

#endif
