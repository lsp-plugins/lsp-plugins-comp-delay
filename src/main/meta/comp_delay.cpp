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

#include <lsp-plug.in/plug-fw/meta/ports.h>
#include <lsp-plug.in/shared/meta/developers.h>
#include <private/meta/comp_delay.h>

#define LSP_PLUGINS_COMP_DELAY_VERSION_MAJOR         1
#define LSP_PLUGINS_COMP_DELAY_VERSION_MINOR         0
#define LSP_PLUGINS_COMP_DELAY_VERSION_MICRO         10

#define LSP_PLUGINS_COMP_DELAY_VERSION  \
    LSP_MODULE_VERSION( \
        LSP_PLUGINS_COMP_DELAY_VERSION_MAJOR, \
        LSP_PLUGINS_COMP_DELAY_VERSION_MINOR, \
        LSP_PLUGINS_COMP_DELAY_VERSION_MICRO  \
    )

namespace lsp
{
    namespace meta
    {
        //-------------------------------------------------------------------------
        // Compensation delay
        static const port_item_t comp_delay_modes[] =
        {
            { "Samples",    "comp_delay.samples"    },
            { "Distance",   "comp_delay.distance"   },
            { "Time",       "comp_delay.time"       },
            { NULL, NULL }
        };

        static const port_t comp_delay_mono_ports[] =
        {
            // Input audio ports
            AUDIO_INPUT_MONO,

            // Output audio ports
            AUDIO_OUTPUT_MONO,

            // Input controls
            BYPASS,

            COMBO("mode", "Mode", 0, comp_delay_modes),
            SWITCH("ramp", "Ramping", 0.0f),
            INT_CONTROL("samp", "Samples", U_SAMPLES, comp_delay::SAMPLES),
            INT_CONTROL("m", "Meters", U_M, comp_delay::METERS),
            CONTROL("cm", "Centimeters", U_CM, comp_delay::CENTIMETERS),
            CONTROL("t", "Temperature", U_DEG_CEL, comp_delay::TEMPERATURE),
            CONTROL("time", "Time", U_MSEC, comp_delay::TIME),
            DRY_GAIN(0.0f),
            WET_GAIN(1.0f),

            OUT_GAIN,

            // Output controls
            METER_MINMAX("d_t", "Delay time", U_HZ, 0.0f, comp_delay::DELAY_OUT_MAX_TIME),
            METER_MINMAX("d_s", "Delay samples", U_SAMPLES, 0.0f, comp_delay::DELAY_OUT_MAX_SAMPLES),
            METER_MINMAX("d_d", "Delay distance", U_CM, 0.0f, comp_delay::DELAY_OUT_MAX_DISTANCE),

            PORTS_END
        };

        static const port_t comp_delay_stereo_ports[] =
        {
            // Input audio ports
            AUDIO_INPUT_LEFT,
            AUDIO_INPUT_RIGHT,

            // Output audio ports
            AUDIO_OUTPUT_LEFT,
            AUDIO_OUTPUT_RIGHT,

            // Input controls
            BYPASS,

            COMBO("mode", "Mode", 0, comp_delay_modes),
            SWITCH("ramp", "Ramping", 0.0f),
            INT_CONTROL("samp", "Samples", U_SAMPLES, comp_delay::SAMPLES),
            INT_CONTROL("m", "Meters", U_M, comp_delay::METERS),
            CONTROL("cm", "Centimeters", U_CM, comp_delay::CENTIMETERS),
            CONTROL("t", "Temperature", U_DEG_CEL, comp_delay::TEMPERATURE),
            CONTROL("time", "Time", U_MSEC, comp_delay::TIME),
            DRY_GAIN(0.0f),
            WET_GAIN(1.0f),

            OUT_GAIN,

            // Output controls
            METER_MINMAX("d_t", "Delay time", U_HZ, 0.0f, comp_delay::DELAY_OUT_MAX_TIME),
            METER_MINMAX("d_s", "Delay samples", U_SAMPLES, 0.0f, comp_delay::DELAY_OUT_MAX_SAMPLES),
            METER_MINMAX("d_d", "Delay distance", U_CM, 0.0f, comp_delay::DELAY_OUT_MAX_DISTANCE),

            PORTS_END
        };

