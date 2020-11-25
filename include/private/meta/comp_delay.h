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

#ifndef PRIVATE_META_COMP_DELAY_H_
#define PRIVATE_META_COMP_DELAY_H_

#include <lsp-plug.in/plug-fw/meta/types.h>
#include <lsp-plug.in/plug-fw/const.h>

namespace lsp
{
    //-------------------------------------------------------------------------
    // Compensation delay metadata
    namespace meta
    {
        typedef struct comp_delay_t
        {
            static const float  METERS_MIN          = 0.0f;
            static const float  METERS_MAX          = 200.0f;
            static const float  METERS_DFL          = 0.0f;
            static const float  METERS_STEP         = 1.0f;

            static const float  CENTIMETERS_MIN     = 0.0f;
            static const float  CENTIMETERS_MAX     = 100.0f;
            static const float  CENTIMETERS_DFL     = 0.0f;
            static const float  CENTIMETERS_STEP    = 0.1f;

            static const float  SAMPLES_MIN         = 0.0f;
            static const float  SAMPLES_MAX         = 10000.0f;
            static const float  SAMPLES_DFL         = 0.0f;
            static const float  SAMPLES_STEP        = 1.0f;

            static const float  TIME_MIN            = 0.0f;
            static const float  TIME_MAX            = 1000.0f;
            static const float  TIME_DFL            = 0.0f;
            static const float  TIME_STEP           = 0.01f;

            static const float  TEMPERATURE_MIN     = -60.0f;
            static const float  TEMPERATURE_MAX     = +60.0f;
            static const float  TEMPERATURE_DFL     = 20.0f;
            static const float  TEMPERATURE_STEP    = 0.1f;

            static const float  DELAY_OUT_MAX_TIME      = 1000 /* TIME_MAX [ms] */;
            static const float  DELAY_OUT_MAX_SAMPLES   = 1000 /* TIME_MAX [ms] */ * 0.001 /* [ s/ms ] */ * MAX_SAMPLE_RATE /* [samples / s] */;
            static const float  DELAY_OUT_MAX_DISTANCE  = 1000 /* TIME_MAX [ms] */ * 0.001 /* [ s/ms ] */ * MAX_SOUND_SPEED /* [m/s] */ * 100 /* [cm / m ] */;

            enum modes
            {
                M_SAMPLES,
                M_DISTANCE,
                M_TIME
            };
        } comp_delay_t;

        // Plugin metadata
        extern const plugin_t comp_delay_mono;
        extern const plugin_t comp_delay_stereo;
        extern const plugin_t comp_delay_x2_stereo;
    }
}

#endif /* PRIVATE_META_COMP_DELAY_H_ */
