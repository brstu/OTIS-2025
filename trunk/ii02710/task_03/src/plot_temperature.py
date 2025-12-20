"""
@file plot_temperature.py
@brief Скрипт для визуализации данных симуляции PID-регулятора
@details Считывает данные из CSV файла и строит графики температуры и управляющего сигнала
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

def plot_temperature_data(csv_file='temperature_data.csv'):
    """
    @brief Строит графики по данным из CSV файла
    @param csv_file Имя CSV файла с данными
    """
    
    # Проверяем существование файла
    if not os.path.exists(csv_file):
        print(f"Ошибка: Файл '{csv_file}' не найден!")
        print("Сначала запустите симуляцию на C++")
        return
    
    # Читаем данные из CSV
    try:
        data = pd.read_csv(csv_file)
        print(f"Загружено {len(data)} строк данных")
        print(f"Колонки: {list(data.columns)}")
        
        # Создаем фигуру с несколькими графиками
        fig, axes = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
        
        # 1. График температуры
        axes[0].plot(data['Time'], data['Temperature'], 'b-', linewidth=2, label='Температура')
        axes[0].plot(data['Time'], data['Setpoint'], 'r--', linewidth=2, label='Заданная температура')
        axes[0].set_ylabel('Температура (°C)')
        axes[0].set_title('Система управления температурой с PID-регулятором')
        axes[0].grid(True, alpha=0.3)
        axes[0].legend()
        
        # Вычисляем и отображаем статистику ошибки
        error = data['Setpoint'] - data['Temperature']
        rmse = np.sqrt(np.mean(error**2))
        max_error = np.max(np.abs(error))
        
        # Добавляем текстовую информацию
        stats_text = f'Среднеквадратичная ошибка: {rmse:.2f} °C\nМаксимальная ошибка: {max_error:.2f} °C'
        axes[0].text(0.02, 0.98, stats_text, transform=axes[0].transAxes,
                    verticalalignment='top', bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
        
        # 2. График управляющего сигнала
        axes[1].plot(data['Time'], data['Control_Signal'], 'g-', linewidth=2)
        axes[1].fill_between(data['Time'], 0, data['Control_Signal'], alpha=0.3, color='green')
        axes[1].set_ylabel('Управляющий сигнал (%)')
        axes[1].set_ylim([0, 105])
        axes[1].grid(True, alpha=0.3)
        axes[1].set_title('Сигнал управления нагревателем')
        
        # 3. График ошибки регулирования
        axes[2].plot(data['Time'], error, 'r-', linewidth=1.5)
        axes[2].axhline(y=0, color='k', linestyle='-', linewidth=0.5)
        axes[2].fill_between(data['Time'], 0, error, where=(error >= 0), 
                            alpha=0.3, color='red', interpolate=True)
        axes[2].fill_between(data['Time'], 0, error, where=(error < 0), 
                            alpha=0.3, color='blue', interpolate=True)
        axes[2].set_xlabel('Время (секунды)')
        axes[2].set_ylabel('Ошибка (°C)')
        axes[2].grid(True, alpha=0.3)
        axes[2].set_title('Ошибка регулирования')
        
        # Настраиваем общий вид
        plt.suptitle('Анализ работы PID-регулятора', fontsize=14, fontweight='bold')
        plt.tight_layout()
        
        # Сохраняем график
        plt.savefig('temperature_plot.png', dpi=300, bbox_inches='tight')
        plt.savefig('temperature_plot.pdf', bbox_inches='tight')
        
        # Показываем график
        plt.show()
        
        # Выводим статистику в консоль
        print("\n=== Статистика ===")
        print(f"Временной диапазон: {data['Time'].min():.1f} - {data['Time'].max():.1f} с")
        print(f"Средняя температура: {data['Temperature'].mean():.2f} °C")
        print(f"Среднее управляющее воздействие: {data['Control_Signal'].mean():.2f} %")
        print(f"Среднеквадратичная ошибка (RMSE): {rmse:.2f} °C")
        print(f"Максимальная ошибка: {max_error:.2f} °C")
        
    except Exception as e:
        print(f"Ошибка при обработке файла: {e}")

def plot_phase_plane(csv_file='temperature_data.csv'):
    """
    @brief Строит фазовый портрет системы
    @param csv_file Имя CSV файла с данными
    """
    
    try:
        data = pd.read_csv(csv_file)
        
        # Вычисляем производную температуры (скорость изменения)
        temp_diff = np.diff(data['Temperature']) / np.diff(data['Time'])
        # Добавляем NaN в начало для выравнивания размеров
        temp_diff = np.insert(temp_diff, 0, np.nan)
        
        # Создаем график фазового портрета
        plt.figure(figsize=(10, 6))
        
        # Используем цвет для обозначения времени
        scatter = plt.scatter(data['Temperature'][1:], temp_diff[1:], 
                             c=data['Time'][1:], cmap='viridis', 
                             s=20, alpha=0.7)
        
        plt.xlabel('Температура (°C)')
        plt.ylabel('dT/dt (°C/с)')
        plt.title('Фазовый портрет системы управления температурой')
        plt.grid(True, alpha=0.3)
        
        # Добавляем цветовую шкалу для времени
        cbar = plt.colorbar(scatter)
        cbar.set_label('Время (с)')
        
        # Сохраняем график
        plt.savefig('phase_plane.png', dpi=300, bbox_inches='tight')
        plt.show()
        
    except Exception as e:
        print(f"Ошибка при построении фазового портрета: {e}")

def analyze_performance(csv_file='temperature_data.csv'):
    """
    @brief Анализирует производительность системы
    @param csv_file Имя CSV файла с данными
    """
    
    try:
        data = pd.read_csv(csv_file)
        
        # Находим моменты изменения заданной температуры
        setpoint_changes = np.where(np.diff(data['Setpoint']) != 0)[0]
        
        if len(setpoint_changes) > 0:
            print("\n=== Анализ переходных процессов ===")
            
            for i, change_idx in enumerate(setpoint_changes):
                if change_idx < len(data) - 10:
                    start_time = data['Time'][change_idx]
                    new_setpoint = data['Setpoint'][change_idx + 1]
                    old_setpoint = data['Setpoint'][change_idx]
                    
                    print(f"\nИзменение {i+1}: {old_setpoint:.1f} → {new_setpoint:.1f} °C в {start_time:.1f} с")
                    
                    # Анализируем переходный процесс
                    window = data.iloc[change_idx:change_idx + 100]
                    
                    if len(window) > 1:
                        # Время установления (в пределах 5%)
                        tolerance = 0.05 * abs(new_setpoint - old_setpoint)
                        settled_idx = window.index[np.abs(window['Temperature'] - new_setpoint) < tolerance]
                        
                        if len(settled_idx) > 0:
                            settle_time = window.loc[settled_idx[0], 'Time'] - start_time
                            print(f"  Время установления: {settle_time:.2f} с")
                        
                        # Перерегулирование
                        if new_setpoint > old_setpoint:
                            max_temp = window['Temperature'].max()
                            overshoot = ((max_temp - new_setpoint) / (new_setpoint - old_setpoint)) * 100
                            print(f"  Перерегулирование: {overshoot:.1f} %")
        
        # Анализ стационарного режима
        steady_state_data = data[data['Time'] > 80]  # Последние 20 секунд
        
        if len(steady_state_data) > 0:
            print("\n=== Анализ стационарного режима ===")
            temp_std = steady_state_data['Temperature'].std()
            control_std = steady_state_data['Control_Signal'].std()
            
            print(f"Стандартное отклонение температуры: {temp_std:.3f} °C")
            print(f"Стандартное отклонение управления: {control_std:.2f} %")
            
            # Коэффициент использования энергии
            avg_control = steady_state_data['Control_Signal'].mean()
            print(f"Средняя мощность нагрева: {avg_control:.1f} %")
    
    except Exception as e:
        print(f"Ошибка при анализе производительности: {e}")

if __name__ == "__main__":
    print("Запуск анализа данных PID-регулятора...")
    print("=" * 50)
    
    # Основной график
    plot_temperature_data()
    
    # Фазовый портрет
    try:
        plot_phase_plane()
    except:
        print("\nНе удалось построить фазовый портрет")
    
    # Анализ производительности
    analyze_performance()
    
    print("\n" + "=" * 50)
    print("Анализ завершен. Графики сохранены в файлы:")
    print("  - temperature_plot.png")
    print("  - temperature_plot.pdf")
    print("  - phase_plane.png (если доступно)")