/*

Get WAV file duration.

Copyright (C) 2014 Sergey Kolevatov

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


// $Revision: 9631 $ $Date:: 2018-08-08 #$ $Author: serge $

#ifndef WAV_TOOLS__GET_WAV_DURATION_H
#define WAV_TOOLS__GET_WAV_DURATION_H

#include <string>               // std::string

namespace wav_tools {

double get_wav_duration( const std::string & filename );

} // namespace wav_tools

#endif  // WAV_TOOLS__GET_WAV_DURATION_H
