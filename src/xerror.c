/**
 *
 * @file     xerror.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon May 05, 2003 10:41
 * @brief    Internal error functions
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2003 Aleix Conchillo Flaque
 *
 * SCEW is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SCEW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * @endif
 */

#include "xerror.h"

#include <pthread.h>

static pthread_key_t key_error;
static pthread_once_t key_once = PTHREAD_ONCE_INIT;

void
create_keys()
{
    scew_error* code = NULL;

    pthread_key_create(&key_error, free);

    code = (scew_error*) malloc(sizeof(scew_error));
    *code = scew_error_none;
    pthread_setspecific(key_error, code);
}

void
set_last_error(scew_error code)
{
    scew_error* old_code = NULL;
    scew_error* new_code = NULL;

    /* Initialize error code per thread */
    pthread_once(&key_once, create_keys);

    old_code = (scew_error*) pthread_getspecific(key_error);
    new_code = (scew_error*) malloc(sizeof(scew_error));
    free(old_code);
    pthread_setspecific(key_error, new_code);
}

scew_error
get_last_error()
{
    scew_error* code = NULL;

    code = (scew_error*) pthread_getspecific(key_error);
    if (code == NULL)
    {
        return scew_error_none;
    }
    return *code;
}
