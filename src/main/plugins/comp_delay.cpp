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

#include <private/plugins/comp_delay.h>

namespace lsp
{
    namespace plugins
    {
        //---------------------------------------------------------------------
        // Plugin factory
        static const meta::plugin_t *plugins[] =
        {
            &meta::comp_delay_mono,
            &meta::comp_delay_stereo,
            &meta::comp_delay_x2_stereo
        };

        static plug::IModule *comp_delay_factory(const meta::plugin_t *meta)
        {
            return new comp_delay(meta);
        }

        static plug::Factory factory(comp_delay_factory, plugins, 3);

        //---------------------------------------------------------------------
        // Implementation
        comp_delay::comp_delay(const meta::plugin_t *meta):
            IModule(meta)
        {
            // Check plugin type
            nMode           = (meta == &meta::comp_delay_mono) ? CD_MONO :
                              (meta == &meta::comp_delay_stereo) ? CD_STEREO :
                              (meta == &meta::comp_delay_x2_stereo) ? CD_X2_STEREO :
                              CD_MONO;

            // Initialize other parameters
            vChannels       = NULL;
            bRamping        = false;

            pRamping        = NULL;

            pData           = NULL;
        }

        comp_delay::~comp_delay()
        {
            destroy();
        }

        void comp_delay::init(plug::IWrapper *wrapper)
        {
            IModule::init(wrapper);
        }

        void comp_delay::destroy()
        {
        }

        void comp_delay::update_sample_rate(long sr)
        {
        }

        void comp_delay::process(size_t samples)
        {
        }

        void comp_delay::dump(dspu::IStateDumper *v)
        {
        }

    }
}


