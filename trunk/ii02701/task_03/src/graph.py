import matplotlib.pyplot as plt

# ---------- ЗАГРУЗКА ПАРАМЕТРОВ ИЗ ФАЙЛА ----------
def load_config(filename):
    config = {}
    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            key, value = line.split("=")
            config[key] = float(value)
    return config


cfg = load_config("config.txt")

# ---------- ПИД-КОЭФФИЦИЕНТЫ ----------
kp = cfg["kp"]
ki = cfg["ki"]
kd = cfg["kd"]

# ---------- ПАРАМЕТРЫ МОДЕЛИРОВАНИЯ ----------
dt = cfg["dt"]
steps = int(cfg["steps"])

# ---------- УСТАВКА И НАЧАЛЬНЫЕ УСЛОВИЯ ----------
setpoint = cfg["setpoint"]
process_pid = cfg["initial_pid"]
process_no_pid = cfg["initial_no_pid"]

# ---------- ПРОЧИЕ ПЕРЕМЕННЫЕ ----------
alpha = cfg["alpha"]

integral = 0.0
prev_error = 0.0

time = []
pid_values = []
no_pid_values = []

# ---------- МОДЕЛИРОВАНИЕ ----------
for i in range(steps):
    t = i * dt
    time.append(t)

    # --- СИСТЕМА БЕЗ РЕГУЛЯТОРА ---
    process_no_pid += alpha * (setpoint - process_no_pid)
    no_pid_values.append(process_no_pid)

    # --- ПИД-РЕГУЛЯТОР ---
    error = setpoint - process_pid
    integral += error * dt
    derivative = (error - prev_error) / dt

    control = kp * error + ki * integral + kd * derivative
    process_pid += control * dt

    pid_values.append(process_pid)
    prev_error = error

# ---------- ВИЗУАЛИЗАЦИЯ ----------
plt.figure()
plt.plot(time, pid_values, label="PID control")
plt.plot(time, no_pid_values, label="Without controller")
plt.axhline(y=setpoint, linestyle="--", label="Setpoint")

plt.xlabel("Time (s)")
plt.ylabel("Process value")
plt.title("PID controller vs system without controller")
plt.legend()
plt.grid()

plt.show()