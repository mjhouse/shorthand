#ifndef UTILITIES_H
#define UTILITIES_H

/*

Copyright (C) 2015  Michael House

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */

#include <vector>
#include <string>
#include "list.h"

namespace shorthand {

/*
 * SPLIT:
 * 		returns a vector<std::string> object containing given string split on delimitor
 * 		if no delimitor is given, splits on space.
 */
	std::vector<std::string> split(std::string s, std::string d=" "){
		std::vector<std::string> tmp;
		while(s.find(d)!=std::string::npos){
			tmp.push_back(s.substr(0,s.find(d)));
			s.erase(0, s.find(d) + d.length());
		}
		tmp.push_back(s);
		return tmp;
	}

}

#endif
