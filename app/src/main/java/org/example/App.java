package org.example;

import com.fazecast.jSerialComm.SerialPort;
import org.example.ArduinoView;
import org.example.MonitoringAgent;
import javax.swing.*;

public class App {

    static ArduinoView view = null;

    public static void main(String[] args) throws Exception {
        SwingUtilities.invokeAndWait(() -> {
            view = new ArduinoView();
        });
        String portName = "/dev/ttyACM0";
        SerialCommChannel channel = new SerialCommChannel(portName, 115200);
        new MonitoringAgent(channel, view).start();
        view.registerCommChannel(channel);
    }
}