package org.example;

public class MonitoringAgent extends Thread {

    SerialCommChannel channel;
    ArduinoView view;

    public MonitoringAgent(SerialCommChannel channel, ArduinoView view) throws Exception {
        this.view = view;
        this.channel = channel;
    }

    private void processArduinoMessage(String message) {
        if (!message.contains(":")) {
            return;
        }
        // System.out.println("Received message: " + message);
        String msg = message.split(":")[1];
        if (message.startsWith("EMERGENCY:")) {
            view.receiveEmergency(msg);
        } else if (message.startsWith("TEMP:")) {
            view.receiveTemperature(msg);
        } else if (message.startsWith("BIN:")) {
            view.receiveBinStatus(msg);
        } else if (message.startsWith("LOG:")) {
            view.receiveLog(msg);
        }

    }

    public void run() {
        while (true) {
            try {
                String msg = channel.receiveMsg();
                processArduinoMessage(msg);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

}
