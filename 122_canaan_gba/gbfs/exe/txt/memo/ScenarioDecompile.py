#!/usr/bin/env python3
import sys
import os
import struct
import typing
import argparse
import nec_jis_conv


# Scene Command Parameter Types
SCPT_INT = 0x01		# 2-byte integer
SCPT_BYTE = 0x02	# "byte" (2-byte parameter, high byte ignored)
SCPT_LONG = 0x03	# 4-byte integer
SCPT_ILVAR = 0x0F	# 2-byte/4-byte integer, based on previous register ID
SCPT_DATA1 = 0x10	# data pointer (1-byte groups)
SCPT_DATA2 = 0x11	# data pointer (2-byte groups)
SCPT_STR = 0x12		# string pointer
SCPT_FNAME = 0x13	# file path pointer
SCPT_JUMP = 0x14	# jump destination pointer
SCPT_REG_INT = 0x80	# register: integer
SCPT_REG_LNG = 0x81	# register: long
SCPT_REG_IL = 0x82	# register: integer/long
SCPT_REG_STR = 0x83	# register: string

SCPT_MASK = 0xF0
SCPTM_VAL = 0x00	# immediate value
SCPTM_PTR = 0x10	# pointer
SCPTM_REG = 0x80	# register

SC_EXEC_END = 0x01	# terminate script execution here
SC_EXEC_SPC = 0xFF	# special handling

LBLFLG_UNUSED = 0x01
LBLFLG_MENU = 0x10

