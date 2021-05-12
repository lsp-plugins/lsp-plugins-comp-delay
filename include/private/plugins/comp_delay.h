/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins-comp-delay
 * Created on: 25 нояб. 2020 г.
 *
 * lsp-plugins-comp-delay is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins-comp-delay is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins-comp-delay. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PRIVATE_PLUGINS_COMP_DELAY_H_
#define PRIVATE_PLUGINS_COMP_DELAY_H_

#include <lsp-plug.in/dsp-units/util/Delay.h>
#include <lsp-plug.in/dsp-units/ctl/Bypass.h>
#include <lsp-plug.in/plug-fw/plug.h>
#include <private/meta/comp_delay.h>

namespace lsp
{
    namespace plugins
    {
        /**
         * Base class for the latency compensation delay
         */
        class comp_delay: public plug::Module
        {
            private:
                comp_delay & operator = (const comp_delay &);

            protected:
                enum mode_t
                {
                    CD_MONO,
                    CD_STEREO,
                    CD_X2_STEREO
                };

                typedef struct channel_t
                {
                    dspu::Delay         sLine;              // Delay line
                    dspu::Bypass        sBypass;            // Bypass

                    ssize_t             nDelay;             // Actual delay
                    ssize_t             nNewDelay;          // New delay
                    size_t              nMode;              // Delay mode
                    bool                bRamping;           // Ramping flag
                    float               fDry;               // Dry control
                    float               fWet;               // Wet control

                    plug::IPort        *pIn;                // Input port
                    plug::IPort        *pOut;               // Output port
                    plug::IPort        *pMode;              // Mode port
                    plug::IPort        *pRamping;           // Ramping
                    plug::IPort        *pSamples;           // Samples port
                    plug::IPort        *pMeters;            // Distance meters
                    plug::IPort        *pCentimeters;       // Distance centimeters
                    plug::IPort        *pTemperature;       // Temperature port
                    plug::IPort        *pTime;              // Time port
                    plug::IPort        *pDry;               // Dry control
                    plug::IPort        *pWet;               // Wet control

                    plug::IPort        *pOutTime;           // Output time
                    plug::IPort        *pOutSamples;        // Output samples
                    plug::IPort        *pOutDistance;       // Output distance
                } channel_t;

            protected:
                size_t              nMode;              // mode
                channel_t          *vChannels;          // Delay channels
                float              *vBuffer;            // Temporary buffer

                plug::IPort        *pBypass;            // Bypass
                plug::IPort        *pGainOut;           // Output gain

                uint8_t            *pData;              // Allocated data

            public:
                explicit comp_delay(const meta::plugin_t *meta);
                virtual ~comp_delay();

                virtual void        init(plug::IWrapper *wrapper);
                void                destroy();

            public:

                virtual void        update_sample_rate(long sr);
                virtual void        update_settings();
                virtual void        process(size_t samples);
                virtual void        dump(dspu::IStateDumper *v) const;
        };
    }
}


#endif /* PRIVATE_PLUGINS_COMP_DELAY_H_ */

