# coding: Shift_JIS
# 未使用フレームのリスト作成

# Gemini 260725

dir_file_path = 'dir.txt'
nouse_file_path = 'nouse.txt'
output_file_path = 'del.txt'

def main():
    # 1. dir.txt と nouse.txt の内容をShift-JISで読み込み、集合(Set)にする
    with open(dir_file_path, 'r', encoding='shift_jis') as f:
        # line.strip() で改行コードを削除してセットに格納
        dir_files = set(line.strip() for line in f if line.strip())

    with open(nouse_file_path, 'r', encoding='shift_jis') as f:
        nouse_files = set(line.strip() for line in f if line.strip())

    # 2. 積集合(AND)をとる (dir.txt に実在し、かつ nouse.txt にも記載されているファイル)
    # nouse.txtに含まれる「dir.txtに存在しないファイル」はここで弾かれます
    delete_files = dir_files & nouse_files

    # 3. 見やすいようにソート（元のファイルが連番の場合に並び順が揃います）
    delete_files_sorted = sorted(list(delete_files))

    # 4. del.txt としてShift-JISで出力
    with open(output_file_path, 'w', encoding='shift_jis') as f:
        for file_name in delete_files_sorted:
            f.write(f"{file_name}\n")

    print(f"抽出完了: {len(delete_files_sorted)} 件のファイルを '{output_file_path}' に書き出しました。")

if __name__ == "__main__":
    main()