        static const port_t comp_delay_x2_stereo_ports[] =
        {
            // Input audio ports
            AUDIO_INPUT_LEFT,
            AUDIO_INPUT_RIGHT,

            // Output audio ports
            AUDIO_OUTPUT_LEFT,
            AUDIO_OUTPUT_RIGHT,

            // Input controls
            BYPASS,

            COMBO("mode_l", "Mode L", 0, comp_delay_modes),
            SWITCH("ramp_l", "Ramping L", 0.0f),
            INT_CONTROL("samp_l", "Samples L", U_SAMPLES, comp_delay::SAMPLES),
            INT_CONTROL("m_l", "Meters L", U_M, comp_delay::METERS),
            CONTROL("cm_l", "Centimeters L", U_CM, comp_delay::CENTIMETERS),
            CONTROL("t_l", "Temperature L", U_DEG_CEL, comp_delay::TEMPERATURE),
            CONTROL("time_l", "Time L", U_MSEC, comp_delay::TIME),
            DRY_GAIN_L(0.0f),
            WET_GAIN_L(1.0f),

            COMBO("mode_r", "Mode R", 0, comp_delay_modes),
            SWITCH("ramp_r", "Ramping R", 0.0f),
            INT_CONTROL("samp_r", "Samples R", U_SAMPLES, comp_delay::SAMPLES),
            INT_CONTROL("m_r", "Meters R", U_M, comp_delay::METERS),
            CONTROL("cm_r", "Centimeters R", U_CM, comp_delay::CENTIMETERS),
            CONTROL("t_r", "Temperature R", U_DEG_CEL, comp_delay::TEMPERATURE),
            CONTROL("time_r", "Time R", U_MSEC, comp_delay::TIME),
            DRY_GAIN_R(0.0f),
            WET_GAIN_R(1.0f),

            OUT_GAIN,

            // Output controls
            METER_MINMAX("d_t_l", "Delay time L", U_HZ, 0.0f, comp_delay::DELAY_OUT_MAX_TIME),
            METER_MINMAX("d_s_l", "Delay samples L", U_SAMPLES, 0.0f, comp_delay::DELAY_OUT_MAX_SAMPLES),
            METER_MINMAX("d_d_l", "Delay distance L", U_CM, 0.0f, comp_delay::DELAY_OUT_MAX_DISTANCE),

            METER_MINMAX("d_t_r", "Delay time R", U_HZ, 0.0f, comp_delay::DELAY_OUT_MAX_TIME),
            METER_MINMAX("d_s_r", "Delay samples R", U_SAMPLES, 0.0f, comp_delay::DELAY_OUT_MAX_SAMPLES),
            METER_MINMAX("d_d_r", "Delay distance R", U_CM, 0.0f, comp_delay::DELAY_OUT_MAX_DISTANCE),

            PORTS_END
        };

        static const int plugin_classes[]       = { C_DELAY, -1 };
        static const int clap_features_mono[]   = { CF_AUDIO_EFFECT, CF_DELAY, CF_MONO, -1 };
        static const int clap_features_stereo[] = { CF_AUDIO_EFFECT, CF_DELAY, CF_STEREO, -1 };

        const meta::bundle_t comp_delay_bundle =
        {
            "comp_delay",
            "Compensation Delay",
            B_DELAYS,
            "j-rNb409GYg",
            "This plugin allows one to add short delay to compensate the phase offset\nrelatively to other channels. The main idea is to add some delay\nof the signal recorded by set of microphones placed at different\npositions and distances from the sound source."
        };

        const plugin_t comp_delay_mono =
        {
            "Verzögerungsausgleicher Mono",
            "Delay Compensator Mono",
            "VA1M",
            &developers::v_sadovnikov,
            "comp_delay_mono",
            LSP_LV2_URI("comp_delay_mono"),
            LSP_LV2UI_URI("comp_delay_mono"),
            "jav8",
            LSP_LADSPA_COMP_DELAY_BASE + 0,
            LSP_LADSPA_URI("comp_delay_mono"),
            LSP_CLAP_URI("comp_delay_mono"),
            LSP_PLUGINS_COMP_DELAY_VERSION,
            plugin_classes,
            clap_features_mono,
            E_DUMP_STATE,
            comp_delay_mono_ports,
            "delay/comp/mono.xml",
            NULL,
            mono_plugin_port_groups,
            &comp_delay_bundle
        };

        const plugin_t comp_delay_stereo =
        {
            "Verzögerungsausgleicher Stereo",
            "Delay Compensator Stereo",
            "VA1S",
            &developers::v_sadovnikov,
            "comp_delay_stereo",
            LSP_LV2_URI("comp_delay_stereo"),
            LSP_LV2UI_URI("comp_delay_stereo"),
            "qpwr",
            LSP_LADSPA_COMP_DELAY_BASE + 1,
            LSP_LADSPA_URI("comp_delay_stereo"),
            LSP_CLAP_URI("comp_delay_stereo"),
            LSP_PLUGINS_COMP_DELAY_VERSION,
            plugin_classes,
            clap_features_stereo,
            E_DUMP_STATE,
            comp_delay_stereo_ports,
            "delay/comp/stereo.xml",
            NULL,
            stereo_plugin_port_groups,
            &comp_delay_bundle
        };

        const plugin_t comp_delay_x2_stereo =
        {
            "Verzögerungsausgleicher x2 Stereo",
            "Delay Compensator x2 Stereo",
            "VA2S",
            &developers::v_sadovnikov,
            "comp_delay_x2_stereo",
            LSP_LV2_URI("comp_delay_x2_stereo"),
            LSP_LV2UI_URI("comp_delay_x2_stereo"),
            "fwd3",
            LSP_LADSPA_COMP_DELAY_BASE + 2,
            LSP_LADSPA_URI("comp_delay_x2_stereo"),
            LSP_CLAP_URI("comp_delay_x2_stereo"),
            LSP_PLUGINS_COMP_DELAY_VERSION,
            plugin_classes,
            clap_features_stereo,
            E_DUMP_STATE,
            comp_delay_x2_stereo_ports,
            "delay/comp/x2_stereo.xml",
            NULL,
            stereo_plugin_port_groups,
            &comp_delay_bundle
        };
    } /* namespace meta */
} /* namespace lsp */


