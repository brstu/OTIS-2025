<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Документация проекта "Liza Proj" | Лабораторная работа №3</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
            background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
            color: #333;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.1);
        }
        
        header {
            text-align: center;
            margin-bottom: 40px;
            padding-bottom: 20px;
            border-bottom: 3px solid #4CAF50;
        }
        
        h1 {
            color: #2c3e50;
            font-size: 2.5em;
            margin-bottom: 10px;
        }
        
        .subtitle {
            color: #7f8c8d;
            font-size: 1.2em;
            margin-bottom: 20px;
        }
        
        .project-info {
            background: #f8f9fa;
            padding: 20px;
            border-radius: 10px;
            margin: 20px 0;
            border-left: 5px solid #3498db;
        }
        
        .file-section {
            background: #fff;
            border: 1px solid #ddd;
            border-radius: 10px;
            padding: 25px;
            margin: 30px 0;
            transition: transform 0.3s ease;
        }
        
        .file-section:hover {
            transform: translateY(-5px);
            box-shadow: 0 15px 35px rgba(0,0,0,0.1);
        }
        
        .file-header {
            color: #2c3e50;
            font-size: 1.8em;
            margin-bottom: 15px;
            display: flex;
            align-items: center;
            gap: 10px;
        }
        
        .file-header i {
            color: #4CAF50;
            font-size: 1.5em;
        }
        
        .function-card {
            background: #f9f9f9;
            border-radius: 8px;
            padding: 20px;
            margin: 15px 0;
            border-left: 4px solid #3498db;
        }
        
        .function-name {
            color: #2c3e50;
            font-weight: bold;
            font-size: 1.2em;
            margin-bottom: 10px;
        }
        
        .param-list {
            background: #e8f4f8;
            padding: 15px;
            border-radius: 5px;
            margin: 10px 0;
        }
        
        .param-item {
            margin: 5px 0;
            padding-left: 20px;
            position: relative;
        }
        
        .param-item:before {
            content: "•";
            color: #3498db;
            position: absolute;
            left: 0;
        }
        
        .class-info {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 25px;
            border-radius: 10px;
            margin: 20px 0;
        }
        
        .class-methods {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }
        
        .method-card {
            background: rgba(255,255,255,0.1);
            padding: 15px;
            border-radius: 8px;
            backdrop-filter: blur(10px);
        }
        
        footer {
            text-align: center;
            margin-top: 50px;
            padding-top: 20px;
            border-top: 1px solid #ddd;
            color: #7f8c8d;
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 15px;
            }
            
            h1 {
                font-size: 2em;
            }
            
            .class-methods {
                grid-template-columns: 1fr;
            }
        }
    </style>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