SCENE_CMD_LIST = {
	0x00: ("DOSEXIT", [], SC_EXEC_END),
	0x01: (None     , []),
	0x02: ("IMGLOAD", [SCPT_INT, SCPT_INT, SCPT_BYTE, SCPT_BYTE, SCPT_FNAME, SCPT_BYTE]),
	0x03: ("TBOPEN" , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT]),
	0x04: ("TBCLOSE", [SCPT_INT]),
	0x05: ("TBCLEAR", [SCPT_INT]),
	0x06: ("PALAPL" , []),
	0x07: ("PALBW"  , [SCPT_INT, SCPT_INT]),
	0x08: ("PALFADE", [SCPT_INT, SCPT_INT]),
	0x09: ("PALLCKT", [SCPT_BYTE]),
	0x0A: ("JP"     , [SCPT_JUMP], SC_EXEC_END),
	0x0B: ("CMPR"   , [SCPT_REG_INT, SCPT_REG_INT]),
	0x0C: ("CMPI"   , [SCPT_REG_INT, SCPT_INT]),
	0x0D: ("JEQ"    , [SCPT_JUMP]),
	0x0E: ("JLT"    , [SCPT_JUMP]),
	0x0F: ("JGT"    , [SCPT_JUMP]),
	0x10: ("JGE"    , [SCPT_JUMP]),
	0x11: ("JLE"    , [SCPT_JUMP]),
	0x12: ("JNE"    , [SCPT_JUMP]),
	0x13: ("JTBL"   , [SCPT_REG_INT], SC_EXEC_SPC),
	0x14: ("PCOLSET", [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x15: ("PRINT"  , [SCPT_BYTE, SCPT_STR]),
	0x16: ("CMD16"  , [SCPT_INT, SCPT_INT, SCPT_DATA1]),
	0x17: (None     , []),
	0x18: ("MOVI"   , [SCPT_REG_IL, SCPT_ILVAR]),
	0x19: ("MOVR"   , [SCPT_REG_IL, SCPT_REG_IL]),
	0x1A: ("BGMPLAY", [SCPT_FNAME]),
	0x1B: ("BGMFADE", []),
	0x1C: ("BGMSTOP", []),
	0x1D: ("BGMODEG", [SCPT_REG_INT]),
	0x1E: ("CMD1E"  , [SCPT_REG_INT]),
	0x1F: ("LDSCENE", [SCPT_FNAME], SC_EXEC_END),
	0x20: ("GV02"   , []),
	0x21: ("WAIT"   , [SCPT_REG_INT]),
	0x22: ("GFX22"  , [SCPT_REG_INT]),
	0x23: (None     , []),
	0x24: ("ADDI"   , [SCPT_REG_IL, SCPT_ILVAR]),
	0x25: ("SUBI"   , [SCPT_REG_IL, SCPT_ILVAR]),
	0x26: ("TXCLR1" , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_BYTE]),
	0x27: ("ADDR"   , [SCPT_REG_IL, SCPT_REG_IL]),
	0x28: ("SUBR"   , [SCPT_REG_IL, SCPT_REG_IL]),
	0x29: ("XYREAD" , [SCPT_REG_INT, SCPT_INT, SCPT_INT]),
	0x2A: ("XYWRT"  , [SCPT_REG_INT, SCPT_INT, SCPT_INT]),
	0x2B: (None     , []),
	0x2C: (None     , []),
	0x2D: ("REGCLR" , [SCPT_REG_INT, SCPT_REG_INT]),
	0x2E: (None     , []),
	0x2F: ("CMD2F"  , [SCPT_BYTE, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_BYTE, SCPT_INT, SCPT_INT]),
	0x30: (None     , []),
	0x31: (None     , []),
	0x32: ("PRINTR" , [SCPT_BYTE, SCPT_REG_INT]),
	0x33: ("PA4GET" , [SCPT_REG_INT]),
	0x34: ("PA4SET" , [SCPT_REG_INT]),
	0x35: ("TXFILL" , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT]),
	0x36: ("GFX36"  , []),
	0x37: ("XYFLOAD", [SCPT_FNAME]),
	0x38: ("ANDR"   , [SCPT_REG_INT, SCPT_REG_INT]),
	0x39: ("ORR"    , [SCPT_REG_INT, SCPT_REG_INT]),
	0x3A: ("GFX3A"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x3B: ("GFX3B"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x3C: ("TXCLR2" , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_BYTE]),
	0x3D: ("MULR"   , [SCPT_REG_IL, SCPT_REG_IL]),
	0x3E: ("DIVR"   , [SCPT_REG_IL, SCPT_REG_IL]),
	0x3F: ("CMD3F"  , [SCPT_REG_INT, SCPT_REG_INT]),
	0x40: ("MENUSEL", [SCPT_REG_INT, SCPT_REG_INT, SCPT_DATA2, SCPT_JUMP], SC_EXEC_SPC),
	0x41: ("CMD41"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_JUMP]),
	0x42: ("CMD42"  , [SCPT_BYTE]),
	0x43: ("CMD43"  , [SCPT_REG_INT, SCPT_REG_INT]),
	0x44: (None     , []),
	0x45: (None     , []),
	0x46: (None     , []),
	0x47: (None     , []),
	0x48: (None     , []),
	0x49: (None     , []),
	0x4A: ("REGFSAV", [SCPT_BYTE, SCPT_FNAME]),
	0x4B: ("REGFLD" , [SCPT_BYTE, SCPT_FNAME]),
	0x4C: ("CMD4C"  , [SCPT_REG_INT, SCPT_REG_INT]),
	0x4D: ("BGMMEAS", [SCPT_REG_INT]),
	0x4E: ("SFXSSG" , [SCPT_BYTE]),
	0x4F: ("SFXFM"  , [SCPT_BYTE]),
	0x50: ("BGMSTAT", [SCPT_REG_INT]),
	0x51: ("ANDI"   , [SCPT_REG_INT, SCPT_INT]),
	0x52: ("ORI"    , [SCPT_REG_INT, SCPT_INT]),
	0x53: ("STRCAT" , [SCPT_REG_STR, SCPT_REG_STR]),
	0x54: ("CALL"   , [SCPT_JUMP]),
	0x55: ("RET"    , [], SC_EXEC_END),
	0x56: ("STRCMPR", [SCPT_REG_STR, SCPT_REG_STR]),
	0x57: ("STRNCPY", [SCPT_REG_STR, SCPT_REG_STR, SCPT_INT]),
	0x58: ("STRCPYC", [SCPT_REG_STR, SCPT_REG_STR, SCPT_INT]),
	0x59: ("STRCPYI", [SCPT_REG_STR, SCPT_STR]),
	0x5A: ("STRCLR" , [SCPT_REG_STR]),
	0x5B: ("STRCPY" , [SCPT_REG_STR, SCPT_REG_STR]),
	0x5C: (None     , []),
	0x5D: (None     , []),
	0x5E: ("CMD5E"  , [SCPT_BYTE, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT]),
	0x5F: ("STRTIME", [SCPT_REG_STR]),
	0x60: ("FILETM" , [SCPT_REG_INT, SCPT_REG_STR, SCPT_FNAME]),
	0x61: ("XYFSAVE", [SCPT_FNAME]),
	0x62: ("CMD62"  , [SCPT_REG_INT, SCPT_REG_INT]),
	0x63: ("GFX63"  , [SCPT_BYTE, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_BYTE, SCPT_INT, SCPT_INT]),
	0x64: ("GFX64"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x65: (None     , []),
	0x66: (None     , []),
	0x67: ("GFX67"  , [SCPT_BYTE, SCPT_BYTE, SCPT_BYTE, SCPT_BYTE]),
	0x68: ("GFX68"  , [SCPT_REG_INT, SCPT_REG_INT]),
	0x69: ("GFX69"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x6A: ("CMD6A"  , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT]),
	0x6B: ("CMD6B"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x6C: (None     , []),
	0x6D: (None     , []),
	0x6E: ("STRLEN" , [SCPT_REG_INT, SCPT_REG_STR]),
	0x6F: (None     , []),
	0x70: (None     , []),
	0x71: (None     , []),
	0x72: ("LOOPSTI", [SCPT_INT]),
	0x73: ("LOOPGTR", [SCPT_REG_INT]),
	0x74: ("LOOPJPI", [SCPT_INT, SCPT_JUMP]),
	0x75: ("FONTCHR", [SCPT_INT, SCPT_DATA1]),
	0x76: ("CMD76"  , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT]),
	0x77: ("CMD77"  , [SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT, SCPT_INT]),
	0x78: ("CMD78"  , [SCPT_INT, SCPT_INT]),
	0x79: ("CMD79"  , [SCPT_INT]),
	0x7A: ("LOOPSTR", [SCPT_REG_INT]),
	0x7B: ("LOOPJPR", [SCPT_REG_INT, SCPT_JUMP]),
	0x7C: (None     , []),
	0x7D: (None     , []),
	0x7E: (None     , []),
	0x7F: ("DOSRETR", [SCPT_REG_INT], SC_EXEC_END),
	0x80: ("STRFLD" , [SCPT_REG_STR, SCPT_FNAME]),
	0x81: ("STRFSAV", [SCPT_REG_STR, SCPT_FNAME]),
	0x82: ("GFX82"  , []),
	0x83: ("GFX83"  , [SCPT_REG_INT]),
	0x84: ("GFX84"  , []),
	0x85: ("GFX85"  , []),
	0x86: ("GFX86"  , [SCPT_DATA1]),
	0x87: ("GFX87"  , [SCPT_INT, SCPT_BYTE, SCPT_INT, SCPT_INT, SCPT_BYTE, SCPT_BYTE, SCPT_BYTE, SCPT_BYTE, SCPT_BYTE, SCPT_BYTE]),
	0x88: ("GFX88"  , [SCPT_BYTE, SCPT_INT, SCPT_INT]),
	0x89: ("GFX89"  , [SCPT_DATA1]),
	0x8A: ("GFX8A"  , [SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT, SCPT_REG_INT]),
	0x8B: ("GFX8B"  , [SCPT_REG_INT, SCPT_INT, SCPT_INT]),
	0x8C: ("GFX8C"  , []),
	0x8D: ("GFX8D"  , []),
	0x8E: ("GFX8E"  , []),
}

