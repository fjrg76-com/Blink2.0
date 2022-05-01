/* Copyright (C) 
 * 2022 - fjrg76 at hotmail dot com
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#pragma once

#include <cstdint>
#include "hal/Blink/IBlinkable.hpp"

namespace fjrg76{
namespace components{
namespace Blink{
   /**
    * @brief This class allows a binary peripheral to blink just once, for a
    * certain number of cycles, or forever, without client intervention once
    * it was configured and started.
    *
    * This class also allows you to set the number of ticks the peripheral will
    * be in the ON and OFF states, independently. 
    */
   class Blink
   {
      public:

         /**
          * @brief Modes of operation
          */
         enum class eMode: uint8_t
         { 
            ONCE,       ///< The pin goes on its active state (ON) just once
            REPETITIVE, ///< Repeats the cycle (ON/OFF) n times
            FOREVER     ///< Repeats the cycle (ON/OFF) forever
         };
         
         /**
          * @brief Hardware peripheral's polarity
          */
         enum class ePolarity: uint8_t
         { 
            ACTIVE_HIGH, ///< The pin is in its active state when writing a logic 1
            ACTIVE_LOW   ///< The pin is in its active state when writing a logic 0
         };


         Blink( fjrg76::hal::Blink::IBlinkable& new_gpio );
         Blink& operator=(Blink&) = delete; ///< Copies are not allowed
         Blink(Blink&) = delete;            ///< Copy assignements are not allowed

         void begin( ePolarity polarity = ePolarity::ACTIVE_HIGH );
         void set( eMode mode, uint16_t ticks_on, uint16_t ticks_off = 0, uint16_t times = 1);
         void start();
         void stop();
         void state_machine();
         bool is_running();

         void always_on();
         void always_off();

      private:
         fjrg76::hal::Blink::IBlinkable& gpio;

         uint16_t ticks_onMOD{0};
         uint16_t ticks_offMOD{0};
         uint16_t ticks{0};

         eMode mode{eMode::ONCE};

         ePolarity polarity{ePolarity::ACTIVE_HIGH};

         uint16_t timesMOD{0};
         uint16_t times{0};
         bool running{false};
         uint8_t state{0};
   };




}
}
}
