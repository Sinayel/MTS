import tkinter as tk
import customtkinter
from tkinter import *
import webbrowser
from PIL import Image


# Colors
gris_fonce = "#333333"
gris_moyen = "#C0C0C0"
gris_claire = "#CCCCCC"
blanc = "#FFFFFF"
bleu = "#003366"

window = tk()



# Code :
def open_link():
    webbrowser.open("https://github.com/Sinayel?tab=repositories")

def on_enter(event):
    packBouton["bg"] = blanc
    packBouton["fg"] = "#323232"
    packBouton["borderwidth"] = 2

def on_leave(event):
    packBouton["bg"] = "#323232"
    packBouton["fg"] = blanc
    packBouton["borderwidth"] = 0

def on_click():
    # Action à effectuer lorsque le bouton est cliqué
    pass



# Main frames/blocks
topbar=tk.Frame(window, bg=bleu)
topbar.place(relx=0, rely=0, relwidth=1, relheight=0.08)

mainFrame=tk.Frame(window, bg=gris_moyen)
mainFrame.place(relx=0.15, rely=0.08, relwidth=1, relheight=0.92)



# Tous les Buttons

# Topbar Contents
reportBug=tk.Button(topbar, text="    GitHub", anchor="w", font=("Futura PT", 13), fg=gris_fonce, borderwidth=0, command=open_link)
reportBug.place(relx=0.9, rely=0.2, relwidth=0.085, relheight=0.55)


# Main content
packButton=customtkinter.CTkButton(mainFrame, text="📂", font=("Futura PT", 30), fg=gris_fonce, borderwidth=0, command=on_click)
packButton.place(relx=0.06, rely=0.05, relwidth=0.1, relheight=0.08)


# Créer un label pour l'effet visuel du bouton
packBouton = tk.Label(mainFrame, text=" appliquer", font=("Futura PT", 15))
packBouton.bind("<Enter>", on_enter)
packBouton.bind("<Leave>", on_leave)
packBouton.bind("<Button-1>", lambda event: on_click())
packBouton.place(relx=0.06, rely=0.15, relwidth=0.1, relheight=0.046)

button = customtkinter.CTkButton(master=window, text="Hello World!")
button.place(relx=0.5, rely=0.5, anchor=CENTER)



# Personalization
window.resizable(width=False, height=False)
window.configure(bg=blanc)

window.title("MTS")
window.geometry('830x500')
window.update()
window.mainloop()