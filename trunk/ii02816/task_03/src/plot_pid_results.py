#!/usr/bin/env python3
"""
Упрощенный скрипт для визуализации результатов PID-контроллера
Работает со стандартными библиотеками Python
"""

import csv
import sys
import os
from datetime import datetime

def read_csv_data(filename):
    """Чтение CSV файла без pandas"""
    data = {
        'Step': [],
        'Setpoint': [],
        'Linear_Output': [],
        'Nonlinear_Output': []
    }
    
    try:
        with open(filename, 'r') as f:
            reader = csv.DictReader(f)
            for row in reader:
                data['Step'].append(int(row['Step']))
                data['Setpoint'].append(float(row['Setpoint']))
                data['Linear_Output'].append(float(row['Linear_Output']))
                data['Nonlinear_Output'].append(float(row['Nonlinear_Output']))
        print(f"Successfully read {len(data['Step'])} rows from {filename}")
        return data
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found!")
        print("Please run the C++ program first to generate data.")
        return None
    except KeyError as e:
        print(f"Error: Missing column in CSV: {e}")
        return None

def _calculate_scale_params(data):
    """Вычисление параметров масштабирования"""
    all_values = data['Linear_Output'] + data['Nonlinear_Output'] + data['Setpoint']
    y_min = min(all_values)
    y_max = max(all_values)
    y_range = y_max - y_min if y_max != y_min else 1
    return y_min, y_range

def _scale_data(data, y_min, y_range, height):
    """Масштабирование данных"""
    scaled_data = {}
    for key in ['Setpoint', 'Linear_Output', 'Nonlinear_Output']:
        scaled_data[key] = [
            int((val - y_min) * (height - 1) / y_range)
            for val in data[key]
        ]
    return scaled_data

def _get_plot_characters(scaled_data, x, y):
    """Определение символов для точки графика"""
    chars = []
    if scaled_data['Setpoint'][x] == y:
        chars.append('S')
    if scaled_data['Linear_Output'][x] == y:
        chars.append('L')
    if scaled_data['Nonlinear_Output'][x] == y:
        chars.append('N')
    return chars[0] if chars else ' '

