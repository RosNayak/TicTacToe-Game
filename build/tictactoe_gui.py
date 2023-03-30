import os
import tkinter
from tkinter import messagebox
import tictactoe

class Player:
    curr_player = 'one'
    chars = {'one' : 'X', 'two' : 'O'}

class Widgets:
    buttons = []
    message_text = None

def restart_game():
    for i in range(9):
        Widgets.buttons[i].configure(text='  ')

def action(row, column, result):
    status = tictactoe.play_once(row, column)

    Widgets.message_text.delete(1.0, tkinter.END)
    if result[status] == "Error":
        messagebox.showerror("Play Again","Invalid move. Play again.") 
        return 
        # Widgets.message_text.insert(tkinter.INSERT, "Invalid move. Play again.")
    else:
        Widgets.buttons[row*3 + column].configure(text=Player.chars[Player.curr_player])

        if Player.curr_player == 'one':
            Player.curr_player = 'two'
        else:
            Player.curr_player = 'one'
    
        if result[status] == "Player1 Won":
            messagebox.showinfo("Result","Player1 Won the game!!")
        elif result[status] == "Player2 Won":
            messagebox.showinfo("Result","Player2 Won the game!!")
        elif result[status] == "Draw":
            messagebox.showinfo("Result","The game was drawn!!")
        
        if result[status] != "Continue":
            restart_game()

if __name__ == '__main__':

    result = {
        -1 : "Error",
        0 : "Continue",
        1 : "Player1 Won",
        2 : "Player2 Won",
        3 : "Draw"
    }
    
    master = tkinter.Tk()
    master.title("Tic Tac Toe")
    master.geometry("250x250")

    for i in range(9):
        button = tkinter.Button(master, text='  ', command=lambda r=int(i/3),c=int(i%3): action(r, c, result))
        button.grid(row=int(i/3), column=int(i%3))
        Widgets.buttons.append(button)

    message_text = tkinter.Text(master)
    Widgets.message_text = message_text

    tictactoe.setup()

    master.mainloop()    
