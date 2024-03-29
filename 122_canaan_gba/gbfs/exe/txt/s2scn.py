#!/usr/bin/env python3
import sys
import os

if len(sys.argv) < 3:
	print("four-nine/Izuho Saruta System-98 Scenario De-/Encoder")
	print("Usage: {} input.bin output.bin".format(sys.argv[0]))
	sys.exit(1)

print("s2scn... " + os.path.basename(sys.argv[1]))

with open(sys.argv[1], "rb") as f:
	data = f.read()

# It skips the first 0x100 bytes and XORs all remaining ones with 0x01.
dec = data[:0x100] + bytes([x ^ 0x01 for x in data[0x100:]])

with open(sys.argv[2], "wb") as f:
	f.write(dec)
