/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Omid Alipourfard <g@omid.io>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _HEAVYHITTER_HASHMAP_LINEAR_PTR_H_
#define _HEAVYHITTER_HASHMAP_LINEAR_PTR_H_

#include "../../common.h"
#include "../../experiment.h"
#include "../../module.h"
#include "../../net.h"
#include "../../reporter.h"

#include "../../dss/hashmap_linear.h"

/*
 * Heavyhitter detection with a linear hash map
 *
 * This linear hash map implementation keeps keys and values separately, so the
 * 99th percentile performance is less affected by the separation of keys and
 * values.
 *
 */
typedef uint32_t Counter;
struct ModuleHeavyHitterHashmapLinearPtr {
    struct Module _m;

    uint32_t  size;
    unsigned  keysize;
    unsigned  elsize;
    unsigned  socket;

    unsigned stats_search;

    ReporterPtr reporter;
    HashMapLinearPtr hashmap_linear;

    HashMapLinearPtr hashmap_linear_ptr1;
    HashMapLinearPtr hashmap_linear_ptr2;

    uint8_t *values;

    uint8_t *vals1;
    uint8_t *vals2;

    uint32_t index;
};

typedef struct ModuleHeavyHitterHashmapLinearPtr* ModuleHeavyHitterHashmapLinearPPtr;

ModulePtr heavyhitter_hashmap_linear_ptr_init(ModuleConfigPtr);

void heavyhitter_hashmap_linear_ptr_delete(ModulePtr);
void heavyhitter_hashmap_linear_ptr_execute(ModulePtr, PortPtr, struct rte_mbuf **, uint32_t);
void heavyhitter_hashmap_linear_ptr_reset(ModulePtr);
void heavyhitter_hashmap_linear_ptr_stats(ModulePtr, FILE *);

#endif