def _build_x_axis_labels(data):
    """Построение подписей оси X"""
    x_labels = " " * 8 + " "
    step_count = len(data['Step'])
    step_size = max(1, step_count // 10)
    
    for i in range(0, step_count, step_size):
        if i < step_count:
            x_labels += f"{data['Step'][i]:<8}"
    return x_labels

def _print_plot_header():
    """Вывод заголовка графика"""
    print("\n" + "=" * 80)
    print("ASCII PLOT - PID Controller Results")
    print("=" * 80)

def generate_ascii_plot(data, width=80, height=20):
    """Генерация ASCII графика в консоли"""
    _print_plot_header()
    
    # Масштабирование данных
    y_min, y_range = _calculate_scale_params(data)
    scaled_data = _scale_data(data, y_min, y_range, height)
    
    # Подготовка параметров для построения
    step_count = len(data['Step'])
    x_step = max(1, step_count // width)
    
    # Построение графика строка за строкой
    for y in range(height-1, -1, -1):
        line = f"{y + y_min:6.1f} | "
        
        for x in range(0, step_count, x_step):
            if x < step_count:
                line += _get_plot_characters(scaled_data, x, y)
            else:
                line += ' '
        
        print(line)
    
    # Ось X и подписи
    print(" " * 8 + "+" + "-" * width)
    
    x_labels = _build_x_axis_labels(data)
    print(x_labels)
    print("\nLegend: S=Setpoint, L=Linear, N=Nonlinear")

def _calculate_error_statistics(data):
    """Вычисление статистики ошибок"""
    linear_errors = []
    nonlinear_errors = []
    
    for i in range(len(data['Step'])):
        lin_err = data['Setpoint'][i] - data['Linear_Output'][i]
        nonlin_err = data['Setpoint'][i] - data['Nonlinear_Output'][i]
        linear_errors.append(lin_err)
        nonlinear_errors.append(nonlin_err)
    
    return linear_errors, nonlinear_errors

def _calculate_model_stats(errors):
    """Вычисление статистики для модели"""
    if not errors:
        return {'mean_error': 0, 'max_error': 0, 'min_error': 0, 'rmse': 0}
    
    mean_error = sum(errors) / len(errors)
    max_error = max(errors)
    min_error = min(errors)
    rmse = (sum(e*e for e in errors) / len(errors)) ** 0.5
    
    return {
        'mean_error': mean_error,
        'max_error': max_error,
        'min_error': min_error,
        'rmse': rmse
    }

def generate_html_report(data):
    """Генерация HTML отчета с текстовой статистикой"""
    if not data:
        return
    
    # Вычисляем ошибки и статистику
    linear_errors, nonlinear_errors = _calculate_error_statistics(data)
    
    stats = {
        'Linear': _calculate_model_stats(linear_errors),
        'Nonlinear': _calculate_model_stats(nonlinear_errors)
    }
    
    # Генерация HTML
    html_content = f"""<!DOCTYPE html>
<html>
<head>
    <title>PID Controller Report</title>
    <style>
        body {{ font-family: Arial, sans-serif; margin: 40px; }}
        .container {{ max-width: 1200px; margin: 0 auto; }}
        .header {{ background: #2c3e50; color: white; padding: 20px; text-align: center; }}
        .stats {{ display: grid; grid-template-columns: 1fr 1fr; gap: 20px; margin: 20px 0; }}
        .stat-box {{ background: #f8f9fa; border: 1px solid #dee2e6; padding: 15px; border-radius: 5px; }}
        table {{ width: 100%; border-collapse: collapse; margin: 20px 0; }}
        th, td {{ border: 1px solid #ddd; padding: 8px; text-align: center; }}
        th {{ background-color: #4CAF50; color: white; }}
        tr:nth-child(even) {{ background-color: #f2f2f2; }}
        .timestamp {{ color: #666; font-size: 0.9em; margin-top: 20px; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>PID Controller Simulation Report</h1>
            <p>Analysis of Linear vs Nonlinear Models</p>
        </div>
        
        <div class="stats">
            <div class="stat-box">
                <h3>Linear Model Statistics</h3>
                <p>Mean Error: {stats['Linear']['mean_error']:.4f}</p>
                <p>Max Error: {stats['Linear']['max_error']:.4f}</p>
                <p>Min Error: {stats['Linear']['min_error']:.4f}</p>
                <p>RMSE: {stats['Linear']['rmse']:.4f}</p>
            </div>
            
            <div class="stat-box">
                <h3>Nonlinear Model Statistics</h3>
                <p>Mean Error: {stats['Nonlinear']['mean_error']:.4f}</p>
                <p>Max Error: {stats['Nonlinear']['max_error']:.4f}</p>
                <p>Min Error: {stats['Nonlinear']['min_error']:.4f}</p>
                <p>RMSE: {stats['Nonlinear']['rmse']:.4f}</p>
            </div>
        </div>
        
        <h2>Simulation Data</h2>
        <table>
            <thead>
                <tr>
                    <th>Step</th>
                    <th>Setpoint</th>
                    <th>Linear Output</th>
                    <th>Nonlinear Output</th>
                    <th>Linear Error</th>
                    <th>Nonlinear Error</th>
                </tr>
            </thead>
            <tbody>
"""
    
    # Добавляем строки данных
    for i in range(min(50, len(data['Step']))):
        lin_err = data['Setpoint'][i] - data['Linear_Output'][i]
        nonlin_err = data['Setpoint'][i] - data['Nonlinear_Output'][i]
        html_content += f"""
                <tr>
                    <td>{data['Step'][i]}</td>
                    <td>{data['Setpoint'][i]:.4f}</td>
                    <td>{data['Linear_Output'][i]:.4f}</td>
                    <td>{data['Nonlinear_Output'][i]:.4f}</td>
                    <td style="color: {'red' if abs(lin_err) > 1 else 'green'}">{lin_err:.4f}</td>
                    <td style="color: {'red' if abs(nonlin_err) > 1 else 'green'}">{nonlin_err:.4f}</td>
                </tr>
"""
    
    html_content += f"""
            </tbody>
        </table>
        
        <div class="timestamp">
            Report generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}
        </div>
    </div>
</body>
</html>
"""
    
    # Сохраняем HTML файл
    with open('pid_report.html', 'w', encoding='utf-8') as f:
        f.write(html_content)
    
    print("\nHTML report generated: pid_report.html")
    print("Open this file in your web browser to view the report.")

def print_text_summary(data):
    """Вывод текстовой сводки результатов"""
    if not data:
        return
    
    print("\n" + "="*60)
    print("TEXT SUMMARY - PID Controller Simulation")
    print("="*60)
    
    # Выводим первые 10 строк таблицы
    print("\nFirst 10 steps of simulation:")
    print("-"*60)
    print(f"{'Step':>6} {'Setpoint':>10} {'Linear':>10} {'Nonlinear':>10} {'L-Error':>10} {'NL-Error':>10}")
    print("-"*60)
    
    for i in range(min(10, len(data['Step']))):
        lin_err = data['Setpoint'][i] - data['Linear_Output'][i]
        nonlin_err = data['Setpoint'][i] - data['Nonlinear_Output'][i]
        print(f"{data['Step'][i]:6d} {data['Setpoint'][i]:10.4f} {data['Linear_Output'][i]:10.4f} "
              f"{data['Nonlinear_Output'][i]:10.4f} {lin_err:10.4f} {nonlin_err:10.4f}")
    
    # Вычисляем статистику
    linear_errors, nonlinear_errors = _calculate_error_statistics(data)
    lin_stats = _calculate_model_stats(linear_errors)
    nonlin_stats = _calculate_model_stats(nonlinear_errors)
    
    print("\n" + "="*60)
    print("STATISTICS:")
    print("="*60)
    print(f"{'Metric':<20} {'Linear Model':>15} {'Nonlinear Model':>15}")
    print("-"*60)
    print(f"{'Mean Error':<20} {lin_stats['mean_error']:15.4f} {nonlin_stats['mean_error']:15.4f}")
    print(f"{'Max Error':<20} {lin_stats['max_error']:15.4f} {nonlin_stats['max_error']:15.4f}")
    print(f"{'Min Error':<20} {lin_stats['min_error']:15.4f} {nonlin_stats['min_error']:15.4f}")
    print(f"{'RMSE':<20} {lin_stats['rmse']:15.4f} {nonlin_stats['rmse']:15.4f}")
    print(f"{'Data Points':<20} {len(data['Step']):15d} {len(data['Step']):15d}")

def main():
    """Основная функция"""
    print("PID Controller Results Visualizer")
    print("="*40)
    
    # Проверяем аргументы командной строки
    csv_file = 'simulation_results.csv'
    if len(sys.argv) > 1:
        csv_file = sys.argv[1]
    
    # Читаем данные
    data = read_csv_data(csv_file)
    if not data:
        print("\nCreating sample data for demonstration...")
        # Создаем демонстрационные данные
        data = {
            'Step': list(range(100)),
            'Setpoint': [20.0] * 100,
            'Linear_Output': [20 * (1 - (0.9 ** i)) for i in range(100)],
            'Nonlinear_Output': [20 * (1 - (0.85 ** i)) for i in range(100)]
        }
    
    # Выводим различные представления
    print_text_summary(data)
    
    # ASCII график
    generate_ascii_plot(data)
    
    # HTML отчет
    generate_html_report(data)
    
    print("\n" + "="*40)
    print("Visualization complete!")
    print("="*40)
    print("\nAvailable outputs:")
    print("1. Text summary (above)")
    print("2. ASCII plot (above)")
    print("3. HTML report: pid_report.html")

if __name__ == "__main__":
    main()