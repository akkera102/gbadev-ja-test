// Gemini 260108
#include <stdio.h>
#include <math.h>

// GBAのプロジェクト設定に合わせる
#define BASE_STEP_C4 1000
#define BASE_STEP_C5 2048

int main() {
    // 1半音ごとの倍率を計算 (2.048の12乗根)
    // これにより、1オクターブ上がるとちょうど2.048倍（ド5=2048）になる
    double semi_ratio = pow((double)BASE_STEP_C5 / BASE_STEP_C4, 1.0 / 12.0);

    printf("// GBA Sound Engine Pitch Table (C4=1000, C5=2048)\n");
    printf("const u32 g_pitch_table[] = {\n");

    for (int oct = 0; oct <= 8; oct++) {
        printf("    /* Oct % d */ ", oct);
        for (int note = 0; note < 12; note++) {
            // ド4（ノート番号48）からの半音距離
            int n = (oct * 12 + note) - 48;
            
            // 指数関数による計算
            double step = BASE_STEP_C4 * pow(semi_ratio, (double)n);
            
            printf("%4u, ", (unsigned int)(step + 0.5));
        }
        printf("\n");
    }
    printf("};\n");

    return 0;
}
