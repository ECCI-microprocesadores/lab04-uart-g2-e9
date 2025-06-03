import serial

# Configuración del puerto
SERIAL_PORT = 'COM4'
BAUDRATE = 9600

try:
    # Abrir puerto serie
    ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
    print(f"Conectado al puerto {SERIAL_PORT}")
    print("Presiona Ctrl+C para terminar")
    print("-" * 40)
    
    # Leer datos continuamente
    while True:
        if ser.in_waiting > 0:  # Si hay datos disponibles
            data = ser.readline().decode('utf-8').strip()
            if data:  # Si se recibió algo
                print(data)  # Mostrar en terminal
                
except serial.SerialException as e:
    print(f"Error al conectar al puerto {SERIAL_PORT}: {e}")
    print("Verifica que el puerto esté disponible y no esté en uso")
    
except KeyboardInterrupt:
    print("\nPrograma terminado")
    
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Puerto cerrado")