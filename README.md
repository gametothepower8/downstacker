# downstacker
The bot aims to clear 10 garbage lines with small numebr of pieces.
Board size = 22 (vertical) x 10 (horizontal)
Garbage lines: 1 hole in corresponding row.
Input format:
Line 1: Seed (any 32-bit signed integer)
Line 2: a non-empty string matching regex (IOTJLSZ)*, indicating the piece sequence.
Line 3: 10 integers bewteen 0 to 9 (0 = left, 9 = right), indicating positions of the holes in garabage lines from bottom to top
