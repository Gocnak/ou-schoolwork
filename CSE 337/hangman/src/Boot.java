import gui.GUIMain;

import javax.swing.*;

/**
 * Created by Nick on 1/5/2017.
 */
public class Boot
{
    public static void main(String[] args)
    {


        // Open the main GUI
        SwingUtilities.invokeLater(() ->
        {
            setLookAndFeel();
            new GUIMain();
        });
    }

    private static void setLookAndFeel() {
        try {
            UIManager.setLookAndFeel("lib.jtattoo.com.jtattoo.plaf.hifi.HiFiLookAndFeel");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