JISCHR_COMMENTS = {}
necjis = nec_jis_conv.JISConverter()
config = {}


def load_additional_font_table(filepath: str) -> int:
	global necjis
	global JISCHR_COMMENTS
	
	with open(filepath, "rt", encoding="utf-8") as f:
		for line in f:
			line = line.rstrip()
			items = line.split('\t')
			for (iid, item) in enumerate(items):
				if item.lstrip().startswith('#'):
					items = items[0:iid]
					break
			if len(items) <= 1:
				continue
			
			# parse table
			jis_code = int(items[0], 0)
			ucode_str = items[1]
			if ucode_str.startswith('U'):
				ucodes_strs = ucode_str.split('+')[1:]
				ucodes = [int(uc, 0x10) for uc in ucodes_strs]
				
				if config.use_emojis:
					ins = necjis.add_character(jis_code, ucodes)
					if not ins:
						print(f"Warning: Replacing JIS character 0x{jis_code:04X}.")
			elif (len(ucode_str) == 0) or (ucode_str.startswith('-')):
				pass	# undefined character (comment only)
			else:
				print(f"Error in line: {line}")
				continue
			if len(items) > 2:
				JISCHR_COMMENTS[jis_code] = items[2]
	necjis.recalc_decode_lut()

def load_scene_binary(fn_in: str) -> bytes:
	with open(fn_in, "rb") as f:
		data = f.read()

	if config.unscrambled:
		return data
	else:
		# remove the "encryption":
		#   The game engine skips the first 0x100 bytes and XORs all remaining ones with 0x01.
		return data[:0x100] + bytes([x ^ 0x01 for x in data[0x100:]])

def scene_read_array(scenedata: bytes, usage_mask: list, pos: int, array_size: int) -> bytes:
	try:
		for ofs in range(array_size):
			usage_mask[pos + ofs] |= 0x01
		return scenedata[pos : pos + array_size]
	except Exception as e:
		print(f"Error in scene_read_array(pos 0x{pos:04X}, array size 0x{array_size:04X}, file size 0x{len(scenedata):04X}): {e}")
		raise e

def scene_read_int(scenedata: bytes, usage_mask: list, pos: int) -> int:
	usage_mask[pos + 0x00] |= 0x01
	usage_mask[pos + 0x01] |= 0x01
	return struct.unpack_from("<H", scenedata, pos)[0]

def find_next_label(labels: dict, pos: int) -> int:
	for lblpos in sorted(labels.keys()):
		if lblpos >= pos:
			return lblpos
	return -1

