/*

 WAV file re-sampler using SoX library.

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

// $Revision: 3515 $ $Date:: 2016-03-01 #$ $Author: serge $

#include <string>
#include <cstdint>

namespace wav_resample
{

bool resample( const std::string & infile, const std::string & outfile, std::string & error, uint32_t rate, uint32_t bps = 16 );

} // namespace wav_resample
