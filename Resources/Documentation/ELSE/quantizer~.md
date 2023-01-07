---
title: quantizer~
description: Quantize to steps

categories:
 - object

pdcategory: General

arguments:
- type: float
  description: step value
  default: 0, no approximation
- type: float
  description: approximation mode: 0 (round), 1 (int), 2 (floor), or 3 (ceil)
  default: 0

inlets:
  1st:
  - type: signal
    description: a float to be quantized
  2nd:
  - type: float/signal
    description: step value to quantize to

outlets:
  1st:
  - type: signal
    description: quantized signal

methods:
  - type: mode <float>
    description: sets approximarion mode <0, 1, 2, or 3>

---

[quantizer~] approximates a value to step values defined by the argument. There are 4 approximation modes: round (default), int, floor & ceil.
