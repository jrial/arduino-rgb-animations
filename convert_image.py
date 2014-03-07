#!/usr/bin/env python

import png

reader = png.Reader('Images/warning.png')
in_rows = reader.asRGBA8()[2]
rows_arr = []
out_rows = []
for row in in_rows:
    rows_arr.append(row)
for i in range(16):
    pixels = rows_arr[i]
    sensible_row = []
    for j in range(16):
        if not pixels[j*4+3]:
            sensible_row.append('0x000000')
        else:
            r = hex(pixels[j*4])[2:]
            g = hex(pixels[j*4+1])[2:]
            b = hex(pixels[j*4+2])[2:]
            if len(r) < 2:
                r = '0' + r
            if len(g) < 2:
                g = '0' + g
            if len(b) < 2:
                b = '0' + b
            sensible_row.append('0x' + r + g + b)
    out_rows.append(sensible_row)

# print out_rows
columns = [[row[i] for row in out_rows] for i in range(16)]
for i in range(8):
    columns[2*i-1].reverse()
out = 'uint32_t colours[256] = {\n    '
for column in columns:
    for pixel in column:
        out += pixel + ', '
    out += '\n    '
out = out[:-7]
out += '\n};'
print out
