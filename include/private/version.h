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

#ifndef PRIVATE_VERSION_H_
#define PRIVATE_VERSION_H_

#define LSP_PLUGINS_COMP_DELAY_VERSION_MAJOR         1
#define LSP_PLUGINS_COMP_DELAY_VERSION_MINOR         0
#define LSP_PLUGINS_COMP_DELAY_VERSION_MICRO         3

#define LSP_PLUGINS_COMP_DELAY_VERSION  \
    LSP_MODULE_VERSION( \
        LSP_PLUGINS_COMP_DELAY_VERSION_MAJOR, \
        LSP_PLUGINS_COMP_DELAY_VERSION_MINOR, \
        LSP_PLUGINS_COMP_DELAY_VERSION_MICRO  \
    )

#endif /* PRIVATE_VERSION_H_ */
