# Event handling

The purpose of this document is to server as a plan and reminder of what needs to be done in order to properly handle player input on the client side.

## Requirements

The game uses the left mouse click for everything game-play related, but the game should also handle keys that could be used to chat or to input text generally (like when typing one's own name or the server address/port).
Given these considerations, I suppose the game should have some sort of special handling for events. Understandably, the key events should only do anything if a text entry widget is selected. That should no be a problem given that that is the only place where text can be the input, and since that widget could be reused wherever it's needed.
However, the mouse click could actually do different things, and I suppose it should "route" that click somehow. Consider the case when the game is being played:
    - If the text entry widget in the chat box is clicked, it is put in focus and text entry starts working.
    - If a button such as main menu, submit turn, or undo turn step is clicked, those actions should do what they need to.
    - If an elemental piece is clicked, it should enter the placement mode, where the next click on the field is used to place the piece.
    - If water empowerment needs to be used, it enters a mode where the arrow keys move the river, the back space returns to the original location and, and enter commits the turn step.
    - If the player clicks on the sage, the sage player should see which places the sage can land on.
To me it seems that there are different states the input can be in. I am unsure whether I should make some sort of state machine, or have different "sets" (not literal, mathematical sets) of keybindings to use in different states, or a combination of those two.
The problem which arises with callbacks in such a manner is that sometimes the function that is called should be interested in the key that was pressed (enter, arrow keys, some letter) and sometimes not (mouse click).

I am currently unsure how to do this, but I suppose I will get back to it in a weekend.
