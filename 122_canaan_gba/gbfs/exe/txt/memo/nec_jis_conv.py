#!/usr/bin/env python3
import sys
import pickle
import typing

class JISConverter:
	def __init__(self):
		self.jis_uc_lut = {}
		self.uc_jis_lut = {}

	def load_from_pickle(self, filepath: str) -> None:
		with open(filepath, "rb") as f:
			self.jis_uc_lut = pickle.load(f)
		self.recalc_decode_lut()
	
	def recalc_decode_lut(self) -> None:
		self.uc_jis_lut = {}
		for jis_code in self.jis_uc_lut:
			ucodes = self.jis_uc_lut[jis_code]
			if ucodes[0] not in self.uc_jis_lut:
				self.uc_jis_lut[ucodes[0]] = []
			self.uc_jis_lut[ucodes[0]] += [(ucodes, jis_code)]

	def add_character(self, jis_code: int, unicode_chrs: typing.Union[str, typing.List[int]]) -> bool:
		# NOTE: requires manual call of recalc_decode_lut()
		if type(unicode_chrs) is str:
			ucodes = [ord(c) for c in unicode_chrs]
		else:
			ucodes = unicode_chrs
		new_insert = (jis_code not in self.jis_uc_lut)
		self.jis_uc_lut[jis_code] = ucodes
		return new_insert

	# convert JIS (2-byte int) -> Shift JIS (2-byte int)
	@staticmethod
	def jis2sjis(chr_id: int) -> typing.Union[int, None]:
		if chr_id < 0x80:
			return chr_id
		jis1 = (chr_id >> 8) & 0xFF
		jis2 = (chr_id >> 0) & 0xFF
		
		if jis1 >= 0x21 and jis1 <= 0x5E:
			sjis1 = 0x70 + (jis1 + 1) // 2	# 0x21..0x5E -> 0x81..0x9F
		elif jis1 >= 0x5F and jis1 <= 0x7E:
			sjis1 = 0xB0 + (jis1 + 1) // 2	# 0x5F..0x7E -> 0xE0..0xEF
		else:
			return None
		if jis2 < 0x21 or jis2 > 0x7E:
			return None
		if (jis1 & 0x01) == 0:
			sjis2 = 0x7E + jis2	# 0x21..0x7E -> 0x9F..0xFC
		elif jis2 < 0x60:
			sjis2 = 0x1F + jis2	# 0x21..0x5F -> 0x40..0x7E
		else:
			sjis2 = 0x20 + jis2	# 0x60..0x7E -> 0x80..0x9E
		
		return (sjis1 << 8) | (sjis2 << 0)

	# convert Shift JIS (2-byte int) -> JIS (2-byte int)
	@staticmethod
	def sjis2jis(chr_id: int) -> typing.Union[int, None]:
		if chr_id < 0x80:
			return chr_id
		if not ((chr_id >= 0x8140 and chr_id <= 0x9FFC) or (chr_id >= 0xE040 and chr_id <= 0xEFFC)):
			return None
		sjis1 = (chr_id >> 8) & 0xFF
		sjis2 = (chr_id >> 0) & 0xFF
		
		jis1 = (0x1F + sjis1 * 2) & 0x7F	# 0x81..0x9F, 0xE0..0xEF -> 0x21..0x5D, 0x5F..0x7D
		if sjis2 < 0x80:
			jis2 = sjis2 - 0x1F	# 0x40..0x7E -> 0x21..0x5F
		elif sjis2 < 0x9F:
			jis2 = sjis2 - 0x20	# 0x80..0x9E -> 0x60..0x7E
		else:
			jis2 = sjis2 - 0x7E	# 0x9F..0xFC -> 0x21..0x7E
			jis1 += 0x01
		
		return (jis1 << 8) | (jis2 << 0)

	# decode JIS character (2-byte int) to Python String (may be 1 or more characters)
	def jis_decode_chr(self, chr_id: int) -> typing.Union[str, None]:
		if chr_id in self.jis_uc_lut:
			c_ids = self.jis_uc_lut[chr_id]
			return "".join([chr(c) for c in c_ids])
		elif chr_id < 0x80:
			return chr(chr_id)
		else:
			return None

	@staticmethod
	def __list_longest_match(l1: list, l2: list) -> int:
		l_size = min([len(l1), len(l2)])
		for idx in range(l_size):
			if l1[idx] != l2[idx]:
				return idx
		return l_size

	# encode Python character (str) into JIS character (int)
	# returns a tuple of (JIS character, consumed str characters)
	def jis_encode_chr(self, chr_str: str) -> typing.Union[typing.Tuple[int, int], None]:
		chr_ids = [ord(c) for c in chr_str]
		if chr_ids[0] in self.uc_jis_lut:
			max_match = 0
			result = None
			for (ucodes, jis_code) in self.uc_jis_lut[chr_ids[0]]:
				lm = self.__list_longest_match(chr_ids, ucodes)
				if (lm >= len(ucodes)) and (lm > max_match):
					max_match = lm
					result = jis_code
			if result is not None:
				return (result, max_match)
		if chr_ids[0] < 0x80:
			return (chr_ids[0], 1)
		else:
			return None

	# decode Shift JIS character (2-byte int) to Python String (may be 1 or more characters)
	def sjis_decode_chr(self, chr_id: int) -> typing.Union[str, None]:
		jis_chr = self.sjis2jis(chr_id)
		if jis_chr is None:
			return None
		return self.jis_decode_chr(jis_chr)

	# encode Python character (str) into Shift JIS character (int)
	# returns a tuple of (Shift JIS character, consumed str characters)
	def sjis_encode_chr(self, chr_str: str) -> typing.Union[typing.Tuple[int, int], None]:
		res_data = self.jis_encode_chr(chr_str)
		if res_data is None:
			return None
		sjis_chr = self.jis2sjis(res_data[0])
		if sjis_chr is None:
			return None
		return (sjis_chr, res_data[1])

	# decode Shift JIS dat (bytes) to a Python String
	# returns either a string OR a tuple of (position of unconvertable input character, converted data)
	def sjis_decode_str(self, str_data: bytes) -> typing.Union[str, tuple]:
		res_str = ""
		sjis_1st = None
		for (pos, c) in enumerate(str_data):
			if sjis_1st is None:
				if c >= 0x80:
					sjis_1st = c
				else:
					res_str += chr(c)
			else:
				sjis_chr = (sjis_1st << 8) | (c << 0)
				uchar = self.sjis_decode_chr(sjis_chr)
				if uchar is None:
					return (pos, res_str)
				res_str += uchar
				sjis_1st = None
		return res_str

	# encode Python str into Shift JIS (bytes)
	# returns either a "bytes" object OR a tuple of (position of unconvertable input character, converted data)
	def sjis_encode_str(self, data: str) -> typing.Union[bytes, tuple]:
		result = b""
		idx = 0
		while idx < len(data):
			cdata = self.sjis_encode_chr(data[idx:])
			if cdata is None:
				return (idx, result)
			if cdata[0] < 0x80:
				result += bytes([cdata[0]])
			else:
				sjis1 = (cdata[0] >> 8) & 0xFF
				sjis2 = (cdata[0] >> 0) & 0xFF
				result += bytes([sjis1, sjis2])
			idx += cdata[1]
		return result

if __name__ == "__main__":
	sys.stdout.reconfigure(encoding='utf-8')
	print("testing JIS conversion ...")
	necjis = JISConverter()
	necjis.load_from_pickle("NEC-C-6226-lut.pkl")
	print("SJIS     JIS    SJIS   str  SJIS")
	for ch_sjis in [0x0041,0x8560,0x8168,0x8641,0x8175,0x864C,0x8176,0x8262,0x8292,0x8299,0x989E,0x9FFC,0xE040,0xEAFC,0xEFFC]:
		ch_jis = necjis.sjis2jis(ch_sjis)
		ch_sjis2 = necjis.jis2sjis(ch_jis)
		dec = necjis.sjis_decode_chr(ch_sjis)
		if dec is None:
			enc = None
		else:
			enc = "{:04X}".format(necjis.sjis_encode_chr(dec)[0])
		print(f"{ch_sjis:04X} -> {ch_jis:04X} -> {ch_sjis2:04X} = {dec} -> {enc}")
