package gui;

import lib.jtattoo.com.jtattoo.plaf.ColorHelper;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by Nick on 1/4/14.
 * <p>
 * This class is like a listener for tabs, but only for setting the colors of them.
 * Credit to http://www.coderanch.com/t/346366/GUI/java/macs-button-pulse
 * for the idea.
 */
public class TabPulse extends Thread {

    private Color[] totalColors = new Color[200];
    private final Color controlColorDark = new Color(32, 32, 32);

    private javax.swing.Timer timer;
    private JComponent component;

    public TabPulse(JComponent comp) {
       this.component = comp;
        TimerListener tl = new TimerListener(c ->
        {
            component.setBackground(c);
            component.repaint();
        });
        timer = new javax.swing.Timer(20, tl);
    }

    @Override
    public void run() {
        timer.start();
        while (GUIMain.instance.shouldPulse()) {
            //do pulse, and just sleep
            try {
                Thread.sleep(50);
            } catch (Exception ignored) {
            }
        }
        timer.stop();
        timer = null;
        GUIMain.isPulsing = false;
        component.setBackground(null);
        component.repaint();
    }

    @Override
    public void interrupt() {
        GUIMain.isPulsing = false;
        component.setBackground(null);
        component.repaint();
        super.interrupt();
    }

    @Override
    public synchronized void start() {
        initColors();
        GUIMain.isPulsing = true;
        super.start();
    }

    private void initColors() {
        Color[] colors = ColorHelper.createColorArr(controlColorDark, ColorHelper.darker(Color.orange, 20), 100);
        System.arraycopy(colors, 0, totalColors, 0, totalColors.length / 2);
        for (int i = 100; i < totalColors.length; i++) {
            totalColors[i] = colors[(colors.length - 1) - (i - colors.length)];
        }
    }

    private class TimerListener implements ActionListener {
        ColorChanger colorChanger;
        int currentColor;

        public TimerListener(ColorChanger cc) {
            colorChanger = cc;
            currentColor = 0;
        }

        public void actionPerformed(ActionEvent e) {
            colorChanger.setColor(totalColors[currentColor]);
            currentColor = (currentColor + 1) % totalColors.length;
        }
    }

    // added to loosen coupling a little bit
    private interface ColorChanger {
        void setColor(Color c);
    }
}