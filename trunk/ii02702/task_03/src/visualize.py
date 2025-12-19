import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
from datetime import datetime

# Константы для подписей графиков
SETPOINT_LABEL = "Заданное значение"
TEMPERATURE_LABEL = "Температура (°C)"
TIME_LABEL = "Время (шаги)"
ERROR_LABEL = "Ошибка (°C)"
CONTROL_LABEL = "Управляющее воздействие"
CONTROL_Y_LABEL = "Управление"  # Добавлена константа для оси Y
PLOT_TITLE = "Сравнение систем регулирования температуры"

# Константы для легенд
TEMPERATURE_LEGEND = "Температура"  # Добавлена константа для легенды
WITHOUT_CONTROLLER_LEGEND = "Без регулятора"  # Константа для системы без регулятора
WITH_PID_LEGEND = "С ПИД-регулятором"  # Константа для системы с регулятором
ERROR_WITHOUT_LEGEND = "Ошибка без регулятора"  # Константа для ошибки без регулятора
ERROR_WITH_LEGEND = "Ошибка с ПИД"  # Константа для ошибки с регулятором
START_LEGEND = "Начало"  # Константа для начала на графике
END_LEGEND = "Конец"  # Константа для конца на графике

# Константы для стилей графика
GRID_ALPHA = 0.3
LINE_WIDTH = 2
PLOT_FIGSIZE = (14, 12)
TITLE_FONTSIZE = 16
TITLE_FONTWEIGHT = 'bold'
BBOX_STYLE = {'boxstyle': 'round', 'facecolor': 'wheat', 'alpha': 0.5}
TEXT_VERTICAL_ALIGNMENT = 'top'
STATS_TEXT_POSITION = (0.02, 0.98)

# Константы для заголовков графиков
LINEAR_NO_CONTROL_TITLE = 'Без регулятора (постоянный нагрев)'
LINEAR_WITH_CONTROL_TITLE = 'С ПИД-регулятором'
LINEAR_COMPARISON_TITLE = 'Сравнение обеих систем'
LINEAR_ERROR_TITLE = 'Отклонение от заданного значения'
LINEAR_CONTROL_TITLE = 'Управляющее воздействие ПИД-регулятора'
LINEAR_PHASE_TITLE = 'Фазовый портрет (температура vs управление)'

NONLINEAR_NO_CONTROL_TITLE = 'Нелинейная система без регулятора'
NONLINEAR_WITH_CONTROL_TITLE = 'Нелинейная система с ПИД-регулятором'
NONLINEAR_COMPARISON_TITLE = 'Сравнение нелинейных систем'
NONLINEAR_CONTROL_TITLE = 'Управляющее воздействие (нелинейная система)'

def read_temperature_data(filename):
    """Чтение данных температуры из CSV файла"""
    try:
        df = pd.read_csv(filename)
        print(f"Загружено {len(df)} записей из {filename}")
        return df
    except FileNotFoundError:
        print(f"Файл {filename} не найден")
        return None