</head>
<body>
    <div class="container">
        <header>
            <h1><i class="fas fa-project-diagram"></i> Документация проекта "Liza Proj"</h1>
            <div class="subtitle">Лабораторная работа №3: Система автоматического управления с ПИД-регулятором</div>
        </header>
        
        <div class="project-info">
            <h2><i class="fas fa-info-circle"></i> Общая информация о проекте</h2>
            <p>Данный проект реализует систему моделирования ПИД-регулятора для объектов теплового класса. 
            Проект включает в себя полный цикл разработки: от математической модели до визуализации результатов.</p>
        </div>
        
        <!-- Основная программа -->
        <section class="file-section">
            <div class="file-header">
                <i class="fas fa-cogs"></i>
                <span>lab3main.cpp — Главный модуль управления</span>
            </div>
            
            <p><strong>Назначение:</strong> Основной исполняемый файл, координирующий работу всей системы моделирования.</p>
            
            <div class="function-card">
                <div class="function-name">Функция simulateSystem()</div>
                <p><strong>Описание:</strong> Проводит циклическое моделирование системы управления с использованием ПИД-регулятора.</p>
                
                <div class="param-list">
                    <strong>Параметры:</strong>
                    <div class="param-item">pid — экземпляр ПИД-регулятора</div>
                    <div class="param-item">process — модель управляемого процесса</div>
                    <div class="param-item">setpoints — последовательность заданных значений</div>
                    <div class="param-item">use_nonlinear — выбор типа модели (линейная/нелинейная)</div>
                </div>
                
                <div class="param-list">
                    <strong>Возвращаемое значение:</strong>
                    <div class="param-item">vector<double> — массив результатов моделирования</div>
                </div>
            </div>
            
            <div class="function-card">
                <div class="function-name">Функция main()</div>
                <p><strong>Описание:</strong> Точка входа в программу. Инициализирует компоненты, запускает моделирование и сохраняет результаты.</p>
                <p><strong>Основные этапы:</strong></p>
                <div class="param-list">
                    <div class="param-item">Инициализация модели процесса</div>
                    <div class="param-item">Настройка параметров ПИД-регулятора</div>
                    <div class="param-item">Запуск симуляции для двух режимов</div>
                    <div class="param-item">Экспорт данных в CSV формат</div>
                    <div class="param-item">Запуск визуализации результатов</div>
                </div>
            </div>
        </section>
        
        <!-- ПИД-регулятор -->
        <section class="file-section">
            <div class="file-header">
                <i class="fas fa-sliders-h"></i>
                <span>pid.h / pid.cpp — Модуль ПИД-регулятора</span>
            </div>
            
            <div class="class-info">
                <h3><i class="fas fa-microchip"></i> Класс PIDController</h3>
                <p>Реализация дискретного пропорционально-интегрально-дифференциального регулятора с рекуррентным алгоритмом вычислений.</p>
            </div>
            
            <div class="class-methods">
                <div class="method-card">
                    <div class="function-name">Конструктор PIDController()</div>
                    <p>Создает новый экземпляр регулятора с заданными параметрами.</p>
                    <div class="param-list">
                        <strong>Аргументы:</strong>
                        <div class="param-item">K — коэффициент передачи</div>
                        <div class="param-item">T — постоянная интегрирования</div>
                        <div class="param-item">Td — постоянная дифференцирования</div>
                        <div class="param-item">T0 — интервал дискретизации</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="function-name">Метод calculate()</div>
                    <p>Вычисляет управляющее воздействие на основе текущей ошибки.</p>
                    <div class="param-list">
                        <strong>Аргументы:</strong>
                        <div class="param-item">setpoint — целевое значение</div>
                        <div class="param-item">current_value — текущее измерение</div>
                    </div>
                    <div class="param-list">
                        <strong>Возвращает:</strong>
                        <div class="param-item">double — управляющий сигнал</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="function-name">Метод reset()</div>
                    <p>Сбрасывает внутреннее состояние регулятора к начальным значениям.</p>
                    <p><em>Используется при переключении между режимами моделирования.</em></p>
                </div>
                
                <div class="method-card">
                    <div class="function-name">Метод getCoefficients()</div>
                    <p>Возвращает текущие коэффициенты дискретного регулятора.</p>
                    <div class="param-list">
                        <strong>Возвращает:</strong>
                        <div class="param-item">vector<double> — [q0, q1, q2]</div>
                    </div>
                </div>
            </div>
            
            <div class="function-card">
                <div class="function-name">Принцип работы алгоритма</div>
                <p>Реализован рекуррентный алгоритм ПИД-регулятора:</p>
                <div class="param-list">
                    <div class="param-item">u(k) = u(k-1) + q₀·e(k) + q₁·e(k-1) + q₂·e(k-2)</div>
                    <div class="param-item">q₀ = K·(1 + T₀/T + Td/T₀)</div>
                    <div class="param-item">q₁ = -K·(1 + 2·Td/T₀)</div>
                    <div class="param-item">q₂ = K·Td/T₀</div>
                </div>
            </div>
        </section>
        
        <!-- Модель процесса -->
        <section class="file-section">
            <div class="file-header">
                <i class="fas fa-industry"></i>
                <span>model.h / model.cpp — Модель объекта управления</span>
            </div>
            
            <div class="class-info">
                <h3><i class="fas fa-fire"></i> Класс ProcessModel</h3>
                <p>Математическая модель теплового объекта, поддерживающая линейное и нелинейное поведение.</p>
            </div>
            
            <div class="class-methods">
                <div class="method-card">
                    <div class="function-name">Конструктор ProcessModel()</div>
                    <p>Инициализирует модель с заданными параметрами и начальным состоянием.</p>
                    <div class="param-list">
                        <strong>Аргументы:</strong>
                        <div class="param-item">params — вектор коэффициентов модели</div>
                        <div class="param-item">initial_value — начальная температура</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="function-name">Метод linearModel()</div>
                    <p>Вычисляет выходное значение по линейной модели объекта.</p>
                    <div class="param-list">
                        <strong>Аргумент:</strong>
                        <div class="param-item">input — входное воздействие</div>
                    </div>
                    <div class="param-list">
                        <strong>Возвращает:</strong>
                        <div class="param-item">double — выходное значение</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="function-name">Метод nonlinearModel()</div>
                    <p>Вычисляет выходное значение по нелинейной модели с учетом дополнительных эффектов.</p>
                    <div class="param-list">
                        <strong>Аргумент:</strong>
                        <div class="param-item">input — входное воздействие</div>
                    </div>
                    <div class="param-list">
                        <strong>Возвращает:</strong>
                        <div class="param-item">double — выходное значение</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="function-name">Метод setInitialValue()</div>
                    <p>Устанавливает начальное состояние модели.</p>
                    <div class="param-list">
                        <strong>Аргумент:</strong>
                        <div class="param-item">value — начальное значение</div>
                    </div>
                </div>
            </div>
            
            <div class="function-card">
                <div class="function-name">Математические модели</div>
                <p>В проекте реализованы две модели объекта:</p>
                <div class="param-list">
                    <div class="param-item"><strong>Линейная:</strong> y(k) = a₁·y(k-1) + b₁·u(k)</div>
                    <div class="param-item"><strong>Нелинейная:</strong> y(k) = a₂·y(k-1) - c·y²(k-1) + b₂·u(k) + d·sin(u(k))</div>
                </div>
            </div>
        </section>
        
        <!-- Визуализация -->
        <section class="file-section">
            <div class="file-header">
                <i class="fas fa-chart-line"></i>
                <span>plot_utils.h / plot_utils.cpp — Модуль визуализации</span>
            </div>
            
            <div class="function-card">
                <div class="function-name">Функция generatePythonPlotScript()</div>
                <p><strong>Назначение:</strong> Генерирует и запускает Python-скрипт для визуализации результатов моделирования.</p>
                
                <div class="param-list">
                    <strong>Создаваемые выходные данные:</strong>
                    <div class="param-item">simulation_results.csv — табличные данные</div>
                    <div class="param-item">pid_report.html — интерактивный отчет</div>
                    <div class="param-item">Консольные графики в ASCII-формате</div>
                    <div class="param-item">Текстовая статистика результатов</div>
                </div>
                
                <p><em>Функция автоматически проверяет наличие входных данных и генерирует демонстрационные данные при их отсутствии.</em></p>
            </div>
        </section>
        
        <footer>
            <p><i class="fas fa-graduation-cap"></i> Брестский Государственный технический университет | Кафедра ИИТ</p>
            <p>Лабораторная работа №3 по дисциплине "Общая теория интеллектуальных систем"</p>
            <p>Выполнил: Литвинчук И.М., группа ИИ-28/24 | Проверил: Дворанинович Д.А.</p>
            <p><i class="far fa-copyright"></i> 2025</p>
        </footer>
    </div>
</body>
</html>