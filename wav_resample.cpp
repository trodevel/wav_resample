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

#include <sox.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "wav_resample.h"       // self

namespace wav_resample
{

bool resample( const std::string & infile, const std::string & outfile, std::string & error, uint32_t rate, uint32_t bps )
{
    char * args[10];

    assert( sox_init() == SOX_SUCCESS );

    // input and output files
    sox_format_t * in = sox_open_read( infile.c_str(), NULL, NULL, NULL );

    if( in == nullptr )
    {
        error = "cannot open input file " + infile;
        return false;
    }

    sox_format_t *out= (sox_format_t *) malloc(sizeof (sox_format_t));

    memcpy( out, in, sizeof(sox_format_t) );

    out->encoding.encoding = SOX_ENCODING_SIGN2;
    out->encoding.bits_per_sample = bps;
    out->signal.rate = rate;
    out->signal.precision = 16;
    out->signal.length = SOX_UNSPEC;

    out = sox_open_write( outfile.c_str(), &out->signal, &out->encoding, NULL, NULL, NULL);

    if( out == nullptr )
    {
        error = "cannot open output file " + outfile;
        return false;
    }

    sox_effects_chain_t * chain = sox_create_effects_chain( &in->encoding, &out->encoding );

    {
        sox_effect_t * e = sox_create_effect( sox_find_effect( "input" ) );

        args[0] = (char *)in;
        assert( sox_effect_options(e, 1, args) == SOX_SUCCESS );
        assert( sox_add_effect(chain, e, &in->signal, &in->signal) == SOX_SUCCESS );

        free( e );
    }

    if( in->signal.rate != out->signal.rate )
    {
        sox_effect_t * e = sox_create_effect( sox_find_effect( "rate" ) );
        assert( sox_effect_options(e, 0, NULL) == SOX_SUCCESS );
        e->handler.flags |= SOX_EFF_LENGTH;

        assert( sox_add_effect(chain, e, &in->signal, &out->signal) == SOX_SUCCESS );
        free( e );
    }

    if( in->signal.channels != out->signal.channels )
    {
        sox_effect_t * e = sox_create_effect( sox_find_effect( "channels" ) );
        assert( sox_effect_options(e, 0, NULL) == SOX_SUCCESS );
        assert( sox_add_effect(chain, e, &in->signal, &out->signal) == SOX_SUCCESS );
        free( e );
    }

    {
        sox_effect_t * e = sox_create_effect( sox_find_effect( "output" ) );
        args[0] = (char *)out, assert( sox_effect_options(e, 1, args) == SOX_SUCCESS );
        assert( sox_add_effect(chain, e, &in->signal, &out->signal) == SOX_SUCCESS );
        free( e );
    }

    sox_flow_effects( chain, NULL, NULL );

    sox_delete_effects_chain( chain );
    sox_close( out );
    sox_close( in );
    sox_quit();

    return true;
}

} // namespace wav_resample
