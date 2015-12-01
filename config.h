#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>


#ifndef CONFIG_H
#define CONFIG_H

namespace shorthand {
	/*
	 * WHAT I NEED:
	 * 		i need this to be simple and easy to use- so only a few commands
	 * 		will be used to implement a config instance in texteditor.
	 * 
	 * 		1. 	I declare shorthand::config tmp blah blah blah
	 * 		
	 * 		2. 	I feed it a bunch of search paths and a file name and a delim
	 * 		
	 * 		4. 	I put in an option and the value of that option gets returned,
	 * 			unfortunately, I have no idea how to handle different types
	 * 			of values. Options could be string, int, bool, whatever. but
	 * 			they all go into map as strings.
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 */
	 
	class config {
		private: // PRIVATE FUNCTIONS
//----------------------------------------------------------------------
// UTILITIES
//----------------------------------------------------------------------		
			bool exists(std::string p){
				std::fstream f(p,std::fstream::in);
				return (bool)f;
			}
			
			std::string slash(std::string s){
				if (!s.empty() && s.back() != '/')
					s += '/';
				return s;
			}
//----------------------------------------------------------------------
/* LOAD:
 *		loads options into map from config file at location "path"
 */
//----------------------------------------------------------------------
			int fetch(std::string path){ 
				std::fstream f(path, std::fstream::in);
				if(f.is_open()){
					std::string l;
					while(getline(f,l)){
						// REMOVE COMMENTS -----------------------------
						int c = l.find('#');
						if(c!=std::string::npos){
							l = l.substr(0,c);
						}
						// REMOVE SPACES -------------------------------
						l.erase(std::remove_if(l.begin(), l.end(), [](char x){return std::isspace(x);}), l.end());
						
						// FIND KEY/VALUE ------------------------------
						int d = l.find(delim);
						if(d!=std::string::npos){
							options[l.substr(0,d)] = l.substr(d+1);;
						}
					}
					f.close();
					return 1;
				}
				else
					return 0;
			}
//----------------------------------------------------------------------
/* PRIVATE VARIABLES
 * 	paths: holds paths to search for the given config file
 *  name: holds the name of the config file 
 * 
 * 	map: holds the key/value pairs from the options file
 *  delim: holds the expected delimiting character
 */
//----------------------------------------------------------------------
		private: 
			std::vector<std::string> paths;
			std::string name;
			
			std::map<std::string,std::string> options;
			char delim;
			int found;
		public:
//----------------------------------------------------------------------
// CONSTRUCTORS		
			config(){};
			
			// OVERLOADED CONSTRUCTOR ----------------------------------
			config(
				std::vector<std::string> p,
				std::string n,
				char d)
			{
				paths = p;
				name = n;
				delim = d;
			}
			//----------------------------------------------------------
			~config(){};
//----------------------------------------------------------------------
// PUBLIC FUNCTIONS
//----------------------------------------------------------------------
	
	//------------------------------------------------------------------
	// MAIN FUNCTIONS
	//------------------------------------------------------------------
			
			//----------------------------------------------------------
			// LOAD
			//----------------------------------------------------------
			int load(){
				for(auto i : paths){ // foreach element
						std::string full = slash(i)+name;
						if(exists(full)){
							fetch(full);
							return 1; // found first
						}
				}
				return 0; // not found
			}
			
			// OVERLOADED ----------------------------------------------
			int load(
				std::vector<std::string> p,
				std::string n,
				char d)
			{
				paths = p;
				name = n;
				delim = d;
				
				return load();
			}
			
			//----------------------------------------------------------
			// RETURN VALUES
			//----------------------------------------------------------
			// (work on these- they're not great)
			//----------------------------------------------------------
			std::string str_value_of(std::string s){
				return options[s];
			}
			
			int int_value_of(std::string s){
				int v = atoi(options[s].c_str());
				return v;
			}
			
			bool bool_value_of(std::string s){
				std::string v = options[s];
				if(v.compare("true") == 0)
					return true;
				else
					return false;
			}
			

	//------------------------------------------------------------------
	// GET / SET FUNCTIONS
	//------------------------------------------------------------------
				
			//----------------------------------------------------------
			// GET/SET PATH
			//----------------------------------------------------------
			
			int set_paths(std::vector<std::string> p){
				paths = p;
				return 1;
			}

			std::vector<std::string> get_paths(){
				return paths;
			}
			
			//----------------------------------------------------------
			// GET/SET FILE NAME
			//----------------------------------------------------------
			
			int set_file_name(std::string s){
				name = s;
				return 1;
			}

			std::string get_file_name(){
				return name;
			}
			
			//----------------------------------------------------------
			// GET/SET DELIM CHAR
			//----------------------------------------------------------
			
			int set_delim(char c){
				delim = c;
				return 1;
			}

			char get_delim(){
				return delim;
			}
//----------------------------------------------------------------------
// PRINT: going away at some point, but useful for testing
//----------------------------------------------------------------------
			void print(){
				for(auto i : options){
					std::cout << i.first << "=>" << i.second << std::endl;
				}
			}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
	};
}

#endif