def plot_linear_comparison():
    """Построение графиков сравнения для линейной системы"""
    
    files = {
        'without': 'temperature_linear_without_pid.csv',
        'with': 'temperature_linear_with_pid.csv'
    }
    
    if not all(os.path.exists(f) for f in files.values()):
        print("Файлы с данными не найдены. Сначала запустите C++ программу.")
        return
    
    df_without = read_temperature_data(files['without'])
    df_with = read_temperature_data(files['with'])
    
    if df_without is None or df_with is None:
        return
    
    fig, axes = plt.subplots(3, 2, figsize=PLOT_FIGSIZE)
    fig.suptitle('Линейная система: сравнение с ПИД-регулятором и без', 
                 fontsize=TITLE_FONTSIZE, fontweight=TITLE_FONTWEIGHT)
    
    # График 1: Без регулятора
    ax1 = axes[0, 0]
    ax1.plot(df_without['Time'], df_without['Value'], 'r-', 
             linewidth=LINE_WIDTH, label=TEMPERATURE_LEGEND)
    
    if 'Setpoint' in df_without.columns:
        setpoint_value = df_without['Setpoint'].iloc[0]
        if setpoint_value > 0:
            ax1.axhline(y=setpoint_value, color='g', linestyle='--', 
                       linewidth=LINE_WIDTH, label=SETPOINT_LABEL)
    
    ax1.set_xlabel(TIME_LABEL)
    ax1.set_ylabel(TEMPERATURE_LABEL)
    ax1.set_title(LINEAR_NO_CONTROL_TITLE)
    ax1.grid(True, alpha=GRID_ALPHA)
    ax1.legend()
    
    # График 2: С регулятором
    ax2 = axes[0, 1]
    ax2.plot(df_with['Time'], df_with['Value'], 'b-', 
             linewidth=LINE_WIDTH, label=TEMPERATURE_LEGEND)
    
    if 'Setpoint' in df_with.columns:
        setpoint_value = df_with['Setpoint'].iloc[0]
        ax2.axhline(y=setpoint_value, color='g', linestyle='--', 
                   linewidth=LINE_WIDTH, label=SETPOINT_LABEL)
    
    ax2.set_xlabel(TIME_LABEL)
    ax2.set_ylabel(TEMPERATURE_LABEL)
    ax2.set_title(LINEAR_WITH_CONTROL_TITLE)
    ax2.grid(True, alpha=GRID_ALPHA)
    ax2.legend()
    
    # График 3: Сравнение обеих систем
    ax3 = axes[1, 0]
    ax3.plot(df_without['Time'], df_without['Value'], 'r-', 
             linewidth=LINE_WIDTH, label=WITHOUT_CONTROLLER_LEGEND)
    ax3.plot(df_with['Time'], df_with['Value'], 'b-', 
             linewidth=LINE_WIDTH, label=WITH_PID_LEGEND)
    
    if 'Setpoint' in df_with.columns:
        setpoint_value = df_with['Setpoint'].iloc[0]
        ax3.axhline(y=setpoint_value, color='g', linestyle='--', 
                   linewidth=LINE_WIDTH, label=SETPOINT_LABEL)
    
    ax3.set_xlabel(TIME_LABEL)
    ax3.set_ylabel(TEMPERATURE_LABEL)
    ax3.set_title(LINEAR_COMPARISON_TITLE)
    ax3.grid(True, alpha=GRID_ALPHA)
    ax3.legend()
    
    # График 4: Ошибки регулирования
    ax4 = axes[1, 1]
    if 'Setpoint' in df_with.columns:
        setpoint_value = df_with['Setpoint'].iloc[0]
        error_without = np.abs(df_without['Value'] - setpoint_value)
        error_with = np.abs(df_with['Value'] - setpoint_value)
        
        ax4.plot(df_without['Time'], error_without, 'r-', 
                 linewidth=LINE_WIDTH, label=ERROR_WITHOUT_LEGEND)
        ax4.plot(df_with['Time'], error_with, 'b-', 
                 linewidth=LINE_WIDTH, label=ERROR_WITH_LEGEND)
        ax4.set_xlabel(TIME_LABEL)
        ax4.set_ylabel(ERROR_LABEL)
        ax4.set_title(LINEAR_ERROR_TITLE)
        ax4.grid(True, alpha=GRID_ALPHA)
        ax4.legend()
        
        # Статистика
        avg_error_without = error_without.mean()
        avg_error_with = error_with.mean()
        improvement = ((avg_error_without - avg_error_with) / avg_error_without) * 100
        
        stats_text = f'Средняя ошибка без ПИД: {avg_error_without:.3f} °C\n'
        stats_text += f'Средняя ошибка с ПИД: {avg_error_with:.3f} °C\n'
        stats_text += f'Улучшение: {improvement:.1f}%'
        
        ax4.text(STATS_TEXT_POSITION[0], STATS_TEXT_POSITION[1], 
                stats_text, transform=ax4.transAxes,
                verticalalignment=TEXT_VERTICAL_ALIGNMENT, 
                bbox=BBOX_STYLE)
    
    # График 5: Управляющее воздействие
    ax5 = axes[2, 0]
    if 'Control' in df_with.columns:
        ax5.plot(df_with['Time'], df_with['Control'], 'g-', 
                 linewidth=LINE_WIDTH, label=CONTROL_LABEL)
        ax5.set_xlabel(TIME_LABEL)
        ax5.set_ylabel(CONTROL_Y_LABEL)  # Используем константу
        ax5.set_title(LINEAR_CONTROL_TITLE)
        ax5.grid(True, alpha=GRID_ALPHA)
        ax5.legend()
    
    # График 6: Фазовый портрет
    ax6 = axes[2, 1]
    if 'Control' in df_with.columns and 'Value' in df_with.columns:
        ax6.plot(df_with['Value'][:-1], df_with['Control'][1:], 'purple', 
                 linewidth=LINE_WIDTH, alpha=0.7)
        ax6.scatter(df_with['Value'][0], df_with['Control'][1], 
                   color='red', s=100, label=START_LEGEND, zorder=5)
        ax6.scatter(df_with['Value'].iloc[-1], df_with['Control'].iloc[-1], 
                   color='green', s=100, label=END_LEGEND, zorder=5)
        ax6.set_xlabel(TEMPERATURE_LABEL)
        ax6.set_ylabel(CONTROL_Y_LABEL)  # Используем константу
        ax6.set_title(LINEAR_PHASE_TITLE)
        ax6.grid(True, alpha=GRID_ALPHA)
        ax6.legend()
    
    plt.tight_layout()
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_filename = f"linear_comparison_{timestamp}.png"
    plt.savefig(output_filename, dpi=300, bbox_inches='tight')
    print(f"\nГрафики сохранены в файл: {output_filename}")
    
    plt.show()

