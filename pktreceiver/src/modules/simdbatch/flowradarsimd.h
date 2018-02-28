/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Yang Zhou <zhou.yang@pku.edu.cn>
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

#ifndef _SIMDBATCH_FLOWRADAR_SIMD_H
#define _SIMDBATCH_FLOWRADAR_SIMD_H

#include "../../common.h"
#include "../../experiment.h"
#include "../../module.h"
#include "../../net.h"
#include "common.h"


struct FlowRadarSimd {
    uint32_t size;
    uint16_t rowsize;
    uint16_t keysize;
    uint16_t elsize;

    rte_atomic32_t stats_search;

    uint32_t *rowbf;
    CellPtr rowcell;

    SimdPtr simd_ptr;

    uint32_t table[];
};

typedef struct FlowRadarSimd* FlowRadarSimdPtr; 

/* Create a new flowradarsimd ... row and key sizes are in multiples of 4 bytes -- for
 * better performance due to alignment */
FlowRadarSimdPtr flowradarsimd_create(uint32_t, uint16_t, uint16_t, int);

inline int  flowradarsimd_inc_fr(FlowRadarSimdPtr, void const *, uint32_t);
inline int  flowradarsimd_inc(FlowRadarSimdPtr, void const *);
inline void flowradarsimd_delete(FlowRadarSimdPtr);
inline void flowradarsimd_reset(FlowRadarSimdPtr);

uint32_t flowradarsimd_num_searches(FlowRadarSimdPtr);





typedef uint32_t Counter;

struct ModuleSimdBatchFlowRadarSimd {
    struct Module _m;

    uint32_t  size;
    unsigned  keysize;
    unsigned  elsize;
    unsigned  socket;

    unsigned stats_search;

    FlowRadarSimdPtr flowradarsimd;

    FlowRadarSimdPtr flowradarsimd_ptr1;
    FlowRadarSimdPtr flowradarsimd_ptr2;
};

typedef struct ModuleSimdBatchFlowRadarSimd* ModuleSimdBatchFlowRadarSimdPtr;

ModulePtr simdbatch_flowradarsimd_init(ModuleConfigPtr);

void simdbatch_flowradarsimd_delete(ModulePtr);
void simdbatch_flowradarsimd_execute(ModulePtr, PortPtr, struct rte_mbuf **, uint32_t);
void simdbatch_flowradarsimd_reset(ModulePtr);
void simdbatch_flowradarsimd_stats(ModulePtr, FILE *f);

#endif

