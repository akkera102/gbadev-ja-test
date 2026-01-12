# Gemini 260110
import math

# 設定値
SAMPLING_RATE = 13379  # GBAサンプリングレート (Hz)
TABLE_SIZE = 256        # 波形テーブルのサイズ (byte)
BASE_A4 = 440.0         # 基準音 A4 (Hz)

# 音階名（1オクターブ分）
base_names = ["C", "CS", "D", "DS", "E", "F", "FS", "G", "GS", "A", "AS", "B"]

# 生成するオクターブの範囲
START_OCTAVE = 2
END_OCTAVE = 7

def calculate_fixed_point_pitch():
    note_list = []
    for oct in range(START_OCTAVE, END_OCTAVE + 1):
        for name in base_names:
            note_list.append(f"{name}{oct}")
            if name == "C" and oct == END_OCTAVE: break
        if note_list[-1] == f"C{END_OCTAVE}": break

    print(f"// Generated for {SAMPLING_RATE}Hz, Table Size: {TABLE_SIZE}")
 #   print(f"// Range: {note_list[0]} to {note_list[-1]}")
    
    # 1. 音程定数 (Pitch Values) の出力
    print("// Pitch Step Values (16.16 Fixed Point)")
    print("const u32 SndPitTbl[] = {")
    for i, name in enumerate(note_list):
        oct_val = int(name[-1])
        note_idx = base_names.index(name[:-1])
        midi_note = (oct_val + 1) * 12 + note_idx
        n = midi_note - 69
        freq = BASE_A4 * (2 ** (n / 12.0))
        step_fixed = round(((freq * TABLE_SIZE) / SAMPLING_RATE) * (1 << 16))
        
        comma = "," if i < len(note_list) - 1 else ""
        print(f"    0x{step_fixed:08X}{comma}\t\t// {name}\t{freq:>8.3f} Hz")
    print("};\n")

    # 2. インデックス用Enum (Note Index) の出力
    print("// Note Indices")
    print("enum {")
    for name in note_list:
        print(f"    SND_NOTE_{name},")
    print("    SND_NOTE_MAX")
    print("};")

if __name__ == "__main__":
    calculate_fixed_point_pitch()
