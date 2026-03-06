import serial
import time
import csv
from datetime import datetime
import dearpygui.dearpygui as dpg
 
ser = serial.Serial('COM5', 9600)
time.sleep(2)
 
file_dati = open("storico_dati.csv", "w")
file_dati.write("Timestamp, Temperatura, Umidita\n")
file_dati.flush()
 
valori_x, valori_temp, valori_umid = [], [], []
contatore = 0
ultima_scrittura = time.time()
 
dpg.create_context()
 
with dpg.window(label="Monitor Arduino", width=800, height=600):
    dpg.add_text("Temperatura: --", tag="testo_temp")
    dpg.add_text("Suggerimento: --", tag="testo_suggerimento", color=[255, 255, 0])
    plot_temp = dpg.add_plot(height=250, width=-1)
    dpg.add_plot_axis(dpg.mvXAxis, label="Tempo", tag="asse_x_temp", parent=plot_temp)
    y_t = dpg.add_plot_axis(dpg.mvYAxis, label="°C", tag="asse_y_temp", parent=plot_temp)
    dpg.set_axis_limits("asse_y_temp", 15, 35)
    dpg.add_line_series([], [], tag="serie_temp", parent=y_t)
 
    dpg.add_text("Umidità: --", tag="testo_umid")
    plot_umid = dpg.add_plot(height=250, width=-1)
    dpg.add_plot_axis(dpg.mvXAxis, label="Tempo", tag="asse_x_umid", parent=plot_umid)
    y_u = dpg.add_plot_axis(dpg.mvYAxis, label="%", tag="asse_y_umid", parent=plot_umid)
    dpg.set_axis_limits("asse_y_umid", 30, 90)
    dpg.add_line_series([], [], tag="serie_umid", parent=y_u)
 
dpg.create_viewport(title='Monitor Arduino', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
 
while dpg.is_dearpygui_running():
    linea = ser.readline().decode('utf-8').strip()
    parti = linea.split()
 
    temp = float(parti[1])
    umid = float(parti[4].replace('%', ''))
    if time.time() - ultima_scrittura >= 20:
        timestamp = time.strftime("%H:%M:%S")
        file_dati.write(f"{timestamp}, {temp}, {umid}\n")
        file_dati.flush()
        ultima_scrittura = time.time()
    contatore += 1
    valori_x.append(contatore)
    valori_temp.append(temp)
    valori_umid.append(umid)
    if len(valori_x) > 100:
        valori_x.pop(0)
        valori_temp.pop(0)
        valori_umid.pop(0)
    dpg.set_value("testo_temp", f"Temperatura: {temp} °C")
    dpg.set_value("testo_umid", f"Umidità: {umid} %")
    if temp > 25:
        dpg.set_value("testo_suggerimento", "Suggerimento: Troppo caldo, accendi il condizionatore!")
        dpg.configure_item("testo_suggerimento", color=[255, 0, 0]) #rosso
    elif temp < 15:
        dpg.set_value("testo_suggerimento", "Suggerimento: Troppo freddo, riscalda!")
        dpg.configure_item("testo_suggerimento", color=[0, 150, 255])
    else:
        dpg.set_value("testo_suggerimento", "Suggerimento: Condizioni ideali.")
        dpg.configure_item("testo_suggerimento", color=[0, 255, 0])
 
    dpg.set_value("serie_temp", [valori_x, valori_temp])
    dpg.set_value("serie_umid", [valori_x, valori_umid])
    dpg.fit_axis_data("asse_x_temp")
    dpg.fit_axis_data("asse_x_umid")
    dpg.render_dearpygui_frame()
file_dati.close()
ser.close()
dpg.destroy_context()
