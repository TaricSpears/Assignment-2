import com.fazecast.jSerialComm.SerialPort;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class ArduinoGUI extends Application {

    private SerialPort serialPort;
    private Label temperatureLabel;
    private Label binStatusLabel;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // Inizializza porta seriale
        initializeSerial();

        // Crea interfaccia
        temperatureLabel = new Label("Temperatura: N/D");
        binStatusLabel = new Label("Stato Cassonetto: N/D");

        Button restoreButton = new Button("Restore");
        restoreButton.setOnAction(e -> sendToArduino("RESTORE"));

        Button cleanButton = new Button("Cassonetto Pulito");
        cleanButton.setOnAction(e -> sendToArduino("CLEAN"));

        VBox layout = new VBox(10, temperatureLabel, binStatusLabel, restoreButton, cleanButton);
        layout.setStyle("-fx-padding: 20; -fx-alignment: center;");

        Scene scene = new Scene(layout, 400, 300);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Arduino Communication GUI");
        primaryStage.show();

        // Start lettura seriale
        startReadingSerial();
    }

    private void initializeSerial() {
        SerialPort[] ports = SerialPort.getCommPorts();
        if (ports.length > 0) {
            serialPort = ports[0]; // Seleziona la prima porta trovata
            serialPort.setBaudRate(9600);
            serialPort.openPort();
        } else {
            System.out.println("Nessuna porta seriale trovata.");
        }
    }

    private void sendToArduino(String command) {
        if (serialPort != null && serialPort.isOpen()) {
            serialPort.writeBytes(command.getBytes(), command.length());
        }
    }

    private void startReadingSerial() {
        if (serialPort != null && serialPort.isOpen()) {
            new Thread(() -> {
                byte[] buffer = new byte[1024];
                while (true) {
                    int bytesRead = serialPort.readBytes(buffer, buffer.length);
                    if (bytesRead > 0) {
                        String message = new String(buffer, 0, bytesRead).trim();
                        processArduinoMessage(message);
                    }
                }
            }).start();
        }
    }

    private void processArduinoMessage(String message) {
        // Messaggi formattati come "TEMP:25" o "BIN:FULL"
        if (message.startsWith("TEMP:")) {
            String temp = message.split(":")[1];
            temperatureLabel.setText("Temperatura: " + temp + "°C");
        } else if (message.startsWith("BIN:")) {
            String status = message.split(":")[1];
            binStatusLabel.setText("Stato Cassonetto: " + status);
        }
    }

    @Override
    public void stop() {
        if (serialPort != null && serialPort.isOpen()) {
            serialPort.closePort();
        }
    }
}
