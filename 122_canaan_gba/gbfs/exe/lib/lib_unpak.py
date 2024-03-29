#!/usr/bin/env python3
import sys
import os
import struct

if len(sys.argv) < 4:
	print("System-98 (four-nine/Izuho Saruta) Archive Unpacker")
	print("Usage: {} disk_X.cat disk_X.lib out_folder".format(sys.argv[0]))
	sys.exit(1)

def Decompress(cmpdata: bytes, maxsize: int) -> bytes:
	nameTable = [0] * 0x1000
	nameTblOfs = 1
	repeat_mask = 0
	check_bit = 0
	
	inpos = 0
	outpos = 0
	decdata = [0] * maxsize
	try:
		while True:
			check_bit *= 2
			check_bit &= 0xFF
			if check_bit == 0:
				repeat_mask = cmpdata[inpos];	inpos += 1
				check_bit = 1
			if (repeat_mask & check_bit) != 0:
				al = cmpdata[inpos];	inpos += 1
				decdata[outpos] = al;		outpos += 1
				nameTable[nameTblOfs] = al
				nameTblOfs += 1
				nameTblOfs &= 0xFFF
			else:
				# loc_10A63
				bl = cmpdata[inpos];	inpos += 1
				bh = cmpdata[inpos];	inpos += 1
				# loc_10AAB
				bx = (bh << 8) | (bl << 0)
				if bx == 0:
					break
				cx = (bl & 0x0F) + 3
				rep_ofs = bx >> 4
				
				# loc_10AC3
				for i in range(cx):
					al = nameTable[(rep_ofs + i) & 0xFFF]
					decdata[outpos] = al;	outpos += 1
					nameTable[nameTblOfs] = al
					nameTblOfs = (nameTblOfs + 1) & 0xFFF
	except Exception as e:
		print(e)
		print(inpos)
		print(outpos)
	
	return bytes(decdata)

def ReadCat(filename: str) -> bytes:
	with open(filename, "rb") as f:
		hdr = f.read(6)
		if hdr[0:3] != b"Cat":
			print("Not a CAT file: " + filename, file=sys.stderr)
		fcount = struct.unpack_from("<H", hdr, 0x04)[0]
		cmpdata = f.read()
	return hdr + Decompress(cmpdata, fcount * 0x16)

def ParseCat(data: bytes):
	fcount = struct.unpack_from("<H", data, 0x04)[0]	# 2-byte Little Endian, number of files
	
	inpos = 0x06
	toc = []
	for fileID in range(fcount):
		fname = data[inpos+0x00 : inpos+0x0C].decode("Shift-JIS")
		fname = fname.split('\0')[0]	# end at '\0' character (just for safety)
		fname = fname.rstrip(' ')	# strip trailing spaces
		(flags, fsize, ofs_start) = struct.unpack_from("<HII", data, inpos+0x0C)
		toc += [(fname, flags, fsize, ofs_start)]
		inpos += 0x16
	
	return toc

cat_data = ReadCat(sys.argv[1])

hFileLib = open(sys.argv[2], "rb")
lib_hdr = hFileLib.read(6)
if lib_hdr[0:3] != b"Lib":
	print("Not a LIB file: " + sys.argv[2], file=sys.stderr)

filelist = ParseCat(cat_data)

basepath = sys.argv[3]
os.makedirs(basepath, exist_ok=True)

print("Files: {}".format(len(filelist)))
for file_entry in filelist:
	(fname, flags, fsize, ofs_start) = file_entry
	print("    File: {} (lib ofs: 0x{:06X}, size: {}, compression: {})".format(fname, ofs_start, fsize, "yes" if (flags & 0x0001) else "no"))
	
	hFileLib.seek(0x06 + ofs_start)
	if flags & 0x0001:
		fdata = hFileLib.read(4)
		dec_size = struct.unpack("<I", fdata)[0]	# 4-byte Little Endian, decompressed size
		fdata = hFileLib.read(fsize - 4)
		fdata = Decompress(fdata, dec_size)
	else:
		fdata = hFileLib.read(fsize)
	
	filepath = os.path.join(basepath, fname)
	with open(filepath, "wb") as f:
		f.write(fdata)
