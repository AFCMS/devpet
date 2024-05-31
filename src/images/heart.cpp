/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "heart.hpp"

namespace images
{
    const unsigned char *heart_full[] = {static_heart_full_1, static_heart_full_2};
    const unsigned char *heart_half[] = {static_heart_half_1, static_heart_half_2};
    const unsigned char *heart_empty[] = {static_heart_empty_1, static_heart_empty_1};
    const unsigned char **heart[] = {heart_full, heart_half, heart_empty};
}
