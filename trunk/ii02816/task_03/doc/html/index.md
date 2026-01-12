<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Проект Liza Proj | Лабораторная работа №3</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
            background: linear-gradient(145deg, #0a192f 0%, #172a45 100%);
            color: #e6f1ff;
        }
        
        .wrapper {
            max-width: 1100px;
            margin: 0 auto;
            background: rgba(23, 42, 69, 0.9);
            padding: 30px;
            border-radius: 12px;
            border: 1px solid #233554;
        }
        
        .header-area {
            text-align: center;
            margin-bottom: 35px;
            padding-bottom: 20px;
            border-bottom: 2px solid #64ffda;
        }
        
        .main-title {
            color: #ccd6f6;
            font-size: 2.4em;
            margin: 0 0 10px;
            letter-spacing: 1px;
        }
        
        .tagline {
            color: #8892b0;
            font-size: 1.1em;
        }
        
        .info-panel {
            background: #112240;
            padding: 22px;
            border-radius: 10px;
            margin: 22px 0;
            border-left: 4px solid #64ffda;
        }
        
        .module {
            background: #0d1b2a;
            border: 1px solid #1d2d3f;
            border-radius: 10px;
            padding: 25px;
            margin: 28px 0;
        }
        
        .module-title {
            color: #64ffda;
            font-size: 1.7em;
            margin: 0 0 18px;
            display: flex;
            align-items: center;
            gap: 12px;
        }
        
        .method-block {
            background: #1a2a3a;
            border-radius: 8px;
            padding: 18px;
            margin: 16px 0;
            border: 1px solid #2d4059;
        }
        
        .method-name {
            color: #ffd166;
            font-weight: bold;
            font-size: 1.2em;
            margin-bottom: 10px;
        }
        
        .params {
            background: #152642;
            padding: 14px;
            border-radius: 6px;
            margin: 10px 0;
        }
        
        .param-line {
            margin: 6px 0;
            padding-left: 18px;
            position: relative;
        }
        
        .param-line::before {
            content: "→";
            color: #64ffda;
            position: absolute;
            left: 0;
        }
        
        .class-panel {
            background: linear-gradient(135deg, #1e3a8a 0%, #3730a3 100%);
            color: white;
            padding: 24px;
            border-radius: 10px;
            margin: 20px 0;
        }
        
        .method-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(320px, 1fr));
            gap: 18px;
            margin-top: 20px;
        }
        
        .method-card {
            background: rgba(255,255,255,0.08);
            padding: 16px;
            border-radius: 8px;
            backdrop-filter: blur(8px);
            border: 1px solid rgba(100, 255, 218, 0.2);
        }
        
        .footer-area {
            text-align: center;
            margin-top: 50px;
            padding-top: 20px;
            border-top: 1px solid #2d4059;
            color: #8892b0;
        }
        
        @media (max-width: 720px) {
            .wrapper {
                padding: 18px;
            }
            .main-title {
                font-size: 1.9em;
            }
            .method-grid {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="header-area">
            <h1 class="main-title">Проект Liza Proj</h1>
            <div class="tagline">Лабораторная работа №3: АСУ с ПИД-регулятором</div>
        </div>
        
        <div class="info-panel">
            <h2>Информация о проекте</h2>
            <p>Проект реализует систему моделирования ПИД-регулятора для тепловых объектов. Включает математическую модель, алгоритм управления и визуализацию результатов.</p>
        </div>
        
        <section class="module">
            <div class="module-title">lab3main.cpp — Главный модуль</div>
            <div class="method-block">
                <div class="method-name">Функция simulateSystem()</div>
                <p>Осуществляет пошаговое моделирование системы управления с ПИД-регулятором.</p>
                <div class="params">
                    <strong>Параметры:</strong>
                    <div class="param-line">pid — экземпляр регулятора</div>
                    <div class="param-line">process — модель процесса</div>
                    <div class="param-line">setpoints — целевые значения</div>
                    <div class="param-line">use_nonlinear — тип модели</div>
                </div>
            </div>
            
            <div class="method-block">
                <div class="method-name">Функция main()</div>
                <p>Точка входа в приложение. Запускает симуляцию и управляет выводом данных.</p>
                <div class="params">
                    <strong>Этапы работы:</strong>
                    <div class="param-line">Инициализация модели объекта</div>
                    <div class="param-line">Настройка ПИД-регулятора</div>
                    <div class="param-line">Запуск моделирования</div>
                    <div class="param-line">Сохранение результатов в CSV</div>
                    <div class="param-line">Построение графиков</div>
                </div>
            </div>
        </section>
        
        <section class="module">
            <div class="module-title">pid.h / pid.cpp — Модуль регулятора</div>
            <div class="class-panel">
                <h3>Класс PIDRegulator</h3>
                <p>Реализация дискретного ПИД-регулятора с рекуррентным алгоритмом управления.</p>
            </div>
            
            <div class="method-grid">
                <div class="method-card">
                    <div class="method-name">Конструктор PIDRegulator()</div>
                    <p>Создает регулятор с заданными параметрами.</p>
                    <div class="params">
                        <strong>Аргументы:</strong>
                        <div class="param-line">P_gain — коэффициент усиления</div>
                        <div class="param-line">I_time — время интегрирования</div>
                        <div class="param-line">D_time — время дифференцирования</div>
                        <div class="param-line">sample_time — период дискретизации</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="method-name">Метод update()</div>
                    <p>Вычисляет управляющее воздействие.</p>
                    <div class="params">
                        <strong>Аргументы:</strong>
                        <div class="param-line">target — заданное значение</div>
                        <div class="param-line">measurement — текущее значение</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="method-name">Метод clear()</div>
                    <p>Сбрасывает состояние регулятора.</p>
                </div>
                
                <div class="method-card">
                    <div class="method-name">Метод getCoeffs()</div>
                    <p>Возвращает коэффициенты регулятора.</p>
                </div>
            </div>
            
            <div class="method-block">
                <div class="method-name">Алгоритм работы</div>
                <div class="params">
                    <div class="param-line">u(k) = u(k-1) + a₀·e(k) + a₁·e(k-1) + a₂·e(k-2)</div>
                    <div class="param-line">a₀ = K·(1 + Td/T₀)</div>
                    <div class="param-line">a₁ = -K·(1 + 2·Td/T₀ - T₀/Ti)</div>
                    <div class="param-line">a₂ = K·Td/T₀</div>
                </div>
            </div>
        </section>
        
        <section class="module">
            <div class="module-title">model.h / model.cpp — Модель объекта</div>
            <div class="class-panel">
                <h3>Класс ProcessModel</h3>
                <p>Математическая модель теплового объекта управления.</p>
            </div>
            
            <div class="method-grid">
                <div class="method-card">
                    <div class="method-name">Конструктор ProcessModel()</div>
                    <p>Инициализирует модель с параметрами.</p>
                    <div class="params">
                        <strong>Аргументы:</strong>
                        <div class="param-line">params — коэффициенты модели</div>
                        <div class="param-line">initial_value — начальное состояние</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="method-name">Метод linearModel()</div>
                    <p>Линейная модель объекта.</p>
                    <div class="params">
                        <strong>Аргумент:</strong>
                        <div class="param-line">input — управляющее воздействие</div>
                    </div>
                </div>
                
                <div class="method-card">
                    <div class="method-name">Метод nonlinearModel()</div>
                    <p>Нелинейная модель с дополнительными эффектами.</p>
                </div>
                
                <div class="method-card">
                    <div class="method-name">Метод setInitialValue()</div>
                    <p>Устанавливает начальное значение.</p>
                </div>
            </div>
            
            <div class="method-block">
                <div class="method-name">Математические модели</div>
                <div class="params">
                    <div class="param-line"><strong>Линейная:</strong> y(k) = a₁·y(k-1) + b₁·u(k)</div>
                    <div class="param-line"><strong>Нелинейная:</strong> y(k) = a₂·y(k-1) - c·y²(k-1) + b₂·u(k) + d·sin(u(k))</div>
                </div>
            </div>
        </section>
        
        <section class="module">
            <div class="module-title">plot_utils.h / plot_utils.cpp — Визуализация</div>
            <div class="method-block">
                <div class="method-name">Функция generatePythonPlotScript()</div>
                <p>Генерирует и запускает Python-скрипт для построения графиков.</p>
                <div class="params">
                    <strong>Создаваемые файлы:</strong>
                    <div class="param-line">simulation_results.csv — данные</div>
                    <div class="param-line">pid_report.html — отчет</div>
                    <div class="param-line">Консольные графики</div>
                    <div class="param-line">Статистика результатов</div>
                </div>
            </div>
        </section>
        
        <div class="footer-area">
            <p>Брестский Государственный технический университет | Кафедра ИИТ</p>
            <p>Лабораторная работа №3 по дисциплине "Общая теория интеллектуальных систем"</p>
            <p>Выполнил: Литвинчук И.М., группа ИИ-28/24 | Проверил: Дворанинович Д.А.</p>
            <p>© 2025</p>
        </div>
    </div>
</body>
</html>