def is_sjis_str(data: bytes) -> bool:
	sjis_2nd = False
	for c in data:
		if not sjis_2nd:
			if c >= 0x20 and c <= 0x7E:
				pass
			elif c <= 0x0F:
				pass	# allow for text control commands
			elif c == 0x00:
				break
			elif (c >= 0x81 and c <= 0x9F) or (c >= 0xE0 and c <= 0xEF):
				sjis_2nd = True
			else:
				return False
		else:
			sjis_2nd = False
			if c >= 0x40 and c <= 0x7E:
				pass
			elif c >= 0x80 and c <= 0xFE:
				pass
			else:
				return False
	return True

def guess_data_type(scenedata: bytes, startpos: int, endpos: int) -> int:
	# try to guess what type of data this is
	data = scenedata[startpos : endpos]
	nullpos = data.find(0)
	if nullpos > 1:	# need at least 1 character
		dstr = data[0 : nullpos]
		if dstr[0] < 10:	# first character of file names
			if sum([1 for c in dstr[1:] if not (c >= 0x20 and c <= 0x7E)]) == 0:
				return SCPT_FNAME
		if is_sjis_str(dstr):
			return SCPT_STR
	return -1

def test_for_code(scenedata: bytes, file_usage: list, startpos: int) -> bool:
	# --- parse unknown data as code and do basic syntax checking ---
	# The function is used to detect code in unreferenced data sections.
	curpos = startpos
	while curpos < len(scenedata):
		cmd_id = struct.unpack_from("<H", scenedata, curpos)[0]
		curpos += 0x02
		if cmd_id >= 0x100:
			return False
		if cmd_id not in SCENE_CMD_LIST:
			return False
		cmd_info = SCENE_CMD_LIST[cmd_id]
		if cmd_info[0] is None:
			return False
		
		# parse/skip all parameters
		first_reg_type = None
		for par_type in cmd_info[1]:
			if par_type == SCPT_ILVAR:
				# variable-size parameter
				if first_reg_type == SCPT_REG_STR:
					par_type = SCPT_STR
				elif first_reg_type == SCPT_REG_LNG:
					par_type = SCPT_LONG
				else:
					par_type = SCPT_INT
			
			if par_type == SCPT_LONG:
				par_val = struct.unpack_from("<I", scenedata, curpos)[0]
				curpos += 0x04
			else:
				par_val = struct.unpack_from("<H", scenedata, curpos)[0]
				curpos += 0x02
			
			if (first_reg_type is None) and (par_type & SCPT_MASK) == SCPTM_REG:
				if par_type == SCPT_REG_IL:
					if par_val < 0x400:
						first_reg_type = SCPT_REG_INT
					else:
						first_reg_type = SCPT_REG_LNG
				else:
					first_reg_type = par_type
		
		if len(cmd_info) >= 3:
			# stop parsing at certain commands - result will be success
			if cmd_info[2] == SC_EXEC_END:
				break
			elif cmd_info[2] == SC_EXEC_SPC:
				if cmd_id == 0x13:	# jump table
					break
	return True

def find_possible_code(scenedata: bytes, file_usage: list, label_list: dict) -> int:
	# --- scan all unreferenced data sections and return the position of a potential (unused) code section ---
	curpos = 0x100
	while True:
		# search for next unparsed section
		while (curpos < len(scenedata)) and (file_usage[curpos] != 0x00):
			curpos += 1
		if curpos >= len(scenedata):
			break
		
		if curpos in label_list:
			dtype = label_list[curpos][0]
		else:
			dtype = guess_data_type(scenedata, curpos, len(scenedata))
		
		if dtype >= 0:
			# known (or detected) data section - just skip
			endpos = find_next_label(label_list, curpos + 1)
			if endpos < 0:
				endpos = len(scenedata)
			if dtype in [SCPT_STR, SCPT_FNAME]:
				strend = scenedata.find(0x00, curpos, endpos)
				if strend >= 0:
					endpos = strend + 1
			curpos = endpos
		else:
			is_code = test_for_code(scenedata, file_usage, curpos)
			if is_code:
				#print(f"Found possible code at 0x{curpos:04X}")
				return curpos
			else:
				# skip entire unused block
				while (curpos < len(scenedata)) and (file_usage[curpos] == 0x00):
					curpos += 1
	return -1

