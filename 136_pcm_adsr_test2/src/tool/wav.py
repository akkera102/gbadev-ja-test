# Gemini260110
import numpy as np
import matplotlib.pyplot as plt

# 日本語設定
try:
    import japanize_matplotlib
except ImportError:
    plt.rcParams['font.family'] = 'MS Gothic'

def generate_instrument_waves():
    size = 256
    t = np.linspace(0, 2 * np.pi, size, endpoint=False)

    def additive_synth(harmonics_weights):
        """
        倍音の重みリストを受け取り、波形を合成する
        weights: [基本波, 2倍音, 3倍音, ...]
        """
        wave = np.zeros(size)
        for i, weight in enumerate(harmonics_weights):
            harmonic_num = i + 1
            wave += weight * np.sin(harmonic_num * t)
        
        # -127〜127の範囲に正規化 (s8形式)
        max_val = np.max(np.abs(wave))
        if max_val > 0:
            wave = (wave / max_val) * 127
        return wave.astype(np.int8)

    # --- 楽器の定義 (倍音構成) ---
    # 豊かに聞こえるよう、低次倍音と高次キラキラ成分をブレンドしています
    instruments = [
        {"name": "Sine",             "w": [1.0], "color": "#0078d7"},
        {"name": "Guitar",           "w": [1.0, 0.6, 0.4, 0.2, 0.1, 0.2, 0.1], "color": "#d77800"},
        {"name": "Harmonica",        "w": [1.0, 0.2, 0.8, 0.1, 0.4, 0.05, 0.2], "color": "#7800d7"},
        {"name": "Piano",            "w": [1.0, 0.4, 0.1, 0.05, 0.02, 0.01], "color": "#333333"},
        {"name": "Brass",            "w": [1.0, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3], "color": "#ffd700"},
        {"name": "Clarinet",         "w": [1.0, 0.0, 0.7, 0.0, 0.4, 0.0, 0.2], "color": "#8b4513"},
        {"name": "String",           "w": [1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2], "color": "#ff4500"},
        {"name": "Organ",            "w": [1.0, 1.0, 0.5, 0.0, 0.2, 0.0, 0.0, 0.1], "color": "#4682b4"},
        {"name": "Vibe",             "w": [1.0, 0.1, 0.0, 0.0, 0.0, 0.05], "color": "#00ced1"},
        {"name": "Electric Lead",    "w": [1.0, 0.5, 1.0, 0.5, 1.0, 0.5], "color": "#32cd32"},
    ]

    waves = []
    for i, inst in enumerate(instruments):
        data = additive_synth(inst["w"])
        filename = f"wav_{i}_{inst['name'].lower().replace(' ', '_')}.bin"
        waves.append({
            "name": inst["name"],
            "data": data,
            "file": filename,
            "color": inst["color"]
        })

    # --- プロット ---
    fig, axes = plt.subplots(len(waves), 1, figsize=(10, 20), facecolor='#f0f0f0', sharex=True)
    for ax, w in zip(axes, waves):
        ax.step(range(size), w["data"], where='mid', color=w["color"], alpha=0.8)
        ax.set_ylabel(w["name"], rotation=0, labelpad=40, fontweight='bold')
        ax.set_ylim(-130, 130)
        ax.grid(True, alpha=0.2)
        
        # バイナリ保存
        with open(w["file"], "wb") as f:
            f.write(w["data"].tobytes())

    plt.xlabel("Sample Index (0-255)")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    generate_instrument_waves()
