package gui;

import javax.swing.*;
import java.awt.*;

/**
 * Created by Nick on 1/6/2017.
 * Created for custom overriding of states.
 */
public class GameButton extends JButton
{

    enum BUTTON_STATE
    {
        DISABLED,
        ENABLED,
        TRIED_SUCCESS,
        TRIED_FAIL
    }

    Color defaultBGColor;
    private BUTTON_STATE buttonState;

    public GameButton()
    {
        super();
        setFocusable(false);
        defaultBGColor = getBackground();
        buttonState = BUTTON_STATE.ENABLED;
    }


    public void setButtonState(BUTTON_STATE buttonState)
    {
        this.buttonState = buttonState;
        if (buttonState == BUTTON_STATE.TRIED_FAIL)
            setBackground(Color.red);
        else if (buttonState == BUTTON_STATE.TRIED_SUCCESS)
            setBackground(Color.green);
        else
            setBackground(defaultBGColor);

        setEnabled(buttonState != BUTTON_STATE.DISABLED);
    }

    public BUTTON_STATE getButtonState()
    {
        return buttonState;
    }


}