def plot_nonlinear_comparison():
    """Построение графиков сравнения для нелинейной системы"""
    
    files = {
        'without': 'temperature_nonlinear_without_pid.csv',
        'with': 'temperature_nonlinear_with_pid.csv'
    }
    
    if not all(os.path.exists(f) for f in files.values()):
        print("Файлы с данными не найдены.")
        return
    
    df_without = read_temperature_data(files['without'])
    df_with = read_temperature_data(files['with'])
    
    if df_without is None or df_with is None:
        return
    
    fig, axes = plt.subplots(2, 2, figsize=(14, 8))
    fig.suptitle('Нелинейная система: сравнение с ПИД-регулятором и без', 
                 fontsize=TITLE_FONTSIZE, fontweight=TITLE_FONTWEIGHT)
    
    # График 1: Без регулятора
    ax1 = axes[0, 0]
    ax1.plot(df_without['Time'], df_without['Value'], 'r-', 
             linewidth=LINE_WIDTH, label=TEMPERATURE_LEGEND)
    
    if 'Setpoint' in df_without.columns:
        setpoint_value = df_without['Setpoint'].iloc[0]
        if setpoint_value > 0:
            ax1.axhline(y=setpoint_value, color='g', linestyle='--', 
                       linewidth=LINE_WIDTH, label=SETPOINT_LABEL)
    
    ax1.set_xlabel(TIME_LABEL)
    ax1.set_ylabel(TEMPERATURE_LABEL)
    ax1.set_title(NONLINEAR_NO_CONTROL_TITLE)
    ax1.grid(True, alpha=GRID_ALPHA)
    ax1.legend()
    
    # График 2: С регулятором
    ax2 = axes[0, 1]
    ax2.plot(df_with['Time'], df_with['Value'], 'b-', 
             linewidth=LINE_WIDTH, label=TEMPERATURE_LEGEND)
    
    if 'Setpoint' in df_with.columns:
        setpoint_value = df_with['Setpoint'].iloc[0]
        ax2.axhline(y=setpoint_value, color='g', linestyle='--', 
                   linewidth=LINE_WIDTH, label=SETPOINT_LABEL)
    
    ax2.set_xlabel(TIME_LABEL)
    ax2.set_ylabel(TEMPERATURE_LABEL)
    ax2.set_title(NONLINEAR_WITH_CONTROL_TITLE)
    ax2.grid(True, alpha=GRID_ALPHA)
    ax2.legend()
    
    # График 3: Сравнение обеих систем
    ax3 = axes[1, 0]
    ax3.plot(df_without['Time'], df_without['Value'], 'r-', 
             linewidth=LINE_WIDTH, label=WITHOUT_CONTROLLER_LEGEND)
    ax3.plot(df_with['Time'], df_with['Value'], 'b-', 
             linewidth=LINE_WIDTH, label=WITH_PID_LEGEND)
    
    if 'Setpoint' in df_with.columns:
        setpoint_value = df_with['Setpoint'].iloc[0]
        ax3.axhline(y=setpoint_value, color='g', linestyle='--', 
                   linewidth=LINE_WIDTH, label=SETPOINT_LABEL)
    
    ax3.set_xlabel(TIME_LABEL)
    ax3.set_ylabel(TEMPERATURE_LABEL)
    ax3.set_title(NONLINEAR_COMPARISON_TITLE)
    ax3.grid(True, alpha=GRID_ALPHA)
    ax3.legend()
    
    # График 4: Управляющее воздействие
    ax4 = axes[1, 1]
    if 'Control' in df_with.columns:
        ax4.plot(df_with['Time'], df_with['Control'], 'g-', 
                 linewidth=LINE_WIDTH, label=CONTROL_LABEL)
        ax4.set_xlabel(TIME_LABEL)
        ax4.set_ylabel(CONTROL_Y_LABEL)  # Используем константу
        ax4.set_title(NONLINEAR_CONTROL_TITLE)
        ax4.grid(True, alpha=GRID_ALPHA)
        ax4.legend()
    
    plt.tight_layout()
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_filename = f"nonlinear_comparison_{timestamp}.png"
    plt.savefig(output_filename, dpi=300, bbox_inches='tight')
    print(f"Графики сохранены в файл: {output_filename}")
    
    plt.show()

def main():
    """Основная функция"""
    print("="*60)
    print("ВИЗУАЛИЗАЦИЯ РЕЗУЛЬТАТОВ МОДЕЛИРОВАНИЯ ТЕМПЕРАТУРЫ")
    print("="*60)

    plot_linear_comparison()
    plot_nonlinear_comparison()

if __name__ == "__main__":
    main()