def parse_scene_binary(scenedata: bytes) -> tuple:
	cmd_list = []	# list[ tuple(file offset, command ID, list[params] ) ]
	file_usage = [0x00] * len(scenedata)
	label_list = {}	# dict{ file offset: (label type, flags, label name) }
	
	# --- parse code sections ---
	remaining_code_locs = [0x100]	# start at offset 0x100
	curpos = None
	while True:
		# Note: The code for deciding what to parse next is a bit complex,
		#       but I can not just parse the file once from start to end.
		#       The script can do arbitrary jumps forward and backward
		#       and I need to follow them in order to reach all code.
		if curpos is None:
			if len(remaining_code_locs) > 0:
				curpos = remaining_code_locs.pop(0)
			else:
				# This part is for finding unreferenced code sections.
				curpos = find_possible_code(scenedata, file_usage, label_list)
				if curpos >= 0:
					label_list[curpos] = (SCPT_JUMP, LBLFLG_UNUSED, None)
				else:
					curpos = None
		if curpos is None:
			break	# exit loop when no more code sections are found
		if curpos >= len(scenedata):
			curpos = None
			continue
		if file_usage[curpos] != 0x00:
			curpos = None
			continue
		
		cmd_pos = curpos
		cmd_id = scene_read_int(scenedata, file_usage, cmd_pos)
		curpos += 0x02
		if cmd_id >= 0x100:
			# The game engine treats this as command 0x00. (return to DOS)
			print(f"Found invalid command ID 0x{cmd_id:02X} at offset 0x{cmd_pos:04X}!")
			file_usage[cmd_pos+0] &= ~0x01
			file_usage[cmd_pos+1] &= ~0x01
			curpos = None	# stop processing here
			continue
		if cmd_id not in SCENE_CMD_LIST:
			# These commands will crash the game.
			print(f"Found invalid command ID 0x{cmd_id:02X} at offset 0x{cmd_pos:04X}!")
			cmd_list += [(cmd_pos, -2, [cmd_id])]
			continue
		
		cmd_info = SCENE_CMD_LIST[cmd_id]
		if cmd_info[0] is None:
			# The game engine will quit with an error message for these commands.
			print(f"Found reserved command ID 0x{cmd_id:02X} at offset 0x{cmd_pos:04X}!")
			cmd_list += [(cmd_pos, -2, [cmd_id])]
			continue
		
		# parse command parameters
		params = []
		first_reg_type = None
		for par_type in cmd_info[1]:
			if par_type == SCPT_ILVAR:
				# variable-size parameter
				# The size (2 or 4 bytes) of the parameter depends on destination register.
				if first_reg_type == SCPT_REG_STR:
					par_type = SCPT_STR
				elif first_reg_type == SCPT_REG_LNG:
					par_type = SCPT_LONG
				else:
					par_type = SCPT_INT
			
			if par_type == SCPT_LONG:
				par_data = scene_read_array(scenedata, file_usage, curpos, 0x04)
				par_val = struct.unpack("<I", par_data)[0]
				curpos += 0x04
			else:
				par_val = scene_read_int(scenedata, file_usage, curpos)
				curpos += 0x02
			
			if (par_type & SCPT_MASK) == SCPTM_PTR:
				# pointer parameters: add label for them
				label_list[par_val] = (par_type, 0x00, None)
			if par_type == SCPT_JUMP:
				# add jump destination to list of locations to be processed
				remaining_code_locs.append(par_val)
			
			if (first_reg_type is None) and (par_type & SCPT_MASK) == SCPTM_REG:
				# remember first parameter's register type
				if par_type == SCPT_REG_IL:
					if par_val < 0x400:
						first_reg_type = SCPT_REG_INT
					else:
						first_reg_type = SCPT_REG_LNG
				else:
					first_reg_type = par_type
			params += [(par_type, par_val)]
		cmd_list += [(cmd_pos, cmd_id, params)]
		
		if len(cmd_info) >= 3:
			# special handling
			if cmd_info[2] == SC_EXEC_END:
				curpos = None	# stop processing here
			elif cmd_info[2] == SC_EXEC_SPC:
				if cmd_id == 0x13:	# jump table
					cmd_pos = curpos
					endpos = len(scenedata)
					params = []
					while curpos < endpos:
						if curpos in label_list:
							break
						ptrval = scene_read_int(scenedata, file_usage, curpos)
						if ptrval < 0x100:
							# Note: Some tables begin with a "dummy" value in the range 0x00..0xFF.
							# (Most files in Canaan use 0x80..0x8F, but there are also 0x70..0x7F used in a few files.)
							# This is the case, when there is an "ADDI var, 1" value right before the "JTBL var" commadn.
							# In this case, we have to just accept the pointer.
							# In all other cases, we probably want to exit, so that we don't accidentally interpret code as a pointer.
							if curpos > cmd_pos:
								ptrval = 0xFFFF	# finish reading
							else:
								print(f"Warning: Jump table dummy value 0x{ptrval:04X} at offset 0x{cmd_pos:04X}!")
						if ptrval >= len(scenedata):
							# remove usage mask (-> assume that we didn't process this value)
							# important for unused code
							file_usage[curpos + 0x00] &= ~0x01
							file_usage[curpos + 0x01] &= ~0x01
							break
						params += [ptrval]
						curpos += 0x02
						
						if ptrval >= 0x100:
							label_list[ptrval] = (SCPT_JUMP, 0x00, None)
							remaining_code_locs.append(ptrval)
							if ptrval > cmd_pos and ptrval < endpos:
								endpos = ptrval
					cmd_list += [(cmd_pos, -3, params)]
					curpos = None	# stop processing here
				elif cmd_id == 0x40:	# menu
					lbl_pos = params[2][1]
					(par_type, lbl_flags, lbl_name) = label_list[lbl_pos]
					lbl_flags |= LBLFLG_MENU	# enforce 5 items per line
					label_list[lbl_pos] = (par_type, lbl_flags, lbl_name)
	
	# --- parse data sections ---
	MODE_UNKNOWN = 0x00
	MODE_DATA = 0x10
	MODE_STR = 0x11
	
	mode = MODE_UNKNOWN
	curpos = 0x100
	while True:
		# search for next unparsed section
		while (curpos < len(scenedata)) and (file_usage[curpos] != 0x00):
			curpos += 1
		if curpos >= len(scenedata):
			break
		
		endpos = find_next_label(label_list, curpos + 1)
		if endpos < 0:
			endpos = len(scenedata)
		elif endpos >= len(scenedata):
			endpos = len(scenedata)
		
		cmd_mode = -1	# default to 1-byte data
		if mode == MODE_UNKNOWN:
			if curpos not in label_list:
				# try to detect data type for unused data
				dtype = guess_data_type(scenedata, curpos, endpos)
				if dtype >= 0:
					label_list[curpos] = (dtype, LBLFLG_UNUSED, None)
			if curpos in label_list:
				if label_list[curpos][0] == SCPT_JUMP:
					#mode = MODE_CMD
					print(f"Warning: found unparsed code section at 0x{curpos:04X}!")
				elif label_list[curpos][0] in [SCPT_STR, SCPT_FNAME]:
					mode = MODE_STR
				elif label_list[curpos][0] == SCPT_DATA2:
					mode = MODE_DATA
					cmd_mode = -20	# 2-byte data
				else:
					mode = MODE_DATA
		
		if mode == MODE_STR:
			# terminate strings at '\0'
			strend = scenedata.find(0x00, curpos, endpos)
			if strend >= 0:
				endpos = strend + 1
			str_arr = scene_read_array(scenedata, file_usage, curpos, endpos - curpos)
			cmd_list += get_sjis_str_items(str_arr, curpos)
		elif (cmd_mode == -20) or (cmd_mode == -2):
			# do 2-byte word parsing
			darray = scene_read_array(scenedata, file_usage, curpos, endpos - curpos)
			iterat = struct.iter_unpack("<H", darray)
			cmd_list += [(curpos, cmd_mode, [v[0] for v in iterat])]
		else:
			# just include the data as bytes
			cmd_list += [(curpos, cmd_mode, scene_read_array(scenedata, file_usage, curpos, endpos - curpos))]
		mode = MODE_UNKNOWN
		curpos = endpos
	
	cmd_list.sort(key=lambda cmd: cmd[0])
	return (cmd_list, file_usage, label_list)

