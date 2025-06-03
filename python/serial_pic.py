import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import re
from collections import deque

SERIAL_PORT = 'COM4'  # Puerto serie
BAUDRATE = 9600       # Velocidad de comunicación

MAX_POINTS = 100

ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)  # Inicializa el puerto

voltages = deque(maxlen=MAX_POINTS)
times = deque(maxlen=MAX_POINTS)
time_counter = 0

regex = re.compile(r"V:\s*([\d.]+)")  # Expresión regular mejorada

def update(frame):
    global time_counter
    try:
        line = ser.readline().decode('utf-8').strip()
        
        if line:  # Verifica que se recibió algún dato            
            match = regex.search(line)
            if match:
                voltage = float(match.group(1))
                voltages.append(voltage)
                times.append(time_counter)
                time_counter += 1

                ax.clear()
                ax.plot(times, voltages, color='blue')
                ax.set_ylim(0, 6)
                ax.set_title("Voltaje leído por UART")
                ax.set_xlabel("Tiempo (s)")
                ax.set_ylabel("Voltaje (V)")
                ax.grid(True)

    except UnicodeDecodeError:
        print("Error al decodificar datos")

fig, ax = plt.subplots()
ani = animation.FuncAnimation(fig, update, interval=100, cache_frame_data=False)
plt.tight_layout()
plt.show()