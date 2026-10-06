# Reto-IoT-SOMMNUS
## Prototipo Wearable IoT Monitoreo Biomédico

## 📌 Descripción del Proyecto
Este proyecto consiste en un sistema IoT *wearable* diseñado para el monitoreo continuo y no invasivo de variables biomédicas (oximetría $SpO_2$, frecuencia cardíaca, temperatura corporal y detección de caídas/actividad) utilizando el microcontrolador ESP-32.

---

## Integrantes del Equipo
* **Alexis Leonardo Bojórquez García** - A01799749
* **Diego Hernández Larriva** - A01799452
* **Iván Santiago Díaz Vázquez** - A01799469

**Profesor:** David Higuera Rosales  
**Materia:** TC1004B - Implementación de Internet de las Cosas (Grupo 503)  
**Institución:** Tecnológico de Monterrey, Campus Estado de México

---

## Arquitectura del Sistema
1. **Percepción:** Sensores MAX30102, DS18B20 y MPU6050 conectados al microcontrolador ESP-32.
2. **Red:** Transmisión inalámbrica mediante WiFi (802.11 b/g/n) empaquetando datos en formato JSON.
3. **Procesamiento / Middleware:** Ingesta mediante Broker MQTT (Mosquitto/HiveMQ), procesamiento y lógica de alertas en Node-RED, y almacenamiento en InfluxDB2/MongoDB.
4. **Aplicación:** Visualización en tiempo real mediante un Dashboard en Grafana con 5 indicadores biomédicos.
5. **Negocio:** Sistema automático de alertas e historial clínico con políticas de privacidad de datos de salud.

---

## Estructura del Repositorio
* `/firmware`: Código fuente modular para el ESP-32.
* `/hardware`: Esquemáticos de conexión y renders de ubicación física del dispositivo.
* `/middleware`: Exportación de flujos de Node-RED y configuraciones del broker.
* `/dashboard`: Archivos de configuración e indicadores de Grafana.
* `/docs`: Reportes de etapa y bitácora de desarrollo.

---

## Requisitos de Hardware y Software
* **Hardware:** ESP-32 DevKit, MAX30102, DS18B20/MLX90614, MPU6050, LEDs, resistencias ($220\,\Omega / 330\,\Omega$).
* **Software:** Arduino IDE, Node-RED, MQTT Broker, InfluxDB, Grafana.
