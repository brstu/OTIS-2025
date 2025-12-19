import matplotlib.pyplot as plt
import pandas as pd

# Читаем данные из файла
try:
    data = pd.read_csv("graph_data.txt", sep="\t")
except FileNotFoundError:
    print("Ошибка: файл graph_data.txt не найден!")
    exit(1)

# --- График 1: линейная и нелинейная температура ---
plt.figure(figsize=(10, 6))
plt.plot(data["Time"], data["Linear_Temp"], label="Линейная модель", color="blue", linewidth=2)
plt.plot(data["Time"], data["Nonlinear_Temp"], label="Нелинейная модель", color="red", linestyle="--", linewidth=2)
plt.xlabel("Время (итерации)")
plt.ylabel("Температура")
plt.title("Сравнение линейной и нелинейной модели")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("linear_vs_nonlinear.png", dpi=300)
plt.close()

# --- График 2: значения warm ---
plt.figure(figsize=(10, 6))
plt.plot(data["Time"], data["Warm"], label="Тепловое воздействие (warm)", color="green", marker="o")
plt.xlabel("Время (итерации)")
plt.ylabel("Значение warm")
plt.title("График теплового воздействия")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("warm.png", dpi=300)
plt.close()

print("Графики сохранены: linear_vs_nonlinear.png и warm.png")
