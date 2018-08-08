/*

 Example.

 Copyright (C) 2016 Sergey Kolevatov

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 9632 $ $Date:: 2018-08-08 #$ $Author: serge $

#include "wav_resample.h"       // resample
#include "get_wav_duration.h"   // get_wav_duration()

#include <iostream>

int main( int argc, char* argv[] )
{
    if( argc != 3 )
    {
        std::cout << "Usage: example <input.wav> <output.wav>" << std::endl;
        return 0;
    }

    std::cout << "input : " << argv[1] << "\n"
            <<   "output: " << argv[2] << "\n";

    std::string error;

    auto b = wav_tools::resample( argv[1], argv[2], error, 8000 );

    if( b )
    {
        auto duration = wav_tools::get_wav_duration( argv[1] );

        std::cout << "OK (" << duration << " sec)\n";
    }
    else
    {
        std::cout << "ERROR: " << error << "\n";
    }

    return 0;
}
