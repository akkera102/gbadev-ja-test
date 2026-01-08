// Gemini 260108
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define SAMPLING_RATE 13359      // サンプリング周波数 (Hz)
#define DURATION 1               // 再生時間 (秒)
#define FREQ_C4 261.63           // ド (C4) の周波数 (Hz)
#define PI 3.1415926535

// 楽器タイプ定義
typedef enum {
    INST_SINE,          // 0: 正弦波 (基準)
    INST_ACOUSTIC_PIANO,// 1: アコースティックピアノ風 (複雑な倍音)
    INST_FLUTE,         // 2: フルート (柔らかな奇数倍音)
    INST_VIOLIN,        // 3: バイオリン (鋭いのこぎり波ベース)
    INST_TRUMPET,       // 4: トランペット (時間で変化する倍音)
    INST_WOOD_BASS,     // 5: ウッドベース (太い低域)
    INST_CHURCH_ORGAN,  // 6: チャーチオルガン (重厚な和音)
    INST_MUSIC_BOX,     // 7: オルゴール (高域の澄んだ金属音)
    INST_XYLOPHONE,     // 8: 木琴 (短い立ち上がりと素早い減衰)
    INST_HARMONICA,     // 9: ハーモニカ (リードのうなり)
    INST_MAX
} InstrumentType;

// 楽器名（ファイル名用）
const char* inst_names[] = {
    "sine", "piano", "flute", "violin", "trumpet",
    "bass", "church_organ", "music_box", "xylophone", "harmonica"
};

// 波形生成関数
int8_t generate_sample(InstrumentType type, double t, double freq) {
    double wave = 0;
    switch (type) {
        case INST_SINE:
            wave = sin(2 * PI * freq * t);
            break;
        case INST_ACOUSTIC_PIANO:
            // ピアノ：複数の倍音と、わずかなデチューン
            wave = 0.6 * sin(2 * PI * freq * t) + 0.3 * sin(2 * PI * freq * 2.01 * t) + 0.1 * sin(2 * PI * freq * 3 * t);
            break;
        case INST_FLUTE:
            // フルート：奇数倍音をメインに、わずかな息のノイズ（ランダム）を混ぜる
            wave = 0.8 * sin(2 * PI * freq * t) + 0.2 * sin(2 * PI * freq * 3 * t);
            wave += 0.02 * ((double)rand()/RAND_MAX); 
            break;
        case INST_VIOLIN:
            // バイオリン：のこぎり波にビブラート成分を想定した倍音構成
            wave = 0.5 * (2.0 * (t * freq - floor(t * freq + 0.5))); // のこぎり波
            wave += 0.2 * sin(2 * PI * freq * 2 * t);
            break;
        case INST_TRUMPET:
            // トランペット：強い倍音。波形を少し歪ませて金属的な響きにする
            wave = sin(2 * PI * freq * t) + 0.5 * sin(2 * PI * freq * 2 * t) + 0.3 * sin(2 * PI * freq * 3 * t);
            if (wave > 0.6) wave = 0.6; if (wave < -0.6) wave = -0.6; // ソフトクリップ
            break;
        case INST_WOOD_BASS:
            // ウッドベース：基本波が強く、高域が少ない
            wave = 0.8 * sin(2 * PI * freq * t) + 0.2 * sin(2 * PI * freq * 2 * t);
            break;
        case INST_CHURCH_ORGAN:
            // チャーチオルガン：パイプを複数鳴らしたような厚み
            wave = 0.4 * sin(2 * PI * freq * t) + 0.3 * sin(2 * PI * freq * 0.5 * t) + 0.3 * sin(2 * PI * freq * 2 * t);
            break;
        case INST_MUSIC_BOX:
            // オルゴール：高い周波数の純粋な音に近い
            wave = 0.7 * sin(2 * PI * freq * t) + 0.3 * sin(2 * PI * freq * 4.05 * t);
            break;
        case INST_XYLOPHONE:
            // 木琴：基本波と高い非整数倍音
            wave = 0.7 * sin(2 * PI * freq * t) + 0.3 * sin(2 * PI * freq * 2.5 * t);
            break;
        case INST_HARMONICA:
            // ハーモニカ：矩形波に近いが、リードの震えを出す
            wave = (sin(2 * PI * freq * t) >= 0 ? 0.5 : -0.5) + 0.2 * sin(2 * PI * freq * 2 * t);
            break;
    }

    // 量子化 (-128 ～ 127)
    int32_t sample = (int32_t)(wave * 127);
    if (sample > 127) sample = 127;
    if (sample < -128) sample = -128;

    return (int8_t)sample;
}

int main() {
    int total_samples = SAMPLING_RATE * DURATION;
    int8_t buffer[total_samples];

    printf("Starting wave generation (Sampling Rate: %dHz)...\n", SAMPLING_RATE);

    for (int inst_idx = 0; inst_idx < INST_MAX; inst_idx++) {
        for (int i = 0; i < total_samples; i++) {
            double t = (double)i / SAMPLING_RATE;
            buffer[i] = generate_sample((InstrumentType)inst_idx, t, FREQ_C4);
            
            // ノイズ対策：末尾100サンプルでごく短いフェードアウトをかける
            if (i > total_samples - 100) {
                double fade = (double)(total_samples - i) / 100.0;
                buffer[i] = (int8_t)(buffer[i] * fade);
            }
        }

        // ファイル名の作成 (例: inst_1_organ.bin)
        char filename[64];
        sprintf(filename, "inst_%d_%s.bin", inst_idx, inst_names[inst_idx]);

        FILE* f = fopen(filename, "wb");
        if (f) {
            fwrite(buffer, sizeof(int8_t), total_samples, f);
            fclose(f);
            printf("Generated: %s\n", filename);
        } else {
            fprintf(stderr, "Error: Could not open %s for writing.\n", filename);
        }
    }

    printf("All instruments generated successfully.\n");
    return 0;
}
