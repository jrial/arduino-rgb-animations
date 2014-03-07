#!/usr/bin/env python

import png

reader = png.Reader('Images/Retro Mario 16x16.png')
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
            sensible_row.append([0, 0, 0])
        else:
            sensible_row.append([pixels[j*4],pixels[j*4+1],pixels[j*4+2]])
    out_rows.append(sensible_row)

# console = [hex(channel)[2:] if len(hex(channel)[2:]) == 2 else '0'+hex(channel)[2:] for row in out_rows for pixels in row for channel in pixels]
# for i in range(16):
#     out = ''
#     for j in range(16):
#         out += ''.join([console[48*i+3*j], console[48*i+3*j+1], console[48*i+3*j+2]]) + ' '
#     print out
#     print out
columns = [[row[i] for row in out_rows] for i in range(16)]
for i in range(8):
    columns[2*i-1].reverse()
flat = [channel for column in columns for pixels in column for channel in pixels]
out = 'PROGMEM char warning[768] = {\n'
for i in range(16):
    out += '    '
    for j in range(48):
        out += "%s, " % (flat[48*i+j])
    out += '\n'
out += '};\n'
print out
binary = bytearray(flat)
with open('out.bin', 'wb') as out:
    out.write(binary)
    print "Output %d bytes" % (len(binary))
# print binary
