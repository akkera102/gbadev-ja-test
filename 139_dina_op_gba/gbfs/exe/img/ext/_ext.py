# coding: Shift_JIS
# GBAで使っていない未使用ファイルを抽出

# Gemini 260725

dir_file_path = 'dir.txt'
use_file_path = 'use.txt'
output_file_path = 'del.txt'

def main():
    # 1. dir.txt と use.txt の内容をShift-JISで読み込み、集合(Set)にする
    with open(dir_file_path, 'r', encoding='shift_jis') as f:
        # line.strip() で改行コードを削除してセットに格納
        dir_files = set(line.strip() for line in f if line.strip())

    with open(use_file_path, 'r', encoding='shift_jis') as f:
        use_files = set(line.strip() for line in f if line.strip())

    # 2. 差分をとる (dir には存在するが、use にはないファイル)
    unused_files = dir_files - use_files

    # 3. 見やすいようにソート（元のファイルが連番の場合に並び順が揃います）
    unused_files_sorted = sorted(list(unused_files))

    # 4. del.txt としてShift-JISで出力
    with open(output_file_path, 'w', encoding='shift_jis') as f:
        for file_name in unused_files_sorted:
            f.write(f"{file_name}\n")

    print(f"抽出完了: {len(unused_files_sorted)} 件のファイルを '{output_file_path}' に書き出しました。")

if __name__ == "__main__":
    main()