def generate_label_names(label_list: dict) -> None:
	for lbl_pos in label_list:
		(par_type, lbl_flags, lbl_name) = label_list[lbl_pos]
		if not (lbl_name is None or lbl_name == ""):
			continue
		if (par_type == SCPT_DATA1) or (par_type == SCPT_DATA2):
			lbl_prefix = "data"
		elif par_type == SCPT_STR:
			lbl_prefix = "str"
		elif par_type == SCPT_FNAME:
			lbl_prefix = "file"
		elif par_type == SCPT_JUMP:
			lbl_prefix = "loc"
		else:
			lbl_prefix = "unk"
		lbl_name = f"{lbl_prefix}_{lbl_pos:04X}"
		label_list[lbl_pos] = (par_type, lbl_flags, lbl_name)
	return

def get_sjis_str_items(str_data: bytes, startpos: int) -> list:
	#if not config.inline_sjis_bytes:
	#	return [(startpos, -11, str_data)]	# this line simplifies the output by inlining Shift-JIS data.
	
	# This function splits string data in such a way, that Shift-JIS characters from
	# the "custom font" JIS planes get their own assembly command.
	last_type = None
	new_type = None
	token_data = []
	token_pos = startpos
	new_data = None
	result = []
	sjis_1st = None
	chrpos = 0
	for (pos, c) in enumerate(str_data):
		new_type = -11
		if sjis_1st is None:
			if c >= 0x80:
				sjis_1st = c
				new_data = None
			else:
				new_data = bytes([c])
			chrpos = pos	# save start position of current character
		else:
			sjis = (sjis_1st << 8) | (c << 0)
			jis = necjis.sjis2jis(sjis)
			if (jis is not None) and (jis not in necjis.jis_uc_lut):
				# use special "DSJ" instruction for JIS codes we can not convert
				new_type = -25
				new_data = [jis]
			if new_type == -11:
				new_data = bytes([sjis_1st, c])
			sjis_1st = None
			# do NOT set chrpos
		
		if new_data is not None:
			if last_type != new_type:
				if len(token_data) > 0:
					result += [(token_pos, last_type, token_data)]
				token_data = new_data
				last_type = new_type
				token_pos = startpos + chrpos
			else:
				token_data += new_data
	if len(token_data) > 0:
		result += [(token_pos, last_type, token_data)]
	return result

