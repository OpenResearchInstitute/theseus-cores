/* -*- c++ -*- */
/* Copyright 2015 Ettus Research
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * gr-ettus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gr-ettus; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_THESEUS_RFNOC_GENERIC_H
#define INCLUDED_THESEUS_RFNOC_GENERIC_H

#include <theseus/api.h>
#include <ettus/device3.h>
#include <ettus/rfnoc_block.h>
#include <uhd/stream.hpp>

namespace gr {
  namespace theseus {

    /*!
     * \brief Generic RFNoC block control class.
     *
     * This class is capable of controlling pretty much any RFNoC block.
     * All configuration must be done either via settings bus registers
     * or at initialization via stream args.
     *
     * To operate, it requires a valid device3 object in order to access
     * the RFNoC block on the FPGA. The block is chosen by providing at
     * least the block name, and, if necessary a device and block index.
     *
     * The stream args control the block signature, data type and number
     * of channels. The RFNoC stream signature is also queried from the
     * block at initialization and used to check if the stream signatures
     * match, and set vector lengths.
     *
     * For cases where this block is not restrictive enough, or additional
     * setter/getter methods need to be defined, a dedicated RFNoC block
     * class is recommended.
     */
    class THESEUS_API theseus_generic : virtual public gr::ettus::rfnoc_block
    {
     public:
      typedef boost::shared_ptr<theseus_generic> sptr;

      /*!
       * \param dev Device3 object
       * \param tx_stream_args Tx Stream Args
       * \param rx_stream_args Tx Stream Args
       * \param block_name Block name, e.g. "FFT"
       * \param block_select In case there's multiple blocks with that name, specify which one to choose (-1 for auto)
       * \param device_select If this Device3 object contains multiple USRPs, specify which device to choose (-1 for auto)
       */
      static sptr make(
          const gr::ettus::device3::sptr &dev,
          const ::uhd::stream_args_t &tx_stream_args,
          const ::uhd::stream_args_t &rx_stream_args,
          const std::string &block_name,
          const int block_select=-1,
          const int device_select=-1
      );
    };

  } // namespace theseus
} // namespace gr

#endif /* INCLUDED_THESEUS_RFNOC_GENERIC_H */

