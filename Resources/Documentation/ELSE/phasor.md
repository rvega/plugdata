---
title: phasor

description: Control phasor

categories:
- object

pdcategory:

arguments:
- description: frequency in hertz
  type: float
  default: 0
- description: initial phase offset
  type: float
  default: 0

inlets:
  1st:
  - type: float
    description: frequency in hz
  2nd:
  - type: float
    description: phase sync (ressets internal phase)

outlets:
  1st:
  - type: float
    description: "phase" value from 0 to 127

flags:
  - name: -rate <float>
    description: rate period in ms (default 1, min 0.1)

methods:
  - type: rate <float>
    description: rate period in ms

draft: false
---

This is like the [phasor~] but operates in a control rate (with a maximum resolution of 1 ms).