def str2asm(str_data: bytes) -> typing.List[str]:
	# convert binary array to ASM string
	# This outputs a list of "tokens", consisting of either
	#   - a quoted string or
	#   - a raw number (for unprintable/unconvertable character sequences)
	# This also takes care of converting Shift-JIS characters to UTF-8 where possible.
	res_chrs = []
	sjis_1st = None
	for c in str_data:
		if sjis_1st is None:
			if c >= 0x80:
				sjis_1st = c
			elif c >= 0x20 and c <= 0x7E:
				res_chrs.append(chr(c))
			else:
				res_chrs.append(c)
		else:
			#try:
			#	sjis_str = bytes([sjis_1st, c]).decode("shift-jis")
			#except:
			#	sjis_str = None
			# manual conversion to catch all the special PC-9801 font ROM characters as well
			#sjis_str = necjis.sjis_decode_str(bytes([sjis_1st, c]))
			sjis_str = necjis.sjis_decode_chr((sjis_1st << 8) | (c << 0))
			if type(sjis_str) is str:
				res_chrs.append(sjis_str)
			else:
				res_chrs.append(sjis_1st)
				res_chrs.append(c)
			sjis_1st = None
	
	res_items = []
	mode = 0
	for c in res_chrs:
		if type(c) is str:
			new_mode = 1
			if c in ['"', "'", '\\']:	# escape some special characters
				c = '\\' + c_add
			else:
				c_add = c
		else:
			new_mode = 0
			c_add = f"0x{c:02X}" if c >= 10 else f"{c}"
		if new_mode == 0 and mode == 0:
			res_items.append(c_add)
		elif new_mode == 0 and mode == 1:
			res_items[-1] += '"'
			res_items.append(c_add)
		elif new_mode == 1 and mode == 0:
			res_items.append('"' + c_add)
		elif new_mode == 1 and mode == 1:
			res_items[-1] += c_add
		mode = new_mode
	if mode == 1:
		res_items[-1] += '"'
	return res_items

def gen_string_groups(data_items: typing.List[str]) -> typing.List[int]:
	# generate "groups" of string items to be places on the same line
	# splits after 0D (new line) and 01 (wait for key press)
	chr_mode = None
	new_chr_mode = None
	result = []
	for (idx, itm) in enumerate(data_items):
		if itm.startswith('"'):
			chr_id = 0x22
		else:
			chr_id = int(itm, 0)
		# ignore first character (disk drive in file names)
		# but split at 0D/01 -> text
		if (idx > 0) and (chr_id in [0x01, 0x0D]):
			new_chr_mode = 1
		elif chr_id != 0x00:	# don't split at terminator characters
			new_chr_mode = 0
		if new_chr_mode == 0 and chr_mode == 1:
			result.append(idx)
		chr_mode = new_chr_mode
	result.append(len(data_items))
	return result

def get_filename(params: list) -> typing.Union[str, None]:
	if params[0] > 9:	# first byte is the disk number
		return None
	dataarr = params[1:]
	strend = dataarr.find(0x00)
	if strend >= 0:
		dataarr = dataarr[:strend]
	try:
		return dataarr.decode("shift-jis")
	except:
		return None

