package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ArduinoView {

    private JLabel temperatureLabel;
    private JLabel binStatusLabel;
    private JButton restoreButton;
    private JButton cleanButton;
    private JTextArea logs;
    private SerialCommChannel commChannel;
    private int messageCounter = 0;
    private Boolean emergency = false;
    private int full = 0;

    public ArduinoView() {
        JFrame frame = new JFrame("Arduino Communication GUI");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        temperatureLabel = new JLabel("Temperatura: N/D");
        binStatusLabel = new JLabel("Stato Cassonetto: N/D");
        logs = new JTextArea();
        logs.setEditable(false);
        logs.setLineWrap(true);
        logs.setWrapStyleWord(true);

        restoreButton = new JButton("Restore");
        restoreButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                commChannel.sendMsg("RESTORE");
                emergency = false;
                restoreButton.setEnabled(false);
            }
        });
        restoreButton.setEnabled(false);

        cleanButton = new JButton("Empty the container");
        cleanButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                commChannel.sendMsg("CLEAN");
            }
        });

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        panel.add(temperatureLabel);
        panel.add(Box.createRigidArea(new Dimension(0, 10)));
        panel.add(binStatusLabel);
        panel.add(Box.createRigidArea(new Dimension(0, 10)));
        panel.add(restoreButton);
        panel.add(Box.createRigidArea(new Dimension(0, 10)));
        panel.add(cleanButton);
        panel.add(Box.createRigidArea(new Dimension(0, 10)));

        JScrollPane logScrollPane = new JScrollPane(logs);
        logScrollPane.setPreferredSize(new Dimension(350, 100));
        panel.add(logScrollPane);

        frame.getContentPane().add(panel);
        frame.setVisible(true);
    }

    public void registerCommChannel(SerialCommChannel commChannel) {
        this.commChannel = commChannel;
    }

    public void receiveLog(String log) {
        messageCounter++;
        SwingUtilities.invokeLater(() -> logs.append(messageCounter + " " + log + "\n"));
    }

    public void receiveTemperature(String temperature) {
        SwingUtilities.invokeLater(() -> temperatureLabel.setText("Temperatura: " + temperature + "°C"));
    }

    public void receiveEmergency(String val) {
        SwingUtilities.invokeLater(() -> {
            emergency = val.equals("1");
            restoreButton.setEnabled(emergency);
        });
    }

    public void receiveBinStatus(String status) {
        full = Integer.parseInt(status);
        SwingUtilities.invokeLater(() -> {
            binStatusLabel.setText("Container full at " + status + "%");
            cleanButton.setEnabled(full >= 100);
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ArduinoView::new);
    }
}