def write_asm(cmd_list, label_list, fn_out: str) -> None:
	cmd_pos_map = {}
	for (cid, cmd) in enumerate(cmd_list):
		(cmd_pos, cmd_id, params) = cmd
		cmd_pos_map[cmd_pos] = cid
	
	with open(fn_out, "wt", encoding="utf-8") as f:
		last_mode = None
		for cmd in cmd_list:
			(cmd_pos, cmd_id, params) = cmd
			
			if last_mode is not None:
				# insert empty line when changing between data and code
				new_mode = 1 if cmd_id < 0 else 0
				if last_mode != new_mode:
					f.write("\n")
					last_mode = None
			
			if cmd_pos in label_list:
				# insert labels before commands when references exist
				lbl_name = label_list[cmd_pos][2]
				f.write(f"{lbl_name}:")
				if label_list[cmd_pos][1] & LBLFLG_UNUSED:
					f.write("\t; unused")
				f.write("\n")
			
			if cmd_id < 0:
				# output raw data (byte arrays, word arrays, strings, ...)
				group_size = 8
				group_list = None
				show_idx = False
				comment = None
				if cmd_pos in label_list:
					lbl_flags = label_list[cmd_pos][1]
					if lbl_flags & LBLFLG_MENU:
						group_size = 5
				if cmd_id == -3:
					cmd_name = "DW"
					group_size = 1
					show_idx = True
					data_strs = []
					for ptr in params:
						if ptr in label_list:
							data_strs.append(label_list[ptr][2])
						else:
							data_strs.append(f"0x{ptr:04X}")
					last_mode = -1
				elif cmd_id == -25:
					cmd_name = "DSJ"	# Data: Shift-JIS
					data_strs = [f"0x{val:04X}" for val in params]
					chrs = [JISCHR_COMMENTS[val] for val in params if val in JISCHR_COMMENTS]
					if len(chrs) > 0:
						comment = ", ".join(chrs)
				elif cmd_id == -20:
					cmd_name = "DW"	# Data: word (decimal)
					data_strs = [f"{val}" for val in params]
				elif cmd_id == -2:
					cmd_name = "DW"	# Data: word (hex)
					data_strs = [f"0x{val:04X}" for val in params]
				elif cmd_id == -11:
					cmd_name = "DB"	# Data: string
					data_strs = str2asm(params)
					group_list = gen_string_groups(data_strs)	# intelligent line splitting
				elif cmd_id == -10:
					cmd_name = "DB"	# Data: byte (decimal)
					data_strs = [f"{val}" for val in params]
				else:
					cmd_name = "DB"	# Data: word (hex)
					data_strs = [f"0x{val:02X}" for val in params]
				
				if group_list is None:
					# output multiple lines with N items per line
					group_list = [i for i in range(group_size, len(data_strs), group_size)] + [len(data_strs)]
				start_idx = 0
				for end_idx in group_list:
					data_str = ", ".join(data_strs[start_idx : end_idx])
					f.write(f"\t{cmd_name}\t{data_str}")
					if show_idx:
						f.write(f"\t; {start_idx}")
					if comment is not None:
						f.write(f"\t; {comment}")
					f.write("\n")
					start_idx = end_idx
				last_mode = 1
			else:
				# output commands
				cmd_info = SCENE_CMD_LIST[cmd_id]
				cmd_name = cmd_info[0]
				data_strs = []
				comment = None
				# make list of all parameters, with resolved register and label names
				for (par_type, par_val) in params:
					data_str = None
					if (par_type & SCPT_MASK) == SCPTM_PTR:
						if par_val in label_list:
							data_str = label_list[par_val][2]	# replace pointer value with label string
							if label_list[par_val][0] == SCPT_FNAME:
								# add comment with file name
								try:
									dcmd = cmd_list[cmd_pos_map[par_val]]
									comment = get_filename(dcmd[2])
								except:
									pass	# catch invalid offsets
					elif (par_type & SCPT_MASK) == SCPTM_REG:
						if par_type == SCPT_REG_IL:
							# int/long register (depends on ID)
							if par_val < 0x400:
								par_type = SCPT_REG_INT
							else:
								par_type = SCPT_REG_LNG
								par_val -= 0x400
						# output register names
						if par_type == SCPT_REG_INT:
							data_str = f"i{par_val}"
						elif par_type == SCPT_REG_LNG:
							data_str = f"l{par_val}"
						elif par_type == SCPT_REG_STR:
							data_str = f"s{par_val}"
					if data_str is None:
						data_str = f"{par_val}"
					data_strs.append(data_str)
				data_str = ", ".join(data_strs)
				
				cols = ["", cmd_name]
				if len(data_str) > 0:
					cols += [data_str]
				if comment is not None:
					cols += ["; " + comment]
				f.write("\t".join(cols) + '\n')
				last_mode = 0
				
				if len(cmd_info) >= 3:
					if cmd_info[2] == SC_EXEC_END:
						f.write("\n")
						last_mode = None
					elif cmd_info[2] == SC_EXEC_SPC:
						if cmd_id == 0x13:
							last_mode = 1	# expect data
	return

def decompile_scene(fn_in: str, fn_out: str) -> int:
	try:
		scn_data = load_scene_binary(fn_in)
	except IOError:
		print(f"Error loading {fn_in}")
		return 1
	(cmd_list, file_usage, label_list) = parse_scene_binary(scn_data)
	generate_label_names(label_list)
	try:
		write_asm(cmd_list, label_list, fn_out)
		print("Done.")
	except IOError:
		print(f"Error writing {fn_out}")
		return 1
	return 0

def main(argv):
	global config
	global necjis
	
	print("four-nine/Izuho Saruta System-98 Scenario Decompiler")
	aparse = argparse.ArgumentParser()
	aparse.add_argument("-f", "--font-file", type=str, help="description file for custom font characters")
	aparse.add_argument("-e", "--use-emojis", action="store_true", help="decode custom font into emojis")
	aparse.add_argument("-u", "--unscrambled", action="store_true", help="assume descrambled input data")
	aparse.add_argument("in_file", help="input scenario file (.S)")
	aparse.add_argument("out_file", help="output assembly file (.ASM)")
	
	config = aparse.parse_args(argv[1:])
	
	necjis.load_from_pickle("NEC-C-6226-lut.pkl")
	if config.font_file:
		load_additional_font_table(config.font_file)
	return decompile_scene(config.in_file, config.out_file)

if __name__ == "__main__":
	sys.exit(main(sys.argv))
